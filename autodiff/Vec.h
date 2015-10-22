
#include <iterator>
#include <cassert>

#include "copy.h"

///////////////---------------------------

template <typename T>
struct numeric_traits {
  static T zeros_of_shape(T) {
    return T(0);
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

  Vec() {}
  explicit Vec(size_t size) { assert(size == Size); }
  Vec(Zeros_t z) { 
    assert(z.dims[0] == Size || z.dims[0] == 0); 
    assert(z.dims[1] == 0); 
    for (size_t i = 0; i < Size; ++i)
      storage[i] = numeric_traits<T>::zeros_of_shape(T());
  }
  size_t size() const { return Size; }
  T& operator[](size_t i) { return storage[i]; }
  T const& operator[](size_t i) const { return storage[i]; }

  template <class U, int S, class C>
  Vec(Vec<U, S, C> const& that) {
    assert(that.size() == Size);
    std::copy(that.begin(), that.end(), storage);
  }

  template <class U, int S, class C>
  Vec& operator=(Vec<U, S, C> const& that) {
    if (Size != that.n) throw "oik";
    std::copy(that.begin(), that.end(), storage);
    return *this;
  }

  template <class U, int ZU, class CU>
  Vec<T, Size, Vec_GE>& operator+=(Vec<U, ZU, CU> const& that) {
    assert(size() == that.size());
    for (size_t i = 0; i < size(); ++i)
      (*this)[i] += that[i];
    return *this;
  }

  Vec<T, Size, Vec_GE>& operator+=(T const& that) {
    assert(size() == that.size());
    for (size_t i = 0; i < size(); ++i)
      (*this)[i] += that;
    return *this;
  }

  T* begin() { return storage; }
  T* end() { return storage + Size; }
  T const* begin() const { return storage; }
  T const* end() const { return storage + Size; }

private:
  T storage[Size];
};

// Variable-size vector, general contents
template <class T>
struct Vec<T, 0, Vec_GE> {
  typedef T value_type;

  Vec(Vec<T, 0, Vec_GE>&& that) : n(that.n), storage(that.storage) { that.storage = 0; }
  explicit Vec(size_t n) : n(n), storage(new T[n]) {}
  ~Vec() { delete[] storage; }

  size_t size() const { return n; }

  T& operator[](size_t i) { return storage[i]; }
  T const& operator[](size_t i) const { return storage[i]; }

  template <class U, size_t Size, class CT>
  Vec(Vec<U, Size, CT> const& that) : n(that.size()), storage(new T[n]) {
    //std::copy(that.begin(), that.end(), storage);
    for (size_t i = 0; i < n; ++i) storage[i] = that[i];
  }

  template <class U, size_t Size, class C>
  Vec& operator=(Vec<U, Size, C> const& that) {
    if (n != that.size()) throw "oik";
    std::copy(that.begin(), that.end(), storage);
    return *this;
  }

  Vec& operator=(Vec<T, 0>&& that) {
    if (this != &that) {
      delete[] storage;
      this->n = that.n;
      this->storage = that.storage;
      that.storage = 0;
    }
    return *this;
  }

  Vec<T>& operator+=(Vec<T> const&);

  T* begin() { return storage; }
  T* end() { return storage + n; }
  T const* begin() const { return storage; }
  T const* end() const { return storage + n; }

private:
  size_t n;
  T* storage;
};

template <class T>
struct counting_iterator {
  typedef typename counting_iterator<T> this_t;
  size_t count;
  T retval;
  counting_iterator(size_t n, T retval) : count(n), retval(retval) {}
  this_t & operator++(int) { this_t ret = *this;  ++count; return ret; }
  this_t & operator++() { ++count; return *this; }

  template <class U>
  bool operator==(const U& that) const { return count == that.count; }

  template <class U>
  bool operator!=(const U& that) const { return count != that.count; }

  typedef std::forward_iterator_tag iterator_category;
  typedef int difference_type;
  typedef difference_type distance_type;	// retained

  T operator*() { return retval; }

  typedef T value_type;
  typedef T* pointer;
  typedef T& reference;
};

// Variable-size vector, all zeros
template <class T>
struct Vec<T, 0, Vec_ZE> {
  typedef T value_type;

  static T Zero() { return T{ 0 }; }

  explicit Vec(size_t n) : n(n) {}
  size_t size() const { return n; }
  T operator[](size_t i) const { return Zero(); }

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

  static T Zero() { return T{ 0 }; }

  size_t size() const { return Size; }
  T operator[](size_t i) const { return Zero(); }

  typedef counting_iterator < T > iter_t;
  iter_t begin() const { return iter_t{ 0, Zero() }; }
  iter_t end() const { return iter_t{ Size, Zero() }; }
};

// Create vector from argument list
template <typename T, typename... Ts>
auto vec(T t, Ts ... ts) -> Vec<T, 1 + sizeof...(Ts)> {
  Vec<T, 1 + sizeof...(Ts)> v;
  copy(v.begin(), t, ts...);
  return v;
}


// -------------------------- OPERATORS -----------------------------------
template <class T, int N, class CT>
Vec<T, N, CT> operator*(double a, Vec<T, N, CT> const& b)
{
  Vec<T, N, CT> out(b.size());
  for (size_t i = 0; i < b.size(); ++i)
    out[i] = a * b[i];
  return out;
}

template <class T> Vec<T> operator-(Vec<T> const& a, Vec<T> const& b) {
  Vec<T> ret{ a.size() };
  for (size_t i = 0; i < a.size(); ++i)
    ret[i] = a[i] - b[i];
  return ret;
}

template <class R>
struct run_add {
  template <class U, class V>
  R operator()(U const& a, V const& b)
  {
    // assert on sizes
    R ret{ a.size() };
    for (size_t i = 0; i < a.size(); ++i)
      ret[i] = a[i] + b[i];
    return ret;
  }
};


#define DECLARE_ADD(A, B, Ret) 
auto operator+(A const& a, B const& b) -> Ret
{
  return run_add<decltype(a + b)>()(a, b);
}

// Add: Fixedsize, Anysize -> Fixedsize
template <class T, int N, class CTa, class U, class CTb>
auto operator+(Vec<T, N, CTa> const& a, Vec<U, 0, CTb> const& b) -> Vec<typename numeric_traits_binary<T,U>::result_of_add, N, typename CT_traits<CTa, CTb>::result_of_add>
{
  return run_add<decltype(a + b)>()(a, b);
}

// Add: Anysize, Fixedsize -> Fixedsize
template <class T, int N, class CTa, class U, class CTb>
auto operator+(Vec<T, 0, CTa> const& a, Vec<U, N, CTb> const& b) -> Vec<typename numeric_traits_binary<T, U>::result_of_add, N, typename CT_traits<CTa, CTb>::result_of_add>
{
  return run_add<decltype(a + b)>()(a, b);
}

// Add: Anysize, Anysize -> Anysize
template <class T, class CTa, class U, class CTb>
auto operator+(Vec<T, 0, CTa> const& a, Vec<U, 0, CTb> const& b) -> Vec<typename numeric_traits_binary<T, U>::result_of_add, 0, typename CT_traits<CTa, CTb>::result_of_add>
{
  return run_add<decltype(a+b)>()(a,b);
}

// template <class T> Vec<T> operator+(Vec<T> a, Vec<void>) { return a; }

// template <class T> Vec<void> operator+(Vec<T>, Vec<void> b) { return b; }


//template <typename T, int N, class X>
//struct numeric_traits<Vec<T, N, X>> {
//
//  template <typename T1, int N1, class X1>
//  static Vec<T, N, X> zeros_of_shape(Vec<T1, N1, X1>& x) {
//    return Zeros(;
//  }
//};

