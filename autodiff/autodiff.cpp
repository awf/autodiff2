/*
Basic datastructure chain rule:
Container<Real> f(T<Real>);
Has derivative
Container<T<Real>> ∇f(T<Real>);

Now, C++ can't yet match Container to nested types, so we'll have to hack it, but for now
let's pretend it can match X<Real> like this:
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

And now for something exotic.  We have some arbitrary struct
template <class R> struct Foo {
Matrix<R,3,3> A;
Vec<R,3> b;
}
and a function
list<Real> f(Foo<Real> x)
What's its derivative?  Same as above:
list<Foo<Real>> ∇f(Foo<Real> x)
The derivative of the second entry of the list with respect to the (1,2) element
of x.A is just ++l.begin()->A(1,2)

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



*/

#include <cmath>

template <typename T>
struct numeric_traits {
	static T zeros_of_shape(T) {
		return T(0);
	}
};

template <class T>
struct Vec {
	typedef T element_type;

	Vec(size_t = 0);
	Vec(T, ...);
	size_t size() const;
	T& operator[](size_t);

	Vec<T>& operator+=(Vec<T> const&);

	T* begin();
	T* end();
	T const* begin() const;
	T const* end() const;
};

template <typename T>
struct numeric_traits<Vec<T>> {
	template <class U>
	static Vec<T> zeros_of_shape(Vec<U> a) {
		size_t i = a.size();
		Vec<T> ret(i);
		while (--i) ret[i] = numeric_traits<T>::zeros_of_shape(ret[i]);
		return ret;
	}
};

template <>
struct Vec<void> {
	Vec() {}
	Vec(size_t) {}
};

template <class T>
struct Mat /* : public Vec<Vec<T>> */ {
	typedef T element_type;

	Mat(size_t, size_t) {}
	Mat(Vec<T>) {}
	Mat(Vec<T>, Vec<T>) {}
	Mat(Vec<T>, Vec<T>, Vec<T> ...) {}
	static Mat<T> Id(size_t) {}

	// Linear access
	size_t size() const;
	T& operator[](size_t i) { return p[i]; }

	T* p;

	T* begin();
	T* end();
	T const* begin() const;
	T const* end() const;
	Mat<T>& operator+=(Mat<T>);
};

template <typename T>
struct numeric_traits<Mat<T>> {
	template <typename U>
	static Mat<T> zeros_of_shape(Mat<U> m) {
		return Mat<T>;
	}
};

template <typename... Ts> struct tuple;

template <>
struct tuple<> {
};

template <typename T, typename... Ts>
struct tuple<T, Ts...> {
	T head;
	tuple<Ts...> tail;

	tuple() {}

	/* Doh.  This doesn't work -- T is different for the tail.head
	T& operator[](int i) { if (i == 0) return head; else return tail[i - 1]; }  */

	T& first() { return head; }
	//auto second()->decltype(tail.head&) { return tail.head; }
};

template <class T> Vec<T> operator-(Vec<T>, Vec<T>) {}
template <class T> Vec<T> operator+(Vec<T>, Vec<T>) {}
template <class T> Vec<T> operator*(Mat<T>, Vec<T>) {}
template <class T> Vec<T> operator*(T a, Vec<T> b) { return b; }

template <class T>
Vec<T> operator+(Vec<T> a, Vec<void>) { return a; }
// template <class T> Vec<void> operator+(Vec<T>, Vec<void> b) { return b; }

template <class T>
struct Unit {
	T val;

	Unit(T val) : val(val) {}

	T* begin() { return &val; }
	T const* begin() const { return &val; }
	T* end() { return &val + 1; }
	T const* end() const { return &val + 1; }
};

typedef double R;

#define Vec2 Vec 
#define Vec3 Vec 
#define Vec5 Vec 
#define Mat3x3 Mat

Mat3x3<R> exp2mat(Vec3<R> w);
Mat3x3<Vec3<R>> ∇exp2mat(Vec3<R> w);

Vec3<R> mmul(Mat3x3<R> a, Vec3<R> b) { return b; }
tuple<Vec3<Mat3x3<R>>, Vec3<Vec3<R>>> ∇mmul(Mat3x3<R>, Vec3<R>)
{
	tuple<Vec3<Mat3x3<R>>, Vec3<Vec3<R>>> ret;
	return ret;
}

Vec3<R> mmul(tuple<Mat3x3<R>, Vec3<R>> a) { return mmul(a.head, a.tail.head); }
Vec3<tuple<Mat3x3<R>, Vec3<R>>> ∇mmul(tuple<Mat3x3<R>, Vec3<R>>) {
	Vec3<tuple<Mat3x3<R>, Vec3<R>>> ret;
	return ret;
}

Vec3<Mat3x3<R>>	∇₁mmul(Mat3x3<R> M, Vec3<R> v) { return ∇mmul(M, v).head; }
Vec3<Vec3<R>>	∇₂mmul(Mat3x3<R> M, Vec3<R> v) { return ∇mmul(M, v).tail.head; }

//tuple<T,U> make_tuple(T<R>, U<R>) {}
//tuple<T<T<R>>,U<U<R>>> grad1_make_tuple(T<R>, U<R>) {}

Vec3<R> b() { return{ 1, 2, 3 }; }
Vec3<void> ∇b() { return Vec3<void>(0); }

// Dot function for general containers.
template <template <typename X> class Dottee>
struct Dot {

	template <template <typename AX> class Container1, typename AT, typename BT>
	Container1<BT> operator()(Container1<Dottee<AT>> const& a, Dottee<BT> const& b) {
		// Assert Dottee_of_X is indeed a Dottee...
		typedef decltype(AT()*BT()) ret_t;
		Container1<BT> ret = numeric_traits<Container1<BT>>::zeros_of_shape(*a.begin());

		auto ap = a.begin();
		auto retp = ret.begin();
		for (; retp != ret.end(); ++retp, ++ap) {
			Dottee<AT> const& Ai = *ap;
			auto aip = Ai.begin();
			auto bp = b.begin();
			while (bp != b.end())
				*retp += *aip++ * *bp++;
		}

		return ret;
	}

	
	template <typename AT, typename BT>
	auto operator()(Dottee<AT> const& a, Dottee<BT> const& b) -> decltype(AT()*BT()) {
		typedef decltype(AT()*BT()) ret_t;
		ret_t ret = numeric_traits<ret_t>::zeros_of_shape(*a.begin());

		auto ap = a.begin();
		auto bp = b.begin();
		while (bp != b.end())
			ret += *ap++ * *bp++;

		return ret;
	}

};

template <class T>
using Vec_Vec = Vec<Vec<T>>;

void f() {
	Vec<float> a;
	Vec<double> b;
	Dot<Vec>()(a, b);

	Vec<Vec<R>> c;
	Dot<Vec>()(c, b);

	Vec<Vec<Vec<R>>> d;
	Dot<Vec>()(d, d);
	
	/*
	This can't work because Vec_Vec doesn't have a vectorizing begin(), end().
	Dot<Vec_Vec>()(d, d);
	*/
}
#if 0

template <template <typename X> class Dottee, template <typename X> class Container1, typename AT, typename BT>
Container1<BT> DOT(Container1<Dottee<AT>> const& A, Dottee<BT> const& B)  {
}

template <template <typename X> class Dottee, template <typename X> class Container1, typename AT>
Container1<void> DOT(Container1<Dottee<AT>> const& A, Dottee<void> const& B)  {
	return Container1<void>();
}

// Dot function for nontrivial Container1, Container2
//template <template <typename X> class Dottee, template <typename X> class Container1, template <typename X> class Container2, typename T>
//Container1<Container2<T>> DOTCC(Container1<Dottee<T>> const& A, Dottee<Container2<T>> const& B)  {
//	typedef Container2::element_type V; // Assert V == T
//	Container1<Container2<T>> ret;
//
//	auto retp = ret.begin();
//	const auto in1p = A.begin();
//	for (; retp != ret.end(); ++retp, ++in1p) {
//		Dottee<T> const& Ai = *in1p;
//
//		auto dottee1p = Ai.begin();
//		auto dottee2p = B.begin();
//		*retp = Container2::Zero;
//		while (dottee2p != B.end()) {
//			*retp += DOT(*dottee1p, *dottee2p);
//			++dottee1p;
//			++dottee2p;
//		}
//	}
//
//	return ret;
//}

// Dot function for the case where Container1 is the Unit container.
template <template <typename X> class Dottee, typename AT, typename BT>
BT DOT(Dottee<AT> const& A, Dottee<BT> const& B)
{
	BT ret = numeric_traits<BT>::zeros_of_shape(*B.begin());

	for (auto aip = A.begin(); aip != A.end(); ++aip)
	for (auto bp = B.begin(); bp != B.end(); ++bp)
		ret += DOT(*aip, *bp);

	return ret;
}

// 	Container1<Container2<T>> dot(Container1<Dottee<T>> a, Dottee<Container2<T>> b):
//  matching Identity1<Identity3<R>> dot(Id1<Id2<R>>, Id2<Id3<R>>)
R DOT(R a, R b)
{
	return a * b;
}

Vec3<R> v(1, 2, 3);
Vec<Vec<R>> a = DOT(v, v);

Vec3<R> f(Vec3<R> a) {
	auto Rot = exp2mat(a);
	return mmul(Rot, b());
}

Vec3<Vec3<R>> ∇f(Vec3<R> a) {
	auto Rot = exp2mat(a);
	Mat3x3<Vec3<R>> ∇Rot = ∇exp2mat(a);

	auto f = mmul(Rot, b());
	return DOT(∇₁mmul(Rot, b()), ∇Rot) + DOT<Vec, Vec, R>(∇₂mmul(Rot, b()), ∇b());
}

R sqr(R a) { return a*a; }

Vec2<R> pi(Vec3<R> X)
{
	Vec2<R> ret(2u);
	ret[0] = X[0] / X[2];
	ret[1] = X[1] / X[2];
	return ret;
}

Vec3<Vec3<R>> ∇pi(Vec3<R> X)
{
	Vec<Vec3<R>> ret(2u);
	//	ret[0] = { 1 / X[2], 0, -X[0] / sqr(X[2]) };
	ret[1] = { 0, 1 / X[2], -X[0] / sqr(X[2]) };
	return ret;
}

#if 0
Mat3x3<R> exp2mat(Vec3<R> w)
{
	double w1 = w[0];
	double w2 = w[1];
	double w3 = w[2];
	double t1 = w1*w1;
	double t2 = w2*w2;
	double t3 = w3*w3;
	double t4 = t1 + t2 + t3;
	if (t4 == 0) {
		return Mat3x3<R>::Id(3);
	}
	double t5 = std::sqrt(t4);
	double t6 = std::cos(t5);
	double t14 = std::sin(t5);
	double t7 = 1.0 - t6;
	double t8 = 1 / t4;
	double t9 = t3*t8;
	double t10 = t2*t8;
	double t16 = 1 / t5;
	double t17 = t14*w3*t16;
	double t19 = t8*w1;
	double t20 = t7*w2*t19;
	double t23 = t14*w2*t16;
	double t24 = t7*w3;
	double t25 = t24*t19;
	double t28 = t1*t8;
	double t33 = t14*w1*t16;
	double t35 = t24*t8*w2;
	return{
		{ 1.0 + t7*(-t9 - t10), -t17 + t20, t23 + t25 },
		{ t17 + t20, 1.0 + t7*(-t9 - t28), -t33 + t35 },
		{ -t23 + t25, t33 + t35, 1.0 + t7*(-t10 - t28) }
	};
}

Mat3x3<Vec3<R>> ∇exp2mat(Vec3<R> w)
{
	//... some stuff
}


Vec2<R> project(Vec3<R> rotation, Vec3<R> translation, Vec3<R> X, Vec5<R> kappa) {
	Mat3x3<R> Rot = exp2mat(rotation);
	R f = kappa[0];
	R cx = kappa[1];
	R cy = kappa[2];
	R k1 = kappa[3];
	R k2 = kappa[4];
	Mat3x3<R> K = { { f, 0, cx }, { 0, f, cy }, { 0, 0, 1 } };
	Vec2<R> p = pi(K*(Rot*X + translation));
}

Vec3<Vec3<R>> ∇(Vec3<R> x)
{
	return{ Vec3<R> { 1, 0, 0 }, Vec3<R> { 0, 1, 0 }, Vec3<R> { 0, 0, 1 } };
}

Vec2<tuple<Vec3<R>, Vec3<R>, Vec3<R>, Vec<R>>> ∇project(Vec3<R> rotation, Vec3<R> translation, Vec3<R> X, Vec<R> kappa) {
	Mat3x3<R> Rot = exp2mat(rotation);
	auto ∇Rot = ∇exp2mat(rotation);
	R f = kappa[0];
	R cx = kappa[1];
	R cy = kappa[2];
	R k1 = kappa[3];
	R k2 = kappa[4];
	Vec<R> ef = { 1, 0, 0, 0, 0 };
	Vec<R> ecx = { 0, 1, 0, 0, 0 };
	Vec<R> ecy = { 0, 0, 1, 0, 0 };
	Vec<R> ek1 = { 0, 0, 0, 1, 0 };
	Vec<R> ek2 = { 0, 0, 0, 0, 1 };
	Vec<R> e0 = Vec<R>::Zero;
	Mat3x3<R> K = { { f, 0, cx }, { 0, f, cy }, { 0, 0, 1 } };
	Mat3x3<Vec<R>> ∇K = { { ef, e0, ecx }, { e0, ef, ecy }, { e0, e0, e0 } };

	Vec3<R> xcam = mmul(Rot, X) + translation;
	auto ∇X = ∇(X);

	auto ∇xcam = DOT(∇₁mmul(Rot, X), ∇Rot) + DOT(∇₂mmul(Rot, X), ∇X);

	Vec3<R> xhomg = mmul(K, xcam);
	auto ∇xhomg = DOT(∇₁mmul(K, xcam), ∇K) + DOT(∇₂mmul(K, xcam), ∇xcam);

	Vec2<R> p = pi(xhomg);
	Vec2<Vec3<R>> dpdR = DOT(∇pi(xhomg), ∇xhomg);
}

Vec<Vec2<R>> residuals(Vec<Vec3<R>> rotations, Vec<Vec3<R>> translations, Vec<Vec3<R>> Xs, Vec<R> kappas,
	Vec<Vec2<R>> ms, Vec<int> frames, Vec<int> points)
{
	int nR = ms.size();
	Vec<Vec2<R>> ret(nR);
	for (int i = 0; i < ms.size(); ++i) {
		int f = frames[i];
		int p = points[i];
		ret[i] = project(rotations[f], translations[f], Xs[p], kappas) - ms[i];
	}
}



/**/
#endif
#endif

int main(int argc, char* argv[])
{
	return 0;
}

