
#include <cmath>
#include <cassert>
#include <iostream>
#include <algorithm>
#include <vector>
#include <iterator>
#include <functional>

#include "flat_view.h"

#include "dot.h"
#include "Vec.h"

#include "rodrigues.h"

// GROUP: shape_clone
// Shape clone: Return a container of the same size with a different content type in place of Real
template <class Replace_t>
Replace_t shape_clone(Real that)
{
  return Replace_t{};
}

// Shape clone: Return a container of the same size with a different content type in place of Real
template <class Replace_t, int Size, typename CT>
Vec<Replace_t, Size, CT> shape_clone(Vec<Real, Size, CT> const& that)
{
  Vec<Replace_t, Size, CT> ret{ that.size() };
  return ret;
}

// Shape clone: Return a container of the same size with a different content type
// The container may be multi-level
template <class Replace_t, int Size, typename CT, class T>
auto shape_clone(Vec<T, Size, CT> const& that) ->
  Vec<decltype(shape_clone<Replace_t>(that[0])), Size, CT>
{
  typedef decltype(shape_clone<Replace_t>(that[0])) new_value_type;
  Vec<new_value_type, Size, CT> ret{ that.size() };
  auto const& p = std::begin(that);
  for (auto& i : ret)
    i = shape_clone<Replace_t>(*p++);
  return ret;
}

//decltype(shape_clone<Vec3<Real>>(Vec3<Vec3<Real>>())) a = 3;
ASSERT_SAME_TYPE(decltype(shape_clone<Vec3<Real>>(Vec3<Vec3<Real>>())), Vec3<Vec3<Vec3<Real>>>);

// ENDGROUP: shape_clone

// Helper to declare the type of the gradient of a function which 
// takes a Container2_of_Real and returns a Container1_of_Real
template <class Container1_of_Real, class Container2_of_Real>
struct gradient_declarations_helper {
  typedef std::function<Container1_of_Real(Container2_of_Real const&)> function_t;

  typedef decltype (shape_clone<Container2_of_Real>(std::declval<Container1_of_Real>())) Container1_of_Container2_of_Real;
  typedef decltype (shape_clone<Container1_of_Real>(std::declval<Container2_of_Real>())) Container2_of_Container1_of_Real;
  //typedef typename Container1_of_Container2_of_Real grad_t;
  //typedef std::function<grad_t(Container2_of_Real const&)> grad_function_t;

  // Compute finite-difference gradients
  Container2_of_Container1_of_Real grad_fd_transpose(function_t f, Container2_of_Real const& x) {
    Container2_of_Container1_of_Real grad_fd_transpose;

    // grad_fd[i,j] = (fx(x+delta*e_j)[i] - f(x)[i])/delta;
    // grad_fd[:,j] = (fx(x+delta*e_j) - f(x) )/delta;

    Container1_of_Real fx = f(x);
    double delta = 1e-6;
    auto xp = x;

    auto flat_x = flat_view<Real>(x);
    auto x_iter = flat_x.begin();

    auto flat_xp = flat_view<Real>(xp);
    auto xp_iter = flat_xp.begin();

    auto flat_out = flat_view<Container1_of_Real>(grad_fd_transpose);
    auto out_iter = flat_out.begin();
    for (; x_iter != flat_x.end(); ++x_iter, ++xp_iter, ++out_iter) {
      auto xi = *x_iter;
      *xp_iter = xi + delta;
      double actual_delta = *xp_iter - xi;
      Container1_of_Real fxp = f(xp);
      *out_iter = (fxp - fx) / actual_delta;
      *xp_iter = xi;
    }
    return grad_fd_transpose;
  }
};

template <class Container1_of_Real, class Container2_of_Real>
auto tgrad_finite_difference(std::function<Container1_of_Real(Container2_of_Real const&)> f,
  Container2_of_Real const& x) ->
  typename gradient_declarations_helper<Container1_of_Real, Container2_of_Real>::Container2_of_Container1_of_Real
{
  return gradient_declarations_helper<Container1_of_Real, Container2_of_Real>().grad_fd_transpose(f, x);
}


template <class T>
T trace(Mat3x3<T> const& m)
{
  return sum(diag(m));
}

template <class T>
Mat3x3<T> grad_trace(Mat3x3<T> const& m)
{
  Mat3x3<T> out = Mat<Zero,3,3>();
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

void test_chain_rule()
{
  Vec3<Real> x = vec(-.5, .2, .3);
  Vec3<Real> grad = grad_f(x);
  std::cout << "GRAD_CR = " << grad << "\n";

  // Finite differences
  Vec3<Real> grad_fd = tgrad_finite_difference<Real, Vec3<Real>>(f, x);
  std::cout << "GRAD_FD = " << grad_fd << "\n";
}

#if 1

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


Vec3<Real> mmul(Mat3x3<Real> const& a, Vec3<Real> const& b)
{ 
  return dot(a,b); 
}

Vec3<Mat3x3<Real>> grad1_mmul(Mat3x3<Real> const& a, Vec3<Real> const& b)
{
  Vec<Zero, 3> zero;
  return vec( 
    vec<Vec3<Real>>(b, zero, zero),
    vec<Vec3<Real>>(zero, b, zero),
    vec<Vec3<Real>>(zero, zero, b));
}

Vec3<Vec3<Real>> grad2_mmul(Mat3x3<Real> const& a, Vec3<Real> const& b)
{
  return a;
}


Vec3<Real> b() { return vec<Real>(1, 2, 3); }
//Vec3<void> grad_b() { return Vec3<void>(); }

Vec3<Real> f2(Vec3<Real> const& a) {
  auto Rot = exp2mat(a);
  return mmul(Rot, b());
}

Vec3<Vec3<Real>> grad_f2(Vec3<Real> const& a) {
  auto Rot = exp2mat(a);
  auto grad_Rot = grad_exp2mat(a);

  Vec3<Real> val_b = b();
//  Vec3<void> val_grad_b = grad_b();

  auto f = mmul(Rot, val_b);
  auto d1 = gdot(grad1_mmul(Rot, val_b), grad_Rot, a);
  //auto d2 = gdot(grad2_mmul(Rot, val_b), val_grad_b, void());
  return d1;// + d2
}

Real f3(Vec3<Real> const& a) {
  auto Rot = exp2mat(a);
  return dot(b(), mmul(Rot, b()));
}

Vec3<Real> grad_f3(Vec3<Real> const& a) {
  auto Rot = exp2mat(a);
  auto grad_Rot = grad_exp2mat(a);

  Vec3<Real> val_b = b();
  //  Vec3<void> val_grad_b = grad_b();

  auto f = mmul(Rot, val_b);
  auto d1 = gdot(grad1_mmul(Rot, val_b), grad_Rot, a);
  //auto d2 = gdot(grad2_mmul(Rot, val_b), val_grad_b, void());
  return dot(b(), d1);// + d2
}

#if 1
Vec3<Real> f4(Mat3x3<Real> const& A)
{
  return mmul(A, b());
}

Vec3<Mat3x3<Real>> grad_f4(Mat3x3<Real> const& A)
{
  return grad1_mmul(A, b());
}

void test_f2()
{
  // Test grad of mmul(X,b)
  {
    Mat3x3<Real> A { vec(vec(1.1,1.2,1.3), vec(7.,5.,11.), vec(13.,17.,19.)) };
    std::cout << "GradF4 Hand = " << grad_f4(A) << std::endl;

    auto fd = tgrad_finite_difference<Vec3<Real>, Mat3x3<Real>>(f4, A);
    std::cout << "GradF4 FD = " << fd << std::endl;
  }

  Vec3<Real> a = vec(1., 2., 5.);
  auto f2a = f2(a);
  auto grad_f2a = grad_f2(a);
  std::cout << "GRAD_CR = " << grad_f2a << "\n";

  auto fd = transpose(tgrad_finite_difference<Vec3<Real>, Vec3<Real>>(f2, a));

  // Finite differences
  std::cout << "GRAD_FD = " << fd << "\n";

}
#endif

#if 0

Real sqr(Real a) { return a*a; }

Vec2<Real> pi(Vec3<Real> const& X)
{
  Vec2<Real> ret(2u);
  ret[0] = X[0] / X[2];
  ret[1] = X[1] / X[2];
  return ret;
}

Vec3<Vec3<Real>> grad_pi(Vec3<Real> const& X)
{
  Vec<Vec3<Real>> ret(2);
  Real x = X[0];
  Real y = X[1];
  Real z = X[2];
  Real sz = 1 / z;
  Real szz = sz*sz;

  ret[0] = vec<Real>(sz, 0, -x * szz);
  ret[1] = vec<Real>(0, sz, -y * szz);
  return ret;
}

Vec<Vec<Real>> grad_(Vec<Real> const& x)
{
  Vec<Vec<Real>> ret = numeric_traits<Vec<Vec<Real>>>::zeros_of_shape(x);
  for (size_t i = 0; i < x.size(); ++i)
    ret[i][i] = 1;
  return ret;
}


Vec2<Real> project(Vec3<Real> rotation, Vec3<Real> translation, Vec3<Real> X, Vec5<Real> kappa) {
  Mat3x3<Real> Rot = exp2mat(rotation);
  Real f = kappa[0];
  Real cx = kappa[1];
  Real cy = kappa[2];
  Real k1 = kappa[3];
  Real k2 = kappa[4];
  Mat3x3<Real> K = Mat3x3<Real>(
    vec<Real>(f, 0, cx),
    vec<Real>(0, f, cy),
    vec<Real>(0, 0, 1));
  // ICE:	Mat3x3<Real> K = { { f, 0, cx }, { 0, f, cy }, { 0, 0, 1 } };
  Vec2<Real> p = pi(mmul(K, mmul(Rot, X) + translation));

  return p;
}

tuple < Vec2<Vec3<Real>>, Vec2<Vec3<Real>>, Vec2<Vec3<Real>>, Vec2<Vec<Real>> > grad_project(Vec3<Real> rotation, Vec3<Real> translation, Vec3<Real> X, Vec<Real> kappa) {
  auto grad_rotation = grad_(rotation);
  auto grad_translation = grad_(translation);
  auto grad_X = grad_(X);
  auto grad_kappa = grad_(kappa);

  Mat3x3<Real> Rot = exp2mat(rotation);
  auto grad_Rot = grad_exp2mat(rotation);

  Real f = kappa[0];
  auto grad_f = grad_kappa[0];  // grad_index(kappa,0)
  Real cx = kappa[1];
  auto grad_cx = grad_kappa[1];
  Real cy = kappa[2];
  auto grad_cy = grad_kappa[2];
  Real k1 = kappa[3];
  auto grad_k1 = grad_kappa[3];
  Real k2 = kappa[4];
  auto grad_k2 = grad_kappa[4];
  Vec<Real> e0 = numeric_traits<Vec<Real>>::zeros_of_shape(grad_f);
  Mat3x3<Real> K = Mat3x3<Real>(
    vec<Real>(f, 0, cx),
    vec<Real>(0, f, cy),
    vec<Real>(0, 0, 1));
  Mat3x3<Vec<Real>> grad_K = Mat3x3<Vec<Real>>(
    vec<Vec<Real>>(grad_f, e0, grad_cx),
    vec<Vec<Real>>(e0, grad_f, grad_cy),
    vec<Vec<Real>>(e0, e0, e0));

  Vec3<Real> xcam = mmul(Rot, X) + translation;

  auto grad__Rot_xcam = DOT(grad_₁mmul(Rot, X), grad_Rot);
  auto grad__X_xcam = DOT(grad_₂mmul(Rot, X), grad_X);
  auto grad__translation_xcam = grad_translation;

  Vec3<Real> xhomg = mmul(K, xcam);
  // grad_xhomg = DOT(grad_₁mmul(K, xcam), grad_K) + DOT(grad_₂mmul(K, xcam), grad_xcam);
  auto grad__K_xhomg = DOT(grad_₁mmul(K, xcam), grad_K);
  auto grad__Rot_xhomg = DOT(grad_₂mmul(K, xcam), grad__Rot_xcam);
  auto grad__X_xhomg = DOT(grad_₂mmul(K, xcam), grad__X_xcam);
  auto grad__translation_xhomg = DOT(grad_₂mmul(K, xcam), grad__translation_xcam);

  Vec2<Real> p = pi(xhomg);
  auto grad__K_p = DOT(grad_pi(xhomg), grad__K_xhomg);
  auto grad__Rot_p = DOT(grad_pi(xhomg), grad__Rot_xhomg);
  auto grad__X_p = DOT(grad_pi(xhomg), grad__X_xhomg);
  auto grad__translation_p = DOT(grad_pi(xhomg), grad__translation_xhomg);

  auto g = make_tuple(grad__Rot_p, grad__translation_p, grad__X_p, grad__K_p);

  return g;
}

Vec<Vec2<Real>> residuals(Vec<Vec3<Real>> rotations, Vec<Vec3<Real>> translations, Vec<Vec3<Real>> Xs, Vec<Real> kappas,
  Vec<Vec2<Real>> ms, Vec<int> frames, Vec<int> points)
{
  int nR = ms.size();
  Vec<Vec2<Real>> ret(nR);
  for (size_t i = 0; i < ms.size(); ++i) {
    int f = frames[i];
    int p = points[i];
    ret[i] = project(rotations[f], translations[f], Xs[p], kappas) - ms[i];
  }
  return ret;
}

#endif


int main(int argc, char* argv[])
{
  test_deep_iterator();

  auto v123 = vec(1., 2., 3.);
  auto v357 = vec(3., 5., 7.);
  auto v713 = vec(7., 11., 13.);

  Vec<Vec<Real, 3>, 3> a = vec(v123, v713, v357);
  Vec<Vec<Real, 3>, 3> b = vec(v123, v713, v123);

  std::cout << pr(a) << std::endl;
 
  test_f2();

  test_dotter_1();

  test_chain_rule();

  Real c = 0;
  Vec<Vec<Real, 3>, 3> vvc = Vec3<Vec3<Zero>>();

  /*
  Vec3<Real> rotation = vec<Real>(1,-2,3);
  Vec3<Real> translation = vec<Real>(11, 12, 13);
  Vec3<Real> X = vec<Real>(.1, .3, .5);
  Vec<Real> kappa = vec<Real>(1.4, 0.01, 0.02, 0, 0);

  Vec2<Real> p = project(rotation, translation, X, kappa);

  auto grad_p = grad_project(rotation, translation, X, kappa);
  */
  return 0;
}

#endif
