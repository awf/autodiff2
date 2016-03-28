#include <cmath>
#include <cassert>
#include <iostream>

#include "test.h"

#include "dot.h"
#include "Vec.h"
#include "Mat.h"

// RELU
template <class Real>
Real relu(Real x)
{
  if (x > 0)
    return x;
  else
    return 0;
}

template <class Real>
Real grad_relu(Real x)
{
  if (x > 0)
    return 1;
  else
    return 0;
}

// Should write with map, but...
template <class Any, size_t N>
Vec<Any, N> relu(Vec<Any, N> x)
{
  Vec<Any> ret(x.size());
  for (size_t i = 0; i != x.size(); ++i)
    ret[i] = relu(x[i]);
  return ret;
}

BOOST_AUTO_TEST_CASE(test_relu)
{
  Vec3<Real> x = vec(-.5, .2, .3);
  BOOST_CHECK(relu(x) == vec(0.,.2,.3));
}

template <class Any>
Vec<Vec<Any>> grad_relu(Vec<Any> const& x)
{
  Vec<Vec<Any>> ret(x.size(), Vec<Any>(x.size()));
  for (size_t i = 0; i != x.size(); ++i)
    ret[i][i] = grad_relu(x[i]);
  return ret;
}



template <class Real, size_t W, size_t H, size_t N_out, size_t N_in, size_t Filter_W, size_t Filter_H>
auto conv(Vec<Mat<Real, Filter_W, Filter_H>, N_out> const& filters,
          Mat<Vec<Real, N_in>, W, H> const& in) ->
  Mat<Vec<Real, N_out>, W, H>
{
  // .. do convolution, efficiently presumably, ...
}

template <class Real, size_t W, size_t H, size_t N_out, size_t N_in, size_t Filter_W, size_t Filter_H>
auto grad1_conv(Vec<Mat<Real, Filter_W, Filter_H>, N_out> const& filters,
                Mat<Vec<Real, N_in>, W, H> const& in) ->
  Vec<Mat<Mat<Vec<Real, N_out>, W, H>, Filter_W, Filter_H>, N_out>
{
  // .. do convolution, efficiently presumably, ...
}

