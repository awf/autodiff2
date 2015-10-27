
#include <cmath>
#include <cassert>
#include <iostream>
#include <algorithm>
#include <vector>
#include <iterator>

#include "Vec.h"
#include "dot.h"

typedef double Real;

#define DECLARE_CONTAINER(Name)\
template <class T> struct Name : public Vec<T, 3> {\
  Name() {};\
  template <class U>\
  explicit Name(U const& that) : Vec<T, 3>(that) {}\
\
  template <class U>\
  Name& operator=(U const& that) { Vec<T, 3>::operator=(that); return *this; }\
};

DECLARE_CONTAINER(Bee)
DECLARE_CONTAINER(Cee)
DECLARE_CONTAINER(Dee)
DECLARE_CONTAINER(Eee)
DECLARE_CONTAINER(Foo)
DECLARE_CONTAINER(Gar)

#include <boost/range/counting_range.hpp>
auto inds = boost::counting_range<int>(0, 3);

static double fill_value;
template <class Container>
void do_fill_inc(Container* c) {
  for (auto& pc : *c)
    do_fill_inc(&pc);
  fill_value += 1;
}

template <>
void do_fill_inc(Real* c) {
  *c = fill_value;
  fill_value += .1;
}


void test_dotter_1()
{
  // Compare dot to handwritten vector one
  {
    Vec<double, 3> a = vec(7, 2, 3);
    Vec<double, 3> b = vec(5, 11, 13);
    double d1 = Dotter<0, 1>::dot_inferring(a, b);
    std::cout << "VECDOT: " << a << "." << b << "=" << d1;
    assert(d1 == dot(a, b));
    std::cout << ". OK\n";
  }

  // Jagged jonnies
  {
    Vec<Vec<Real, 3>, 2> a = vec( vec(7, 2, 3), vec(17, 23, 31) );
    Vec<Vec<Real, 3>, 2> b = vec( vec(43, 11, 5), vec(19, 29, 37) );
    double d1 = Dotter<0, 2>::dot_inferring(a, b);
    std::cout << "VECDOT1: " << a << "." << b << "=" << d1;

    double d_gt = dot(flatten(a), flatten(b));

    assert(d1 == d_gt);
    std::cout << ". OK\n";

    dot_inferring_helper<Vec<Vec<Real, 3>, 2>, Vec<Vec<Real, 3>, 2>, Real> dih;
    BOOST_STATIC_ASSERT(dih.C1_depth == 0);
    BOOST_STATIC_ASSERT(dih.C2_depth == 2);

    Real d2 = dot_inferring(a, b, b[0][0]);
    std::cout << "VECDOT2: =" << d2;

    assert(d2 == d_gt);
    std::cout << ". OK\n";
  }

  // Dot of
  Foo< Bee<Cee<Real>> > grad_f;
  Bee<Cee< Dee<Real> >> grad_g;
  // when we know the container over which we must multiply-accumulate is the Bee<Cee>.
  // The output will be a...
  Foo< Dee<Real> > out;
  deep_fill(&out, Real{ 0 });
  // So the dotting will ultimately involve products Real*Dee<Eee<Real>>

  // First fill the containers.
  fill_value = 0;  do_fill_inc(&grad_f);
  fill_value = -20;  do_fill_inc(&grad_g);

  std::cout << "DOT:\n";
  std::cout << "A = " << grad_f << "\n";
  std::cout << "B = " << grad_g << "\n";

  // Declare the dotter.  First arg is depth of C1 in grad_f, second is depth of C2.
  Dotter<1, 2>::dot(grad_f, grad_g, &out);

  std::cout << "DOT1 = " << out << std::endl;

  // Inferred dotter.  First arg is depth of C1 in grad_f, second is depth of C2.
  auto out0a = Dotter<1, 2>::dot_inferring(grad_f, grad_g);
  Foo< Dee<Real> > out0 = Foo< Dee<Real> >{ out0a };
  std::cout << "INFER. = " << out0 << std::endl;

  // Compare to hand-coded
  Foo< Dee<Real> > out2; 
  deep_fill(&out2, Real{ 0 });

  for (int i : inds)
    for (int j : inds)
      for (int k : inds)
        out2[i] += grad_f[i][j][k] * grad_g[j][k];

  std::cout << "DOT0 = " << out2 << std::endl;

}

void test_dotter()
{
  // Dot of
  Foo<Gar< Bee<Cee<Real>> >> grad_f;
  Bee<Cee< Dee<Eee<Real>> >> grad_g;
  // when we know the container over which we must multiply-accumulate is the Bee<Cee>.
  // The output will be a...
  Foo<Gar< Dee<Eee<Real>> >> out;
  deep_fill(&out, Real{ 0 });
  // So the dotting will ultimately involve products Real*Dee<Eee<Real>>

  // First fill the containers.
  fill_value = 0;  do_fill_inc(&grad_f);
  fill_value = -20;  do_fill_inc(&grad_g);

  std::cout << "DOT:\n";
  std::cout << "A = " << grad_f << "\n";
  std::cout << "B = " << grad_g << "\n";

  // Declare the dotter.
  Dotter<2, 2>::dot(grad_f, grad_g, &out);

  std::cout << "DOT = " << out << std::endl;
}


int main(int argc, char* argv[])
{
  auto v123 = vec(1., 2., 3.);
  auto v357 = vec(3., 5., 7.);
  auto v713 = vec(7., 11., 13.);

  Vec<Vec<Real, 3>, 3> a = vec(v123, v713, v357);
  Vec<Vec<Real, 3>, 3> b = vec(v123, v713, v123);

  std::cout << pr(a) << std::endl;
  
  test_dotter_1();

  Real c = 0;
  Vec<Vec<Real, 3>, 3> vvc = Zeros(3);
  /*  Dotter<2, 0>::dot(a, 2.0, &vvc);

  Vec<Real,3> vc = Zeros(3);
  Dotter<1, 1>::dot(a, b, &vvc);

  Foo<Gar<Bee<Cee<Real>>>> a5;
  Bee<Cee<Dee<Eee<Real>>>> b6;
  Foo<Gar<Dee<Eee<Real>>>> fb = dot22(a5, b6);

  Foo<Gar<Dee<Eee<Real>>>> fb2;
  Dotter<2,2>::dot(a5, b6, &fb2);

  /*
  Vec3<R> rotation = vec<R>(1,-2,3);
  Vec3<R> translation = vec<R>(11, 12, 13);
  Vec3<R> X = vec<R>(.1, .3, .5);
  Vec<R> kappa = vec<R>(1.4, 0.01, 0.02, 0, 0);

  Vec2<R> p = project(rotation, translation, X, kappa);

  auto ∇p = ∇project(rotation, translation, X, kappa);
  */
  return 0;
}

#if 0


template <class A, class B>
auto dot00(A const& a, B const& b) -> decltype(A()*B())
{
}

template <class B>
B dot00(Real const& a, B const& b)
{
  return B(a*b);
}

Cee<Dee<Eee<Real>>> cde;
auto a1 = dot00(Real(), cde[0]);

template <class DE>
DE dot01(Cee<Real> const& a, Cee<DE> const& b)
{
  DE out;
  for (int i : inds)
    out += dot00(a[i], b[i]);
  return out;
}

auto a2 = dot01(Cee<Real>(), Cee<Dee<Eee<Real>>>());

template <class C, class CDE>
auto dot02(Bee<C> const& a, Bee<CDE> const& b)-> decltype(dot01(a[0], b[0]))
{
  typedef decltype(dot01(a[0], b[0])) elt_t;
  elt_t out;
  for (int i : inds)
    out += dot01(a[i], b[i]);
  return out;
}

Bee<Cee<Real>> bc;
Bee<Cee<Dee<Eee<Real>>>> bcde;
auto a3 = dot02(bc, bcde);

template <class BC, class CDE>
auto dot12(Gar<BC> const& a, Bee<CDE> const& b)->Gar<decltype(dot02(a[0],b))>
{
  typedef decltype(dot02(a[0], b)) elt_t;
  Gar<elt_t> out;
  for (int i : inds)
    out[i] = dot02(a[i], b);
  return out;
}

Gar<Dee<Eee<Real>>> dot(Gar<Bee<Cee<Real>>> const& a, Bee<Cee<Dee<Eee<Real>>>> const& b)
{
  return dot12<Bee<Cee<Real>>, Cee<Dee<Eee<Real>>>>(a, b);
}

template <class ABC, class CDE>
auto dot22(Foo<ABC> const& a, Bee<CDE> const& b)->Foo<decltype(dot12(a[0],b))>
{
  typedef decltype(dot12(a[0], b)) elt_t;
  Foo<elt_t> out;
  for (int i : inds)
    out[i] = dot12(a[i], b);
  return out;
}


#if 0
Foo<Gar<Real>> f(Bee<Cee<Real>>);
Foo<Gar<Bee<Cee<Real>>>> ∇f(Bee<Cee<Real>>);

Bee<Cee<Real>> g(Dee<Eee<Real>> x);
Bee<Cee<Dee<Eee<Real>>>> ∇g(Dee<Eee<Real>> x);

Foo<Gar<Real>> h(Dee<Eee<Real>> x) 
{ 
  return f(g(x));
}

Foo<Gar<Dee<Eee<Real>>>> ∇h(Dee<Eee<Real>> x)
{
  return dot22(∇f(g(x)), ∇g(x));
}

void test()
{
  ∇h(Dee<Eee<Real>>());
}

#endif

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
  typedef void value_type;

	Vec() {}
	Vec(size_t) {}
};

template <class T>
struct Mat /* : public Vec<Vec<T>> */ {
	typedef T element_type;

	Mat() {}
	Mat(Zeros_t) {}
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

	tuple(){}
	tuple(T head, Ts... tail):head(head), tail(tail) {}

	/* Doh.  This doesn't work -- T is different for the tail.head
	T& operator[](int i) { if (i == 0) return head; else return tail[i - 1]; }  */

	T& first() { return head; }
	//auto second()->decltype(tail.head&) { return tail.head; }
};

template <typename... Ts>
tuple<Ts...> make_tuple(const Ts&... ts) {
	return tuple<Ts...>(ts...);
}
//tuple<T<R>,U<R>> make_tuple(T<R>, U<R>) {}
//tuple<T<T<R>>,U<U<R>>> grad1_make_tuple(T<R>, U<R>) {}

//---------------------------------------------------------------------------------


template <class T>
struct Unit {
	T val;

	Unit(T val) : val(val) {}

	T* begin() { return &val; }
	T const* begin() const { return &val; }
	T* end() { return &val + 1; }
	T const* end() const { return &val + 1; }
};


#if 0

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


Vec3<R> b() { return vec<R>( 1, 2, 3 ); }
Vec3<void> ∇b() { return Vec3<void>(0); }

// Dot function for general containers.
template <template <typename X> class Dottee>
struct Dot {

	template <template <typename AX> class Container1, typename AT, typename BT>
	Container1<BT> operator()(Container1<Dottee<AT>> const& a, Dottee<BT> const& b) {
		// Assert Dottee_of_X is indeed a Dottee...
		Container1<BT> ret = numeric_traits<Container1<BT>>::zeros_of_shape(a);

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
//	Dot<Vec>()(d, d);
	
	/*
	This can't work because Vec_Vec doesn't have a vectorizing begin(), end().
	Dot<Vec_Vec>()(d, d);
	*/
}

template <template <typename Dottee_A1> class Container1, template <typename BX> class Dottee, class AT, class BT>
Container1<BT> DOT(Container1<Dottee<AT>> const& a, Dottee<BT> const& b) {
	return Dot<Dottee>()(a, b);
}

template <template <typename Dottee_A1> class Container1, template <typename BX> class Dottee, class AT>
Container1<void> DOT(Container1<Dottee<AT>> const& a, Dottee<void> const& b) {
	return Container1<void>();
}

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

Vec2<R> pi(Vec3<R> const& X)
{
	Vec2<R> ret(2u);
	ret[0] = X[0] / X[2];
	ret[1] = X[1] / X[2];
	return ret;
}

Vec3<Vec3<R>> ∇pi(Vec3<R> const& X)
{
	Vec<Vec3<R>> ret(2);
	R x = X[0];
	R y = X[1];
	R z = X[2];
	R sz = 1 / z;
	R szz = sz*sz;

	ret[0] = vec<R>(sz,  0, -x * szz);
	ret[1] = vec<R>( 0, sz, -y * szz);
	return ret;
}

Mat3x3<R> exp2mat(Vec3<R> w)
{
	double x1 = w[0];
	double x2 = w[1];
	double x3 = w[2];

	double t2 = x2*x2;
	double t3 = x1*x1;
	double t4 = x3*x3;
	double t5 = t2 + t3 + t4;
	double t6 = 1.0 / t5;
	double t7 = std::sqrt(t5);
	double t8 = std::cos(t7);
	double t9 = t8 - 1.0;
	double t10 = std::sin(t7);
	double t11 = 1.0 / t7;
	double t12 = t10*t11*x3;
	double t13 = t4*t6;
	double t14 = t10*t11*x1;
	double t15 = t3*t6;
	double t16 = t2*t6;
	double t17 = t6*t6;
	double t18 = t13 + t16;
	double t19 = t11*t11*t11;
	double t20 = t6*t8*x1*x3;
	double t21 = t3*t10*t19*x2;
	double t22 = t3*t9*t17*x2*2.0;
	double t23 = t4*t17*x1*2.0;
	double t24 = t13 + t15;
	double t25 = t10*t19*x1*x2;
	double t26 = t3*t10*t19*x3;
	double t27 = t3*t9*t17*x3*2.0;
	double t28 = t10*t11;
	double t29 = t3*t6*t8;
	double t30 = t9*t17*x1*x2*x3*2.0;
	double t31 = t10*t19*x1*x2*x3;
	double t32 = t3*t17*x1*2.0;
	double t33 = t2*t17*x1*2.0;
	double t34 = t15 + t16;
	double t35 = t6*t8*x2*x3;
	
	return Mat3x3<R>(
		vec<R>(t9*t18 + 1.0, t12 - t6*t9*x1*x2, -t10*t11*x2 - t6*t9*x1*x3),
		vec<R>(-t12 - t6*t9*x1*x2, t9*t24 + 1.0, t14 - t6*t9*x2*x3),
		vec<R>(t10*t11*x2 - t6*t9*x1*x3, -t14 - t6*t9*x2*x3, t9*t34 + 1.0)
		);
}

Mat3x3<Vec3<R>> ∇exp2mat(Vec3<R> w)
{
	double x1 = w[0];
	double x2 = w[1];
	double x3 = w[2];

	double t2 = x2*x2;
	double t3 = x1*x1;
	double t4 = x3*x3;
	double t5 = t2 + t3 + t4;
	double t6 = 1.0 / t5;
	double t7 = std::sqrt(t5);
	double t8 = std::cos(t7);
	double t9 = t8 - 1.0;
	double t10 = std::sin(t7);
	double t11 = 1.0 / t7;
	double t12 = t10*t11*x3;
	double t13 = t4*t6;
	double t14 = t10*t11*x1;
	double t15 = t3*t6;
	double t16 = t2*t6;
	double t17 = t6*t6;
	double t18 = t13 + t16;
	double t19 = t11*t11*t11;
	double t20 = t6*t8*x1*x3;
	double t21 = t3*t10*t19*x2;
	double t22 = t3*t9*t17*x2*2.0;
	double t23 = t4*t17*x1*2.0;
	double t24 = t13 + t15;
	double t25 = t10*t19*x1*x2;
	double t26 = t3*t10*t19*x3;
	double t27 = t3*t9*t17*x3*2.0;
	double t28 = t10*t11;
	double t29 = t3*t6*t8;
	double t30 = t9*t17*x1*x2*x3*2.0;
	double t31 = t10*t19*x1*x2*x3;
	double t32 = t3*t17*x1*2.0;
	double t33 = t2*t17*x1*2.0;
	double t34 = t15 + t16;
	double t35 = t6*t8*x2*x3; 
	double t36 = t2*t10*t19*x1;
	double t37 = t2*t9*t17*x1*2.0;
	double t38 = t4*t17*x2*2.0;
	double t39 = t6*t8*x1*x2;
	double t40 = t2*t10*t19;
	double t41 = t2*t10*t19*x3;
	double t42 = t2*t9*t17*x3*2.0;
	double t43 = t2*t17*x2*2.0;
	double t44 = t3*t17*x2*2.0;
	double t45 = t10*t19*x2*x3;
	double t46 = t4*t6*t8;
	double t47 = t4*t17*x3*2.0;
	double t48 = t10*t19*x1*x3;
	double t49 = t4*t10*t19*x1;
	double t50 = t4*t9*t17*x1*2.0;
	double t51 = t4*t10*t19*x2;
	double t52 = t4*t9*t17*x2*2.0;
	double t53 = t3*t17*x3*2.0;
	double t54 = t2*t17*x3*2.0;

	Mat3x3<Vec3<R>> ret(Zeros());
	auto p = ret.begin();

	(*p)[0] = -t9*(t23 + t33) - t10*t11*t18*x1;
	(*p)[1] = t20 + t21 + t22 - t6*t9*x2 - t10*t19*x1*x3;
	(*p)[2] = t25 + t26 + t27 - t6*t9*x3 - t6*t8*x1*x2;
	++p;
	(*p)[0] = -t20 + t21 + t22 + t48 - t6*t9*x2;
	(*p)[1] = -t9*(t23 + t32 - t6*x1*2.0) - t10*t11*t24*x1;
	(*p)[2] = t28 + t29 + t30 + t31 - t3*t10*t19;
	++p;
	(*p)[0] = -t25 + t26 + t27 + t39 - t6*t9*x3;
	(*p)[1] = -t28 - t29 + t30 + t31 + t3*t10*t19;
	(*p)[2] = -t9*(t32 + t33 - t6*x1*2.0) - t10*t11*t34*x1;
	++p;
	(*p)[0] = -t9*(t38 + t43 - t6*x2*2.0) - t10*t11*t18*x2;
	(*p)[1] = t35 + t36 + t37 - t6*t9*x1 - t10*t19*x2*x3;
	(*p)[2] = -t28 + t30 + t31 + t40 - t2*t6*t8;
	++p;
	(*p)[0] = -t35 + t36 + t37 + t45 - t6*t9*x1;
	(*p)[1] = -t9*(t38 + t44) - t10*t11*t24*x2;
	(*p)[2] = -t25 + t39 + t41 + t42 - t6*t9*x3;
	++p;
	(*p)[0] = t28 + t30 + t31 - t40 + t2*t6*t8;
	(*p)[1] = t25 - t39 + t41 + t42 - t6*t9*x3;
	(*p)[2] = -t9*(t43 + t44 - t6*x2*2.0) - t10*t11*t34*x2;
	++p;
	(*p)[0] = -t9*(t47 + t54 - t6*x3*2.0) - t10*t11*t18*x3;
	(*p)[1] = t28 + t30 + t31 + t46 - t4*t10*t19;
	(*p)[2] = -t35 + t45 + t49 + t50 - t6*t9*x1;
	++p;
	(*p)[0] = -t28 + t30 + t31 - t46 + t4*t10*t19;
	(*p)[1] = -t9*(t47 + t53 - t6*x3*2.0) - t10*t11*t24*x3;
	(*p)[2] = t20 - t48 + t51 + t52 - t6*t9*x2;
	++p;
	(*p)[0] = t35 - t45 + t49 + t50 - t6*t9*x1;
	(*p)[1] = -t20 + t48 + t51 + t52 - t6*t9*x2;
	(*p)[2] = -t9*(t53 + t54) - t10*t11*t34*x3;
	
	return ret;
}

Vec<Vec<R>> ∇(Vec<R> const& x)
{
	Vec<Vec<R>> ret = numeric_traits<Vec<Vec<R>>>::zeros_of_shape(x);
	for (size_t i = 0; i < x.size(); ++i)
		ret[i][i] = 1;
	return ret;
}


Vec2<R> project(Vec3<R> rotation, Vec3<R> translation, Vec3<R> X, Vec5<R> kappa) {
	Mat3x3<R> Rot = exp2mat(rotation);
	R f = kappa[0];
	R cx = kappa[1];
	R cy = kappa[2];
	R k1 = kappa[3];
	R k2 = kappa[4];
	Mat3x3<R> K = Mat3x3<R>(
		vec<R>(f, 0, cx),
		vec<R>(0, f, cy),
		vec<R>(0, 0, 1));
	// ICE:	Mat3x3<R> K = { { f, 0, cx }, { 0, f, cy }, { 0, 0, 1 } };
	Vec2<R> p = pi(mmul(K, mmul(Rot, X) + translation));

	return p;
}

tuple < Vec2<Vec3<R>>, Vec2<Vec3<R>>, Vec2<Vec3<R>>, Vec2<Vec<R>> > ∇project(Vec3<R> rotation, Vec3<R> translation, Vec3<R> X, Vec<R> kappa) {
	auto ∇rotation = ∇(rotation);
	auto ∇translation = ∇(translation);
	auto ∇X = ∇(X);
	auto ∇kappa = ∇(kappa);

	Mat3x3<R> Rot = exp2mat(rotation);
	auto ∇Rot = ∇exp2mat(rotation);

	R f = kappa[0];
	auto ∇f = ∇kappa[0];  // ∇index(kappa,0)
	R cx = kappa[1];
	auto ∇cx = ∇kappa[1];
	R cy = kappa[2];
	auto ∇cy = ∇kappa[2];
	R k1 = kappa[3];
	auto ∇k1 = ∇kappa[3];
	R k2 = kappa[4];
	auto ∇k2 = ∇kappa[4];
	Vec<R> e0 = numeric_traits<Vec<R>>::zeros_of_shape(∇f);
	Mat3x3<R> K = Mat3x3<R>(
		vec<R>(f, 0, cx),
		vec<R>(0, f, cy),
		vec<R>(0, 0, 1));
	Mat3x3<Vec<R>> ∇K = Mat3x3<Vec<R>>(
		vec<Vec<R>>(∇f, e0, ∇cx),
		vec<Vec<R>>(e0, ∇f, ∇cy),
		vec<Vec<R>>(e0, e0, e0));

	Vec3<R> xcam = mmul(Rot, X) + translation;

	auto ∇_Rot_xcam = DOT(∇₁mmul(Rot, X), ∇Rot);
	auto ∇_X_xcam = DOT(∇₂mmul(Rot, X), ∇X);
	auto ∇_translation_xcam = ∇translation;

	Vec3<R> xhomg = mmul(K, xcam);
	// ∇xhomg = DOT(∇₁mmul(K, xcam), ∇K) + DOT(∇₂mmul(K, xcam), ∇xcam);
	auto ∇_K_xhomg = DOT(∇₁mmul(K, xcam), ∇K);
	auto ∇_Rot_xhomg = DOT(∇₂mmul(K, xcam), ∇_Rot_xcam);
	auto ∇_X_xhomg = DOT(∇₂mmul(K, xcam), ∇_X_xcam);
	auto ∇_translation_xhomg = DOT(∇₂mmul(K, xcam), ∇_translation_xcam);

	Vec2<R> p = pi(xhomg);
	auto ∇_K_p = DOT(∇pi(xhomg), ∇_K_xhomg);
	auto ∇_Rot_p = DOT(∇pi(xhomg), ∇_Rot_xhomg);
	auto ∇_X_p = DOT(∇pi(xhomg), ∇_X_xhomg);
	auto ∇_translation_p = DOT(∇pi(xhomg), ∇_translation_xhomg);

	auto g = make_tuple(∇_Rot_p, ∇_translation_p, ∇_X_p, ∇_K_p);

	return g;
}

Vec<Vec2<R>> residuals(Vec<Vec3<R>> rotations, Vec<Vec3<R>> translations, Vec<Vec3<R>> Xs, Vec<R> kappas,
	Vec<Vec2<R>> ms, Vec<int> frames, Vec<int> points)
{
	int nR = ms.size();
	Vec<Vec2<R>> ret(nR);
	for (size_t i = 0; i < ms.size(); ++i) {
		int f = frames[i];
		int p = points[i];
		ret[i] = project(rotations[f], translations[f], Xs[p], kappas) - ms[i];
	}
	return ret;
}

#endif

#endif
