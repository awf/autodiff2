
#include <cmath>
#include <cassert>
#include <iostream>
#include <algorithm>
#include <vector>
#include <iterator>
#include <functional>

#include "dot.h"
#include "Vec.h"

#include "rodrigues.h"

#if 1

template <class T>
T trace(Mat3x3<T> const& m)
{
  return sum(diag(m));
}

template <class T>
Mat3x3<T> grad_trace(Mat3x3<T> const& m)
{
  Mat3x3<T> out(Zeros());
  for (size_t i = 0; i < m.size(); ++i)
    out[i][i] = 1;
  return out;
}

/*
template <class T>
Identity3x3<T> grad_trace(Mat3x3<T> const& m)
{
  return Identity3x3<T>{};
}
*/

Real f(Vec3<Real> const& x)
{
  return trace(exp2mat(x));
}

Vec3<Real> grad_f(Vec3<Real> const& x)
{
  // f = t(e(x))  ==> ∇f = ∇t(e(x)) "*" ∇e(x)  
  return gdot(grad_trace(exp2mat(x)), grad_exp2mat(x), x);
}

Vec3<Real> grad_finite_difference(std::function<Real (Vec3<Real> const&)> f, Vec3<Real> const& x)
{
  Vec3<Real> grad_fd;
  Real fx = f(x);
  double delta = 1e-6;
  auto xp = x;
  for (size_t i = 0; i < x.size(); ++i) {
    xp[i] += delta;
    grad_fd[i] = (f(xp) - fx) / (xp[i] - x[i]);
    xp[i] = x[i];
  }
  return grad_fd;
}


void test_chain_rule()
{
  Vec3<Real> x = vec(-.5, .2, .3);
  Vec3<Real> grad = grad_f(x);
  std::cout << "GRAD_CR = " << grad << "\n";

  // Finite differences
  Vec3<Real> grad_fd = grad_finite_difference(f, x);
  std::cout << "GRAD_FD = " << grad_fd << "\n";
}


// -------------------  Test gdot with containers
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
    double d1 = Dotter<0, 1, decltype(a), decltype(b)>::dot(a, b);
    std::cout << "VECDOT: " << a << "." << b << "=" << d1;
    assert(d1 == dot(a, b));
    std::cout << ". OK\n";
  }

  // Jagged jonnies
  {
    Vec<Vec<Real, 3>, 2> a = vec( vec(7, 2, 3), vec(17, 23, 31) );
    Vec<Vec<Real, 3>, 2> b = vec( vec(43, 11, 5), vec(19, 29, 37) );
    double d1 = Dotter<0, 2, decltype(a), decltype(b)>::dot(a, b);
    std::cout << "VECDOT1: " << a << "." << b << "=" << d1;

    double d_gt = dot(flatten(a), flatten(b));

    assert(d1 == d_gt);
    std::cout << ". OK\n";

    typedef dot_inferring_helper<Vec<Vec<Real, 3>, 2>, Vec<Vec<Real, 3>, 2>, Real> dih;
    BOOST_STATIC_ASSERT(dih::C1_depth == 0);
    BOOST_STATIC_ASSERT(dih::C2_depth == 2);

    Real d2 = gdot(a, b, b[0][0]);
    std::cout << "VECDOT2: =" << d2;

    assert(d2 == d_gt);
    std::cout << ". OK\n";
  }

  // Dot of
  Dee<Real> x;
  Bee<Cee<Real>> g;
  Bee<Cee< Dee<Real> >> grad_g;

  Foo<Real> f; // f(g)
  Foo< Bee<Cee<Real>> > grad_f;
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
  Dotter<1, 2, decltype(grad_f), decltype(grad_g)>::dot3(grad_f, grad_g, &out);

  std::cout << "DOT1 = " << out << std::endl;

  // Inferred dotter.  First arg is depth of C1 in grad_f, second is depth of C2.
  auto out0a = Dotter<1, 2, decltype(grad_f), decltype(grad_g)>::dot(grad_f, grad_g);
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


int main(int argc, char* argv[])
{
  auto v123 = vec(1., 2., 3.);
  auto v357 = vec(3., 5., 7.);
  auto v713 = vec(7., 11., 13.);

  Vec<Vec<Real, 3>, 3> a = vec(v123, v713, v357);
  Vec<Vec<Real, 3>, 3> b = vec(v123, v713, v123);

  std::cout << pr(a) << std::endl;
  
  test_dotter_1();

  test_chain_rule();

  Real c = 0;
  Vec<Vec<Real, 3>, 3> vvc = Zeros(3);

  /*
  Vec3<R> rotation = vec<R>(1,-2,3);
  Vec3<R> translation = vec<R>(11, 12, 13);
  Vec3<R> X = vec<R>(.1, .3, .5);
  Vec<R> kappa = vec<R>(1.4, 0.01, 0.02, 0, 0);

  Vec2<R> p = project(rotation, translation, X, kappa);

  auto grad_p = grad_project(rotation, translation, X, kappa);
  */
  return 0;
}


#if 0

typedef double R;

#define Vec2 Vec 
#define Vec3 Vec 
#define Vec5 Vec 
#define Mat3x3 Mat

Mat3x3<R> exp2mat(Vec3<R> w);
Mat3x3<Vec3<R>> grad_exp2mat(Vec3<R> w);

Vec3<R> mmul(Mat3x3<R> a, Vec3<R> b) { return b; }
tuple<Vec3<Mat3x3<R>>, Vec3<Vec3<R>>> grad_mmul(Mat3x3<R>, Vec3<R>)
{
	tuple<Vec3<Mat3x3<R>>, Vec3<Vec3<R>>> ret;
	return ret;
}

Vec3<R> mmul(tuple<Mat3x3<R>, Vec3<R>> a) { return mmul(a.head, a.tail.head); }
Vec3<tuple<Mat3x3<R>, Vec3<R>>> grad_mmul(tuple<Mat3x3<R>, Vec3<R>>) {
	Vec3<tuple<Mat3x3<R>, Vec3<R>>> ret;
	return ret;
}

Vec3<Mat3x3<R>>	grad_₁mmul(Mat3x3<R> M, Vec3<R> v) { return grad_mmul(M, v).head; }
Vec3<Vec3<R>>	grad_₂mmul(Mat3x3<R> M, Vec3<R> v) { return grad_mmul(M, v).tail.head; }


Vec3<R> b() { return vec<R>( 1, 2, 3 ); }
Vec3<void> grad_b() { return Vec3<void>(0); }


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


Vec3<R> f(Vec3<R> a) {
	auto Rot = exp2mat(a);
	return mmul(Rot, b());
}

Vec3<Vec3<R>> grad_f(Vec3<R> a) {
	auto Rot = exp2mat(a);
	Mat3x3<Vec3<R>> grad_Rot = grad_exp2mat(a);

	auto f = mmul(Rot, b());
	return DOT(grad_₁mmul(Rot, b()), grad_Rot) + DOT<Vec, Vec, R>(grad_₂mmul(Rot, b()), grad_b());
}

R sqr(R a) { return a*a; }

Vec2<R> pi(Vec3<R> const& X)
{
	Vec2<R> ret(2u);
	ret[0] = X[0] / X[2];
	ret[1] = X[1] / X[2];
	return ret;
}

Vec3<Vec3<R>> grad_pi(Vec3<R> const& X)
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

Vec<Vec<R>> grad_(Vec<R> const& x)
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

tuple < Vec2<Vec3<R>>, Vec2<Vec3<R>>, Vec2<Vec3<R>>, Vec2<Vec<R>> > grad_project(Vec3<R> rotation, Vec3<R> translation, Vec3<R> X, Vec<R> kappa) {
	auto grad_rotation = grad_(rotation);
	auto grad_translation = grad_(translation);
	auto grad_X = grad_(X);
	auto grad_kappa = grad_(kappa);

	Mat3x3<R> Rot = exp2mat(rotation);
	auto grad_Rot = grad_exp2mat(rotation);

	R f = kappa[0];
	auto grad_f = grad_kappa[0];  // grad_index(kappa,0)
	R cx = kappa[1];
	auto grad_cx = grad_kappa[1];
	R cy = kappa[2];
	auto grad_cy = grad_kappa[2];
	R k1 = kappa[3];
	auto grad_k1 = grad_kappa[3];
	R k2 = kappa[4];
	auto grad_k2 = grad_kappa[4];
	Vec<R> e0 = numeric_traits<Vec<R>>::zeros_of_shape(grad_f);
	Mat3x3<R> K = Mat3x3<R>(
		vec<R>(f, 0, cx),
		vec<R>(0, f, cy),
		vec<R>(0, 0, 1));
	Mat3x3<Vec<R>> grad_K = Mat3x3<Vec<R>>(
		vec<Vec<R>>(grad_f, e0, grad_cx),
		vec<Vec<R>>(e0, grad_f, grad_cy),
		vec<Vec<R>>(e0, e0, e0));

	Vec3<R> xcam = mmul(Rot, X) + translation;

	auto grad__Rot_xcam = DOT(grad_₁mmul(Rot, X), grad_Rot);
	auto grad__X_xcam = DOT(grad_₂mmul(Rot, X), grad_X);
	auto grad__translation_xcam = grad_translation;

	Vec3<R> xhomg = mmul(K, xcam);
	// grad_xhomg = DOT(grad_₁mmul(K, xcam), grad_K) + DOT(grad_₂mmul(K, xcam), grad_xcam);
	auto grad__K_xhomg = DOT(grad_₁mmul(K, xcam), grad_K);
	auto grad__Rot_xhomg = DOT(grad_₂mmul(K, xcam), grad__Rot_xcam);
	auto grad__X_xhomg = DOT(grad_₂mmul(K, xcam), grad__X_xcam);
	auto grad__translation_xhomg = DOT(grad_₂mmul(K, xcam), grad__translation_xcam);

	Vec2<R> p = pi(xhomg);
	auto grad__K_p = DOT(grad_pi(xhomg), grad__K_xhomg);
	auto grad__Rot_p = DOT(grad_pi(xhomg), grad__Rot_xhomg);
	auto grad__X_p = DOT(grad_pi(xhomg), grad__X_xhomg);
	auto grad__translation_p = DOT(grad_pi(xhomg), grad__translation_xhomg);

	auto g = make_tuple(grad__Rot_p, grad__translation_p, grad__X_p, grad__K_p);

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
