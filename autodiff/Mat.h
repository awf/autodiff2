#pragma once

#include "test.h"
#include "Vec.h"

struct Mat_Identity {};

// Typically viewed as a vector of column vectors.  Then gdot<Vec>(Mat, Vec) yields matrix-vector multiply
template <class T, size_t M = 0, size_t N = 0>
struct Mat : public Vec<Vec<T, N>, M> {
  typedef Vec<Vec<T, N>, M> base_t;

  Mat() {}
  Mat(size_t M_, size_t N_) :
    base_t{ M_, Vec<T, N>{N_} }
  {}

  Mat(size_t M_, size_t N_, T const& val) :
    base_t{ M_, Vec<T, N>{N_, val} }
  {}

  template <class U>
  Mat(Vec<Vec<U, N>, M> const& val) :
    base_t{ val }
  {}

  Mat(Vec<Vec<T, N>, M>&& val) :
    base_t{ val }
  {}

  T& operator()(size_t i, size_t j) { return (*this)[j][i]; }

  size_t rows() const { return (*this)[0].size(); }
  size_t cols() const { return size(); }
};

template <class T>
using Mat3x3 = Mat<T,3,3>;

template <class T, size_t N>
Vec<T, N, Vec_GE> diag(Mat<T, N, N> const& m)
{
  Vec<T, N, Vec_GE> out;
  for (size_t i = 0; i < m.size(); ++i)
    out[i] = m[i][i];
  return out;
}

template <class T, size_t N, class CT>
Mat<T, N, N> diaginv(Vec<T, N, CT> const& v)
{
  Mat<T, N, N> out = Mat<Zero, N, N>{ v.size(), v.size() };
  for (size_t i = 0; i < v.size(); ++i)
    out[i][i] = v[i];
  return out;
}

template <class T, size_t N>
Mat<T, N, N> identity() {
  Mat<T, N, N> out(N,N,Zero());
  for (size_t i = 0; i < out.size(); ++i)
    out[i][i] = 1;
  return out;
}

template <class T, size_t N, size_t M>
T trace(Mat<T, N, M> const& m)
{
  return sum(diag(m));
}
