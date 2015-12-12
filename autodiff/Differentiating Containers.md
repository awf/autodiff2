## Computing derivatives of containers

In which we learn how to declare the gradient of a general function, and hence the chain rule, without any nasty vectorization, tensorization, or general brain pain.

Some key desiderata:
 * The derivative of a function should be declared **without needing new datatypes**.
 * We should have a simple consistent **chain rule** for function composition.
 * We should be able to define derivatives of functions taking **arbitrary arguments**, e.g. given the declarations
   ```cpp
   template <class Real>
   struct packet<Real> {
     std::vector<Real> envelope;
     bag<Real> payload;
   };
   // And similar container types
   //  suitcase<Real>
   //  matrix<Real>
   //  bag<Real>
   ```
   we should be able to compute the gradient of
   ```cpp
   std::list<matrix<Real>> foo(suitcase<std::vector<Real>>, packet<Real>);
   ```
 * We probably don't want to serialize each argument into a vector, even if only notionally, because we will lose all the operations defined on the original datatypes, e.g. BLAS multiplication for matrices.
 * Related, many readers will want to put tensors everywhere.   I hope to explain why that's neither necessary nor desirable.
 * When a derivative is a block of zeroes, or the identity matrix, we need to make sure the compiler can see it and generate optimal code.
 * If we do it right, we will easily be able to mix handwritten, symbolically generated and autodiffed derivatives, while generating optimal code.

And I'll write ``grad_foo`` for the derivative of `foo` by the power of unicode.  It's not a special symbol, just a normal character that can be part of identifiers.

#### Introduction

We always knew how to write the derivatives of scalar functions of matrix arguments:
```cpp
	Real trace(Mat3x3<Real> m)
	{
	  return sum(diag(m));
	}

	Mat3x3<Real> grad_trace(Mat3x3<Real> m)
	{
	  return Mat3x3<Real>::identity();
	}
```
or matrix functions of scalars, or vector functions of vectors (or at least we thought we did, see later).
But we always got a little bit stuck with matrix functions of vectors.
```cpp
	Mat3x3<Real> rot(Vec3<Real> v)
	{
	  // fill in some code
	}

	???? grad_rot(Vec3<Real> v)
	{
	  // we know the code to write -- 27 numbers, but where do they go?
	}
```
It's some sort of tensor, we said.  But it was always a bit messy.

And if, instead of Mat3x3<Real>, "rot" had had a return type of
```cpp
	struct Bucket<Real> { 
	   Vec3<Real> u;
	   Mat3x3<Real> v; 
	};
```
we were really quite stuck.

##### Contribution 1: Derivatives of functions of arbitrary containers.

This note defines rules for such derivatives which, I believe, make everything very very simple.  This rule works for anything, and should even make us think hard about vector functions and the Jacobian.

So, what is the new rule?  It's this:
Given arbitrary containers, and a function `f` written using them, like this:
```cpp
	Container1<Real>               f(Container2<Real>);
```
create `grad_f`, such that every `Real` in the output will have a derivative for each `Real` in the input.  That is, we replace `Real` in the return type by `Container2<Real>` from the function argument:
```cpp
	Container1<Container2<Real>>   grad_f(Container2<Real>);
```

And now we can define ```grad_rot```:
```cpp
	Mat3x3<Real> rot(Vec3<Real> v);
	Mat3x3<Vec3<Real>> grad_rot(Vec3<Real> v)
	{
	  ...;
	}
```
Now, I know you're still fretting about the tensors, but please bear with me.  First, let's see how simply we can chain-rule these together.

##### Contribution 2: The chain rule for such functions.

First an example.  Here's a simple function: trace of rot
```cpp
	Real trace_of_rot(Vec3<Real> x)
	{
	  return trace(rot(x));
	}
```
Right away we know the signature of its gradient:
```cpp
	Vec3<Real> grad_trace_of_rot(Vec3<Real>);
```
but it's often difficult to see what to put in the function body.

Well, let's pretend everything's a scalar and just take derivatives:

    trace_of_rot(x) = trace(rot(x))
    trace_of_rot'(x)= trace'(rot(x)) * rot'(x)

So let's just try to write that derivative with grads:

    grad_trace_of_rot(x)= grad_trace(rot(x)) * grad_rot(x)

The only thing that goes wrong is the multiply...  So what multiply is intended here?  Matrix product?  Outer product?  Dot product? If you've done this sort of thing before, you'll be worrying about matrix transposes, order of multiplication, and probably rolling the word &ldquo;tensor&rdquo; around in your mouth.  It is a lovely word.

In fact, it's very simple.  It's always a dot product.  And for a general type `Container<T>`, dot product of A and B means multiplying all the elements of A by the corresponding element of B and accumulating the result.  More generally, we will have
```cpp
    dot(Container<U>, Container<V>) -> typeof U*V
```
So let's go back to `trace_of_rot`, and expand the code with some type
declarations just to see what's happening.
```cpp
    mat<Real>      val_rot = rot(x);
    mat<vec<Real>> grad_rot = grad_rot(x);

    Real           val_trace = trace(val_rot);
    mat<Real>      grad_trace = grad_trace(val_rot);

    vec<Real>      grad_trace_of_rot = dot(grad_trace, grad_rot);
```
So that dot has signature
```cpp
    dot(mat<Real>, mat<vec<Real>>) -> typeof Real * vec<Real>
```
or
```cpp
    vec<Real> dot(mat<Real>, mat<vec<Real>>);
```
And it's the matrix dot, i.e. `dot(A,B) = trace(A*B')`, or more simply,
the one where you add up every element of the elementwise product.  But it doesn't return a scalar, it returns a ```vec<Real>``` because the second matrix's elements are ```vec<Real>``` and I'm assuming a scalar times a vector gives a vector.

Okay, is that it?  Not quite.  Here the original function ```trace_of_rot``` returned a scalar, while our general function ```f``` returns a ```Container1<Real>``` (henceforth  abbreviated ```C1<Real>```).  The general definition of dot we will use is this:
```
   dot(C1<Container<Real>>, Container<C3<Real>>) -> C1<C3<Real>>
```
In words, corresponding elements of the ```Container```s are summed, and the results are gathered into a ``C1`` of the appropriate type.

The last detail is implementation of this in say C++.  We can easily use template magic to identify the Containers for simple cases, but we need our definition to work if `C1` is a `vec<vec<T>>` and `Container` is a `vec<vec<T>>` while `C3` is a `vec<T>`.  Then the compiler sees
```cpp
	dot(vec<vec<vec<vec<Real>>>>, vec<vec<vec<Real>>>) -> ???
```
and `Container` could match to any of
```cpp
	vec<Real>
	vec<vec<Real>>
	vec<vec<vec<Real>>>
```
The solution is to specify how to split the second argument, and the easiest way I found was to pass an additional argument of type `C3<Real>`.  In the case of the chain rule, this is probably lying about because it must be the point at which the composed function was evaluated.   That is, if we're doing grad of ``f(g(x))``, we must have ``x`` somewhere nearby.  Thus, the actual signature of dot, now called gdot to improve some error messages, is
```cpp
   C1<C3<Real>> gdot(C1<Container<Real>>, Container<C3<Real>>, C3<Real>)
```
And the general chain rule is
```
      f(x) = h(g(x))
      grad_f(x) = gdot( grad_h(g(x)), grad_g(x), x )
```
And to go back to our example, the definition of ``grad_trace_of_rot`` is
```cpp
	Vec3<Real> grad_trace_of_rot(Vec3<Real>  x)
	{
	  return gdot(grad_trace(rot(x)), grad_grad(x), x);
	}
```

### Multiple arguments

### Efficiency

### Vec of Vec and Jacobians

### Matrix inverse

In mathematics, we know how to compute the derivative of a function which
takes a vector as argument and returns a vector.  We call it the _Jacobian
matrix_.
```cpp
vec<Real>   f(vec<Real> x);
mat<Real> grad_f(vec<Real> x); // Jacobian is grad_f
```

This remains easy for scalar functions of matrices and matrix functions of
scalars:
```cpp
mat<Real>  f(Real x);
mat<Real> grad_f(Real x); // Also written f' or \dot{f}

Real       trace(mat<Real> x);
mat<Real> grad_trace(mat<Real> x);
```

But often you meet a matrix function of vector argument.  It's straightforward to say "it returns a tensor":
```cpp
mat<Real> f(vec<Real> x);
tensor<Real> grad_f(vec<Real> x);
```
but keeping track of the indices often involves one in intricate
bookkeeping, nasty tensorial analogues of the transpose, and anyway,
not everything is a matrix, even in MATLAB.  Furthermore, we would
like a definition of derivative that does not require us to introduce
new datatypes to hold the result.

#### Containers

A more natural sort of function to deal with in C++ might be like this:

      vec<Real> f(list<mat<Real>> P)

We would like a definition of `grad_f` which works for all such cases.  Well,
it's super easy: every `Real` in the output will have a
derivative for each `Real` in the input.  That is, we replace `Real` in
the return type by `list<mat<Real>>` from the function argument

      vec<list<mat<Real>>> grad_f(list<mat<Real>> P)

and the i'th entry of the returned `vec` is simply the list of matrices
of derivatives of the original i'th entry with respect to the input reals.
In terms of general containers `Container1` and `Container2` we relate
`f` and `grad_f` like this:

    Container2<Real>             f(Container1<Real>)
    Container2<Container1<Real>> grad_f(Container1<Real>)

Of course, simply defining something like this is easy, and could be
done however one likes.   The value of the definition is in whether or
not it simplifies our lives.  Let's first look at a couple of standard
examples and then look at where this really helps—in the chain rule.


##### Example: Matrix function of vector arguments

In the "tensor" example above, the new rule leads to a natural
alternative:

      mat<Real>      f(vec<Real>)
      mat<vec<Real>> grad_f(vec<Real>)

The matrix of vectors may look like it's no more than an inefficient way of
storing a non-[jagged](http://stackoverflow.com/tags/jagged-arrays/info)
3D array or tensor, but don't worry about the jaggedness for the moment.
For one thing, these functions are frequently encountered with
fixed-size arrays.  For example, the
[exponential map](https://en.wikipedia.org/wiki/Rotation_matrix#Exponential_map)
might have signature

      mat<Real,3,3> rot(vec<Real,3>)

indicating that it operates only on 3-vectors and returns only 3x3 matrices.
Then its gradient

     mat<vec<Real,3>,3,3> grad_rot(vec<Real,3>)

will be stored just as efficiently as it would have been in a fixed-size
3x3x3 tensor.


##### Jagged Jacobians "just work"

But now let's look at a potentially worrying (function, derivative) pair:
```cpp
vec<Real>      sin(vec<Real>)
vec<vec<Real>> grad_sin(vec<Real>)
```
Shouldn't that gradient `grad_sin` be a matrix, not a vector of vectors?
Not by our rules, and as you'll see, it won't matter.  In fact, the
special case matrix-vector mutiplication will naturally drop out of
the chain rule, and we'll help the compiler to remove inefficient
computation and storage.  And note that this definition doesn't
require a new datatype: if all you had were vecs, you would not need
another type to represent derivatives.




#### The chain rule

As promised, the full advantage of this containerized view is not really
apparent until we see the chain rule in action.  Consider the function

      Real trace_of_rot(vec<Real> x) {
        return trace(rot(x));
      }

The declarations of `trace` and its gradient are standard:

      Real trace(mat<Real> M)
      mat<Real> grad_trace(mat<Real> M)

Note that I've dropped the fixed-size (e.g. 3x3) annotations.  Without
even looking at the definition of `trace_of_rot`, we know the
signature of its derivative:

      vec<Real> grad_trace_of_rot(vec<Real> x) {
        return ...;
      }

Let's now try to discover what goes in that return statement.


xx
      Real dot(mat<Real>, mat<Real>)

The most general depth-1 form will be in terms of three containers:

      C1<C3<Real>> dot(C1<Container<Real>>, Container<C3<Real>>)
         ...
         out[i] += dot(a[i], b[i])

Let's try it with our example, where `h` is `trace` and `g` is
`rot`.  The types of their gradients are recalled first.

                      mat<Real>        mat<vec<Real>>
                   ------v--------      -----v-----
      return dot(grad_trace(rot(x)),   grad_rot(x));

The dot product is between a `mat<Real>` and a `mat<vec<Real>>`, so its
return type is whatever you get when you multiply `Real*vec<Real>`, i.e.
a `vec<Real>`, which is what we promised before the "`...`" above.
How did the compiler select the right dot?   Answers later at [unification].  For the moment, let's talk about
efficiency.

##### Efficiency

You may have noticed that the programmer who wrote `f` missed some
significant optimizations.   The main point is that the derivative of
`trace` has a particularly simple form: it's the identity, whatever the
input.  So `grad_f`'s return line is effectively

      return dot(Identity, grad_rot(x))

meaning that only the diagonal elements of `grad_rot(x)` need ever be
computed.  Luckily we can help the compiler to fix this for us.  The
full signature of the called functions in the code is as follows:

      mat<Real,3,3,Mat_Identity> grad_trace(mat<Real,3,3,Mat_GENERAL> M);

and the call to `dot` is the specialized

      dot(mat<T1,R1,C1,Mat_Identity> a, mat<T2,R2,C2,Mat_GENERAL> b)

which extracts only the diagonal elements of its second argument,
giving the compile-time information needed to optimize the call.

#### Arbitrary structs

And now for something a little more exotic.  We have some arbitrary
struct





      template <class R>
      struct Foo {
        Matrix<R,3,3> A;
        Vec<R,3> b;
      }

and a function

      list<Real> f(Foo<Real> x)

What's its derivative?  Same as above:

      list<Foo<Real>> grad_f(Foo<Real> x)

The derivative of the second entry of the list with respect to the
(1,2) element of `x.A` is just

      list<Foo<Real>> grad_l = grad_f(x)
      std::cout << "Your derivative: " << ++grad_l.begin()->A(1,2);

Easy.  Or maybe we had

      Foo<Real> f(list<vec<Real>> x)
      Foo<list<vec<Real>>> grad_f(list<vec<Real>> x)

Also easy.


##### Unification
[unification]:

Matching this to our generic dot, we can only do it if `Container` is
`mat`

Tricky case 1:

      set<Foo<Real>> f(list<vec<Real>> x)
      set<Foo<list<vec<Real>>>> grad_f(list<vec<Real>> x)

      list<vec<Real>> g(mat<Real> x)
      list<vec<mat<Real>>> grad_g(mat<Real> x)

      set<Foo<Real>> h(mat<Real> x) {
        return f(g(x))
      }
      set<Foo<mat<Real>>> grad_h(mat<Real> x) {
        return dot(grad_f(g(x)), grad_g(x), g);
      }

      dot(set<Foo<list<vec<Real>>>>, list<vec<mat<Real>>>)

Here, container is "obviously" `list<vec>` because that's as much of
the second argument as you can match to the first.  But what if the
containers had had the same types...

      dot(vec<vec<vec<vec<Real>>>>, vec<vec<vec<Real>>>)

Then simple matching on the types could choose any of

      vec
      vec<vec>
      vec<vec<vec>>

And only the second one is correct.   To fix this, we need to tell `dot`
how many containers to strip from the second argument.



So the chain rule of


Now, C++ can't yet match Container to nested types, so we'll have to hack it, but for now
let's pretend it can match `X<Real>` like this:

  list<Vec<Real>>:  X<.> := list<Vec<.>>
  Real:             X<.> := Identity<.>  where Identity is like a 1-element container

So it works fine for normal scalar/vector setup:
Real f(Vec<Real,N>) // Match is to Identity<Real> f(Vec<Real,N>), so Container==Identity
has derivative
Identity<Vec<Real,N>> grad_f(Vec<Real,N>)
i.e.
Vec<Real,N> grad_f(Vec<Real,N>)
as required.

Now, try
Vec<Real,M> f(Vec<Real,N>)
it has derivative
Vec<Vec<Real,N>,M> grad_f(Vec<Real,N>)
so Vec<Vec<>> is the Jacobian.  As written this implies jagged storage for non-fixed-size vectors,
but we can specialize Vec<Vec<>> to act like a matrix, so don't fret.

Now the case that normally trips up the casual differentiator:
Mat<Real,M,N> f(Vec<Real,D>)
has derivative
Mat<Vec<Real,D>,M,N> grad_f(Vec<Real,D>)
Normally one would go all tensorial at this point, but it really is a pain.   This is just the
same as the Vec<Vec> case above.


!! Chain Rule
Many derivatives one encounters in practice arise from application of the chain rule.   In this
arbitrary data structures scheme, the chain rule works out pretty simply.   We have two functions
Container1<Real> f(T1<Real>);
T1<Real> g(T2<Real>);
which we compose to make function h
Container1<Real> h(T2<Real> x) {
return f(g(x));
}
and notice that "of course", the return type of g matches the argument type of f, otherwise we
couldn't have composed them.
We can see the datatype of grad_h easily as above:
Container1<T2<Real>> grad_h(T2<Real> x)
But what's in the function body?
{
Container1<T1<Real>> gradf = grad_f(g(x));
T1<T2<Real>> gradg = grad_g(x);
return DOT(gradf, gradg); // Call DOT(Container<T1<Stuff>>, T1<OtherStuff>)
}


## References:
∂ for data: differentiating data structures
http://www.cs.nott.ac.uk/~txa/publ/jpartial.pdf
> Derives chain rules for container of container etc

Derivatives of Containers
Michael Abbott, Thorsten Altenkirch, Neil Ghani, and Conor McBride
http://www.cs.nott.ac.uk/~txa/publ/tlca03.pdf‎

http://blog.sigfpe.com/2006/06/fun-with-derivatives-of-containers.html
Dan Piponi

Comonadic functional attribute evaluation
Tarmo Uustalu, Varmo Vene
http://www.cs.ioc.ee/~tarmo/papers/tfp05-book.pdf


## More scribbles

Container<Real> f(Real)
