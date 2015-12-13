#pragma once

#include "Vec.h"

template <class T>
using Vec3 = Vec<T, 3>;

struct Mat_Identity {};

template <class T, size_t M, size_t N>
struct Mat : public Vec<Vec<T, N>, M> {
  typedef Vec<Vec<T, N>, M> base_t;

  Mat() {}
  Mat(size_t M_, size_t N_, T const& val) :
    base_t{ M_, Vec<T, N>{N_, Zero()} }
  {}

  template <class U>
  Mat(Vec<Vec<U, N>, M> const& val) :
    base_t{ val }
  {}

  Mat(Vec<Vec<T, N>, M>&& val) :
    base_t{ val }
  {}
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

template <class T, size_t N>
Mat<T, N, N> identity() {
  Mat<T, N, N> out(N,N,numeric_traits<T>::zero());
  for (size_t i = 0; i < m.size(); ++i)
    out[i][i] = 1;
  return out;
}
