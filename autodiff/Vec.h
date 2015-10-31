#pragma once

#include <iterator>
#include <cassert>
#include <array>
#include <vector>
#include <iostream>

#include "copy.h"
#include "counting_iterator.h"

// TODO better inference of scalars vs containers..
typedef double Real;

///////////////---------------------------

template <typename T>
struct numeric_traits {
  static T zero() {
    return T{ 0 };
  }
  static T zeros_of_shape(T const& that) {
    return T{ 0 };
  }
};

template <typename U, typename V>
struct numeric_traits_binary {
  typedef U result_of_add;
  typedef U result_of_mul;
};

struct numeric_traits_binary_double {
  typedef double result_of_add;
  typedef double result_of_mul;
};

template <>
struct numeric_traits_binary<double, int> : public numeric_traits_binary_double { };

template <>
struct numeric_traits_binary<int, double> : public numeric_traits_binary_double { };

template <>
struct numeric_traits_binary<double, double> : public numeric_traits_binary_double { };

// Class standing for a matrix of Zeros, but not to fully interop with vec and mat, 
// just to act as a tag.
struct Zeros_t {
  size_t dims[2];
  Zeros_t(size_t dims_[2]) { std::copy(dims_, dims_ + sizeof dims / sizeof dims[0], dims); }
  Zeros_t(size_t d0, size_t d1) { dims[0] = d0; dims[1] = d1; }
};

inline Zeros_t Zeros(size_t rows = 0, size_t cols = 0) {
  return Zeros_t(rows, cols);
}
struct Ones_t {};
static const Ones_t Ones;

///////////////---------------------------

// ContentsTag

// Vector contents tag: general
struct Vec_GE {}; 

// Vector contents tag: all zeros
struct Vec_ZE {};

// Vector contents tag: Nth basis vector, i.e. the vector v[N] = 1, otherwise 0;
template <int N>
struct Vec_BV {};

template <class Vec_U, class Vec_V>
struct CT_traits {
  typedef typename Vec_GE result_of_add;
  typedef typename Vec_GE result_of_mul;
};

template <class Vec_U>
struct CT_traits<Vec_U, Vec_ZE> {
  typedef typename Vec_U result_of_add;
  typedef typename Vec_ZE result_of_mul;
};

template <class Vec_U>
struct CT_traits<Vec_ZE, Vec_U> {
  typedef typename Vec_U result_of_add;
  typedef typename Vec_ZE result_of_mul;
};


///////////////---------------------------


// Vector: possibly variable size, possibly special contents
template <class T, int Size = 0, class ContentsTag = Vec_GE>
struct Vec;

// Fixed-size vector, general contents
template <class T, int Size>
struct Vec<T, Size, Vec_GE> {
  typedef T value_type;

  // Vec()
  Vec() {}

  // Vec(size_t)
  explicit Vec(size_t size) { assert(size == Size); }

  // Vec(Zeros)
  Vec(Zeros_t z) { 
    assert(z.dims[0] == Size || z.dims[0] == 0); 
    assert(z.dims[1] == 0); 
    for (size_t i = 0; i < Size; ++i)
      storage[i] = numeric_traits<T>::zeros_of_shape(T());
  }

  // Vec(Vec)
  template <class U, int S, class C>
  Vec(Vec<U, S, C> const& that) {
    assert(that.size() == Size);
    std::copy(that.begin(), that.end(), storage.begin());
  }

  // Vec =(Vec)
  template <class U, int S, class C>
  Vec& operator=(Vec<U, S, C> const& that) {
    assert(Size == that.size());
    std::copy(that.begin(), that.end(), storage.begin());
    return *this;
  }

  // Vec +=(Vec)
  template <class U, int ZU, class CU>
  Vec<T, Size, Vec_GE>& operator+=(Vec<U, ZU, CU> const& that) {
    assert(size() == that.size());
    for (size_t i = 0; i < size(); ++i)
      (*this)[i] += that[i];
    return *this;
  }

  // Vec +=(T)
  Vec<T, Size, Vec_GE>& operator+=(T const& that) {
    assert(size() == that.size());
    for (size_t i = 0; i < size(); ++i)
      (*this)[i] += that;
    return *this;
  }

  // size()
  size_t size() const { return Size; }

  // Vec [size_t]
  T& operator[](size_t i) { return storage[i]; }
  T const& operator[](size_t i) const { return storage[i]; }

  // Vec shape_clone()
  // A vector of the same size, elements uninitialized
  template <class S>
  Vec<S, Size, Vec_GE> shape_clone() const { return Vec<S, Size, Vec_GE>(); }

  // A vector of the same size, elements initialized to zero
  template <class S>
  Vec<S, Size, Vec_GE> zeroed_clone() const { return Vec<S, Size, Vec_ZE>(Size); }

  typedef typename std::array<T, Size>::const_iterator const_iterator;
  typedef typename std::array<T, Size>::iterator iterator;

  iterator begin() { return storage.begin(); }
  iterator end() { return storage.end(); }
  const_iterator begin() const { return storage.begin(); }
  const_iterator end() const { return storage.end(); }

  //private:
  //template <class U1, size_t Size1, class CT1> friend struct Vec<U1,Size1,CT1>;

  std::array<T, Size> storage;
};

// Variable-size vector, general contents
template <class T>
struct Vec<T, 0, Vec_GE> {
  typedef T value_type;

  // Vec(size_t)
  explicit Vec(size_t n) : storage(n) {}

  // Vec(Vec&&)
  Vec(Vec<T, 0, Vec_GE>&& that) : storage(that.storage) {}

  // Vec(Vec)
  template <class U, int S, class C>
  Vec(Vec<U, S, C> const& that): storage(that.size()) {
    std::copy(that.begin(), that.end(), storage.begin());
  }

  // Vec =(Vec)
  template <class U, int S, class C>
  Vec& operator=(Vec<U, S, C> const& that) {
    assert(size() == 0 || size() == that.size());
    storage.resize(that.size());
    std::copy(that.begin(), that.end(), storage.begin());
    return *this;
  }

  Vec& operator=(Vec<T, 0, Vec_GE>&& that) {
    storage = that.storage;
    return *this;
  }

  // size_t size()
  size_t size() const { return storage.size(); }

  // Vec[size_t]
  T& operator[](size_t i) { return storage[i]; }
  T const& operator[](size_t i) const { return storage[i]; }


  Vec<T>& operator+=(Vec<T> const&);

  template <class S>
  Vec<S, 0, Vec_GE> shape_clone() const { return Vec<S, 0, Vec_GE>(size()); }
 
  /**
  template <class S>
  Vec<S, 0, Vec_GE> zeroed_clone() const { }
  */

  typedef typename std::vector<T>::const_iterator const_iterator;
  typedef typename std::vector<T>::iterator iterator;

  iterator begin() { return storage.begin(); }
  iterator end() { return storage.end(); }
  const_iterator begin() const { return storage.begin(); }
  const_iterator end() const { return storage.end(); }

//private:
  //template <class U1, size_t Size1, class CT1> friend struct Vec<U1,Size1,CT1>;
  std::vector<T> storage;
};

// Variable-size vector, all zeros
template <class T>
struct Vec<T, 0, Vec_ZE> {
  typedef T value_type;

  static T Zero() { return T{ 0 }; }

  explicit Vec(size_t n) : n(n) {}
  size_t size() const { return n; }
  T operator[](size_t i) const { return Zero(); }

  template <class S>
  Vec<S, 0, Vec_ZE> shape_clone() const { return Vec<S, 0, Vec_ZE>(n); }

  template <class S>
  Vec<S, 0, Vec_ZE> zeroed_clone() const { return Vec<S, 0, Vec_ZE>(n); }

  typedef counting_iterator < T > iter_t;
  iter_t begin() const { return iter_t(0, Zero()); }
  iter_t end() const { return iter_t(n, Zero()); }

private:
  size_t n;
};

// Fixed-size vector, all zeros
template <class T, int Size>
struct Vec<T, Size, Vec_ZE> {
  typedef T value_type;

  explicit Vec() {}
  explicit Vec(size_t size) { assert(size == Size); }

  static T Zero() { return numeric_traits<T>::zero(); }

  size_t size() const { return Size; }
  T operator[](size_t i) const { return Zero(); }

  template <class S>
  Vec<S, Size, Vec_ZE> shape_clone() const { return Vec<S, Size, Vec_ZE>(); }

  template <class S>
  Vec<S, Size, Vec_ZE> zeroed_clone() const { return Vec<S, Size, Vec_ZE>(); }

  typedef counting_iterator < T > iter_t;
  iter_t begin() const { return iter_t{ 0, Zero() }; }
  iter_t end() const { return iter_t{ Size, Zero() }; }
};

// FUNCTION: vec
// Create vector from argument list
template <typename T, typename... Ts>
auto vec(T t, Ts ... ts) -> Vec<T, 1 + sizeof...(Ts)> {
  Vec<T, 1 + sizeof...(Ts)> v;
  vcopy(v.begin(), t, ts...);
  return v;
}

// -------------------------- OPERATORS -----------------------------------
// OPERATOR: double * Vec
template <class T, int N, class CT>
Vec<T, N, CT> operator*(double a, Vec<T, N, CT> const& b)
{
  Vec<T, N, CT> out(b.size());
  for (size_t i = 0; i < b.size(); ++i)
    out[i] = a * b[i];
  return out;
}


// TODO generalize to args not just double
template <class T, int N, class CT>
Vec<T, N, CT> operator*(Vec<T, N, CT> const& a, double b)
{
  Vec<T, N, CT> out(a.size());
  for (size_t i = 0; i < a.size(); ++i)
    out[i] = a[i] * b;
  return out;
}

template <class R, class Functor>
struct run_elementwise_binary {
  template <class U, class V>
  R operator()(U const& a, V const& b)
  {
    // assert on sizes
    assert(a.size() == b.size());
    R ret{ a.size() };
    for (size_t i = 0; i < a.size(); ++i)
      ret[i] = a[i] + b[i];  // TODO proper functor
    return ret;
  }
};


#define DECLARE_ADD_2(AT, AN, ACT, BT, BN, BCT, Ret_T, Ret_N, Ret_CT) \
auto operator+(Vec<AT, AN, ACT> const& a, Vec<BT, BN, BCT> const& b) -> Vec<Ret_T, Ret_N, Ret_CT>\
{\
  return run_elementwise_binary<decltype(a+b), void>()(a, b);\
}

#define DECLARE_ADD(AT, AN, ACT, BT, BN, BCT, Ret_N, Ret_CT) \
  DECLARE_ADD_2(AT,AN,ACT,BT,BN,BCT,decltype(a[0] + b[0]),Ret_N,Ret_CT)

#define ADD_CT(CTa, CTb) typename CT_traits<CTa, CTb>::result_of_add

// Add: Fixedsize, Anysize -> Fixedsize
template <class T, int N, class CTa, class U, class CTb>
DECLARE_ADD(T, N, CTa, U, 0, CTb, N, ADD_CT(CTa, CTb))

// Add: Anysize, Fixedsize -> Fixedsize
template <class T, int N, class CTa, class U, class CTb>
DECLARE_ADD(T, 0, CTa, U, N, CTb, N, ADD_CT(CTa, CTb))

// Add: Anysize, Anysize -> Anysize
template <class T, class CTa, class U, class CTb>
DECLARE_ADD(T, 0, CTa, U, 0, CTb, 0, ADD_CT(CTa, CTb))

// Add: Fixedsize, Fixedsize -> Fixedsize
template <class T, int N, class CTa, class U, int M, class CTb>
DECLARE_ADD(T, N, CTa, U, M, CTb, N, ADD_CT(CTa, CTb))


// GROUP: STREAMS
template <class T>
struct vector_printer {
  const T& t;
  vector_printer(const T& t) :t(t) {}
};

template <class T>
vector_printer<T> pr(const T& t) {
  return vector_printer<T>(t);
}

template <class T>
std::ostream& operator<<(std::ostream& s, vector_printer<T> const& t)
{
  s << "{ ";
  auto b = std::begin(t.t);
  auto pe = std::end(t.t);
  --pe;
  std::copy(b, pe, std::ostream_iterator<decltype(*b)>(s, ", "));
  return s << *pe << " }";
}

template <class T, int N, class CT>
std::ostream& operator<<(std::ostream& s, Vec<T, N, CT> const& t)
{
  return s << pr(t);
}

// ENDGROUP: streams

template <typename T, int Size, typename CT>
struct numeric_traits<Vec<T,Size,CT>> {
  static Vec<T, Size, Vec_ZE> zero() {
    return Vec<T, Size, Vec_ZE>();
  }

  static Vec<T, Size, Vec_ZE> zeros_of_shape(Vec<T, Size, CT> const & that) {
    return Vec<T, Size, Vec_ZE>{that.size()};
  }
};

// FUNGROUP deep_fill
// Fill every Scalar in a recursive container of Scalar with a given value
template <class Container, class Scalar>
void deep_fill(Container* c, Scalar const& val) {
  for (auto& pc : *c)
    deep_fill(&pc, val);
}

template <class Scalar>
void deep_fill(Scalar* c, Scalar const& val) {
  *c = val;
}
// END deep_fill

// DOT PRODUCT.
// If everything works as intended, this code is now fast for all combinations of
// Fixedness and ContentType
template <class T1, int Size1, class CT1, class T2, int Size2, class CT2>
auto dot(Vec<T1, Size1, CT1> const& a, Vec<T2, Size2, CT2> const& b) -> decltype(a[0] * b[0] + a[0] * b[0])
{
  typedef decltype(a[0] * b[0] + a[0] * b[0]) ret_t;

  assert(a.size() == b.size());
  if (a.size() == 0)
    return numeric_traits<ret_t>::zero();

  ret_t out = a[0] * b[0];
  for (size_t i = 1; i < a.size(); ++i)
    out += a[i] * b[i];
  return out;
}

// NORMSQ
template <class T, int Size, class CT>
auto normsq(Vec<T, Size, CT> const& v) -> decltype(dot(v, v))
{
  return dot(v, v);
}

// FLATTEN
template <class CT1, int Size>
Real* flatten(Vec<Real, Size, CT1> const& a, Real* out)
{
  Real* p = out;
  for (auto val : a)
    *out++ = val;
  return out;
}

template <class T, int Size, class CT1>
Real* flatten(Vec<T, Size, CT1> const& a, Real* out)
{
  for (auto val : a)
    out = flatten(val, out);
  return out;
}

template <int Size, class CT1>
Vec<Real, Size, CT1>  flatten(Vec<Real, Size, CT1> const& a)
{
  return a;
}

// TODO speed up for fixed size inputs
template <class T1, int Size, class CT1>
Vec<Real, 0, CT1>  flatten(Vec<T1, Size, CT1> const& a)
{
  size_t out_size = 0;
  for (auto val : a)
    out_size += flatten(val).size();

  Vec<Real, 0, CT1> out{ out_size };
  flatten(a, &out[0]);
  return out;
}

inline void test_flatten()
{
  auto a = vec(1., 2.);
  auto b = vec(3., 5.);
  auto c = vec(a, b);
  assert(flatten(c).size() == 4);
  assert(flatten(c)[3] == 5);
}

// ENDGROUP flatten
