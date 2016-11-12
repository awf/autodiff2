// benchmark_gmm.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <random>

#include "usecases_gmm.h"

Real gmm_objective(Vec<Vector> const& x,
  Vector const& alphas, Vec<Vector> const& means, Vec<Vector> const& qs, Vec<Vector> const& ls,
  Real wishart_gamma, Real wishart_m);

Real dist(int seed) {
  return ((double)rand()/(double)RAND_MAX);
}

int main()
{
  int rng(42);
  srand(rng);
  // std::mt19937 rng(42);
  // std::uniform_real_distribution<Real> dist(0, 1);

  // Problem size
  size_t n = 100;
  size_t d = GMM_D;
  size_t K = GMM_K;

  // Declare and fill GMM coeffs
  Vector alphas{ K };
  std::vector<VectorD> means{ K, VectorD{ d } };
  std::vector<VectorD> qs{ K, VectorD{ d } };
  Vector l0{ tri(d) };
  std::vector<Vector> ls{ K, l0 };
  for (size_t k = 0; k < K; ++k) {
    alphas[k] = dist(rng);
    for (size_t j = 0; j < d; ++j) {
      means[k][j] = dist(rng) - 0.5;
      qs[k][j] = 10.0*dist(rng) - 5.0;
    }
    for (size_t j = 0; j < size_t(ls[k].size()); ++j)
      ls[k][j] = dist(rng) - 0.5;
  }

  // Declare and fill xs
  std::vector<VectorD> xs{ n, Vector{ d } };
  for (size_t i = 0; i < n; ++i)
    for (size_t j = 0; j < d; ++j)
      xs[i][j] = dist(rng);

  // Qtimesv_test();


  // boost::timer::auto_cpu_timer t;
  timer_t t = tic();

  // Debug 150s 
    // Release 1s
  double total = 0;
  size_t N = 100000;
#ifdef _DEBUG
  N = N / 10;  // Debug is roughly this much slower than release -- multiply timings.
#endif
  double wishart_m = 2.0;
  for (size_t count = 0; count < N; ++count) {
    double wishart_gamma = 1.0 / (1.0 + count);
    total += gmm_objective(xs, alphas, means, qs, ls, wishart_gamma, wishart_m);
  }

  // std::cout << "total =" << total << ", time per call = " << t.elapsed().wall / double(N) / 1000.0 << "us" << std::endl;
  auto elapsed = toc(t);
  printf("total =%f, time per call = %f ms\n", total, elapsed / double(N));

  return 0;
}
