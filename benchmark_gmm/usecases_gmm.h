// GMM: Gaussian Mixture Model
// See eqn 2 of https://github.com/awf/autodiff/blob/master/Documents/AD%202016%20extended.pdf
// alphas
//   vector of logs of mixture weights (unnormalized), so
//   weights = exp(alphas)/sum(exp(alphas))
// means  k x d 
//   Matrix of component means
// qs     k x d 
//   Matrix of logs of diagonals of component inverse covariance matrices
// ls     k x d*(d-1)/2
//   Matrix of vectorized lower triangles of component inverse covariance matrices

#include "stdafx.h"

const size_t GMM_K = 5;
const size_t GMM_D = 3;

#define FIXED_SIZES

// Should/could be faster for fixed K
#ifdef FIXED_SIZES
typedef Vec<Real, GMM_D> VectorD;
typedef Vec<Real> Vector;
#else
typedef Vec<Real> VectorD;
typedef Vec<Real> Vector;
#endif

typedef Vec<Real> Vector;

int tri(int n);

Real logsumexp(Vector const& arr);
VectorD Qtimesv(VectorD const& q, Vector const& l, VectorD const& v);
Real gmm_objective(Vec<VectorD> const& x,
Vector const& alphas, Vec<VectorD> const& means, Vec<VectorD> const& qs, Vec<Vector> const& ls, Real wishart_gamma, Real wishart_m);

void Qtimesv_test();
