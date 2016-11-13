#include <random>

#include "stdafx.h"

typedef Vec<Real> Vector;


Real dist(int seed) {
  return ((double)rand()/(double)RAND_MAX);
}


int main(int argc, char** argv)
{
  if(argc != 2) {
    printf("You should use the following format for running this program: %s <Number of Iterations>\n", argv[0]);
    exit(1);
  }
  cardinality_t N = atoi(argv[1]);
  int rng = 42;
  srand(rng);

  cardinality_t DIM = 100;

  Vector vec1{ DIM };
  Vector vec2{ DIM };
  Vector vec3{ DIM };

  for (cardinality_t k = 0; k < DIM; ++k) {
    vec1[k] = dist(rng);
    vec2[k] = dist(rng);
    vec3[k] = dist(rng);
  }

  timer_t t = tic();

  double total = 0;

  for (cardinality_t count = 0; count < N; ++count) {
    vec1[0] += 1.0 / (2.0 + vec1[0]);
    vec2[10] += 1.0 / (2.0 + vec2[10]);
    total += sum(vec1 + vec2 + vec3);
  }

  auto elapsed = toc(t);
  printf("total =%f, time per call = %f ms\n", total, elapsed / double(N));

  return 0;
}
