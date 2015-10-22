## Computing derivatives of containers

#### Introduction

In mathematics, we know how to compute the derivative of a function which 
takes a vector as argument and returns a vector.  We call it the _Jacobian
matrix_.

      vec<Real>  f(vec<Real> x);
      mat<Real> ∇f(vec<Real> x); // Jacobian is ∇f

This remains easy for scalar functions of matrices and matrix functions of
scalars:

      mat<Real>  f(Real x);
      mat<Real> ∇f(Real x); // Also written f' or \dot{f}

      Real       f(mat<Real> x);
      mat<Real> ∇f(mat<Real> x);

But often you meet a matrix function of vector argument.  It's 
straightforward to say "it returns a tensor":

      mat<Real> f(vec<Real> x);
      tensor<Real> ∇f(vec<Real> x);

but keeping track of the indices often involves one in intricate 
bookkeeping, nasty tensorial analogues of the transpose, and anyway, 
not everything is a matrix, even in MATLAB.



#### Containers

A more natural sort of function to deal with in C++ might be like this:

      vec<Real> f(list<mat<Real>> P)

We would like a definition of ∇f which works for all such cases.  Well,
it's super easy.   Each of the `Real`s in the output will have a 
derivative for each `Real` in the input.  That is, we replace `Real` in
the return type by `list<mat<Real>>` from the function argument

      vec<list<mat<Real>>> ∇f(list<mat<Real>> P)

and the i'th entry of the returned `vec` is simply the list of matrices 
of derivatives of the original i'th entry with respect to the input reals.  
In terms of general containers `Container1` and `Container2` we relate 
`f` and `∇f` like this:

    Container2<Real>             f(Container1<Real>)
    Container2<Container1<Real>> ∇f(Container1<Real>)

Of course, simply defining something like this is easy, and could be 
done however one likes.   The value of the definition is in whether or
not it simplifies our lives.  Let's first look at a couple of standard
examples and then look at where this really helps—in the chain rule.


##### Example: Matrix function of vector arguments

In the "tensor" example above, the new rule leads to a natural 
alternative:

      mat<Real>      f(vec<Real>)
      mat<vec<Real>> ∇f(vec<Real>)

The matrix of vectors may look like it's no more than an inefficient way of 
storing a non-[jagged](http://stackoverflow.com/tags/jagged-arrays/info)
3D array or tensor, but don't worry about the jaggedness for the moment.
For one thing, these functions are most frequently encountered with 
fixed-size arrays.  For example, the 
[exponential map](https://en.wikipedia.org/wiki/Rotation_matrix#Exponential_map)
might have signature

      mat<Real,3,3> exp2mat(vec<Real,3>)

indicating that it operates only on 3-vectors and returns only 3x3 matrices.
Then its gradient

     mat<vec<Real,3>,3,3> ∇exp2mat(vec<Real,3>)

will be stored just as efficiently as it would have been in a fixed-size 
3x3x3 tensor.


##### Jagged Jacobians "just work"

But now let's look at a potentially worrying (function, derivative) pair:

      vec<Real>      sin(vec<Real>)
      vec<vec<Real>> ∇sin(vec<Real>)

Shouldn't that gradient `∇sin` be a matrix, not a vector of vectors?   
Not by our rules, and as you'll see, it won't matter.   In fact, the 
special case matrix-vector mutiplication will naturally drop out of the 
chain rule, and we'll help the compiler to remove inefficient computation
and storage.




#### The chain rule

As promised, the full advantage of this containerized view is not really 
apparent until we see the chain rule in action.  Consider the function

      Real f(vec<Real> x) {
        return trace(exp2mat(x));
      }

The declarations of `trace` and its gradient are standard:

      Real trace(mat<Real> M)
      mat<Real> ∇trace(mat<Real> M)

Note that I've dropped the fixed-size (e.g. 3x3) annotations.   Without 
even looking at the definition of `f`, we know the signature of its 
derivative:

      vec<Real> ∇f(vec<Real> x) {
        return ...;
      }

Let's now try to discover what goes in that return statement.

Now, before applying the container chain rule, let's look at a scalar 
function and its derivative:

>  <math>f(x) = h(g(x))</math><br/>
>  <math>f'(x)= h'(g(x)) * g'(x)</math>

So let's just try to write that derivative with grads:

      ∇f(x) = ∇h(g(x)) * ∇g(x)

We can immediately see that even for simple functions `h` and `g`, that 
that multiplication is ambiguous: if `∇h` and `∇g` are vectors, what 
multiplication is meant?   Dot product?  Outer product?   If you've done
this sort of thing before, you'll be worrying about matrix transposes,
order of multiplication, and probably rolling the word 
&ldquo;tensor&rdquo; around in your mouth.   It is a lovely word.  Anyway,
to cut to the chase, the general chain rule with depth-N containers is

      ∇f(x) = dot( ∇h(g(x)), ∇g(x) )

with one twist: for &ldquo;deeper&rdquo; containers (e.g. `list<vec<T>>`), 
one needs to specify an additional depth parameter (see below).  For now,
let's get back to our example.

The basic rule of dotting any container is that you multiply and add 
all of its elements, whatever shape it has.  So the dot product of matrix 
and matrix is still a scalar:

xx
      Real dot(mat<Real>, mat<Real>)
      
The most general depth-1 form will be in terms of three containers:

      C1<C3<Real>> dot(C1<Container<Real>>, Container<C3<Real>>) 
         ...
         out[i] += dot(a[i], b[i])

Let's try it with our example, where `h` is `trace` and `g` is 
`exp2mat`.  The types of their gradients are recalled first.

                      mat<Real>        mat<vec<Real>> 
                   ------v--------      -----v-----
      return dot(∇trace(exp2mat(x)),   ∇exp2mat(x));
  
The dot product is between a `mat<Real>` and a `mat<vec<Real>>`, so its
return type is whatever you get when you multiply `Real*vec<Real>`, i.e.
a `vec<Real>`, which is what we promised before the "`...`" above.  
How did the compiler select the right dot?   Answers later at [unification].  For the moment, let's talk about 
efficiency.

##### Efficiency

You may have noticed that the programmer who wrote `f` missed some 
significant optimizations.   The main point is that the derivative of
`trace` has a particularly simple form: it's the identity, whatever the 
input.  So `∇f`'s return line is effectively

      return dot(Identity, ∇exp2mat(x))

meaning that only the diagonal elements of `∇exp2mat(x)` need ever be 
computed.  Luckily we can help the compiler to fix this for us.  The 
full signature of the called functions in the code is as follows:

      mat<Real,3,3,Mat_Identity> ∇trace(mat<Real,3,3,Mat_GENERAL> M);

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

      list<Foo<Real>> ∇f(Foo<Real> x)

The derivative of the second entry of the list with respect to the 
(1,2) element of `x.A` is just 

      list<Foo<Real>> ∇l = ∇f(x)
      std::cout << "Your derivative: " << ++∇l.begin()->A(1,2);

Easy.  Or maybe we had

      Foo<Real> f(list<vec<Real>> x)
      Foo<list<vec<Real>>> ∇f(list<vec<Real>> x)

Also easy.


##### Unification
[unification]: 

Matching this to our generic dot, we can only do it if `Container` is 
`mat`

Tricky case 1:

      set<Foo<Real>> f(list<vec<Real>> x)
      set<Foo<list<vec<Real>>>> ∇f(list<vec<Real>> x)

      list<vec<Real>> g(mat<Real> x)
      list<vec<mat<Real>>> ∇g(mat<Real> x)

      set<Foo<Real>> h(mat<Real> x) { 
        return f(g(x)) 
      }
      set<Foo<mat<Real>>> ∇h(mat<Real> x) { 
        return dot(∇f(g(x)), ∇g(x), g);
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
Identity<Vec<Real,N>> ∇f(Vec<Real,N>)
i.e.
Vec<Real,N> ∇f(Vec<Real,N>)
as required.

Now, try
Vec<Real,M> f(Vec<Real,N>)
it has derivative
Vec<Vec<Real,N>,M> ∇f(Vec<Real,N>)
so Vec<Vec<>> is the Jacobian.  As written this implies jagged storage for non-fixed-size vectors,
but we can specialize Vec<Vec<>> to act like a matrix, so don't fret.

Now the case that normally trips up the casual differentiator:
Mat<Real,M,N> f(Vec<Real,D>)
has derivative
Mat<Vec<Real,D>,M,N> ∇f(Vec<Real,D>)
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
We can see the datatype of ∇h easily as above:
Container1<T2<Real>> ∇h(T2<Real> x)
But what's in the function body?
{
Container1<T1<Real>> gradf = ∇f(g(x));
T1<T2<Real>> gradg = ∇g(x);
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

