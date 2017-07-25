#include <iostream>
#include <string>
#include <chrono>
#include <set>

#include "shared/utils.h"
#include "shared/defs.h"

#if defined DO_BA
#include "tapanade/ba_d-all.h"

double sqsum(int n, double *x)
{
  int i;
  double res;
  res = 0;
  for (i = 0; i < n; i++)
    res = res + x[i] * x[i];
  return res;
}


int test_ba()
{
    // auto cam = vec(
    //     0.1, 0.1, 0.1,     // ROT_IDX = 0;    
    //     0.2,0.1,0.3,       // CENTER_IDX = 3;
    //     1.2,               // FOCAL_IDX = 6;
    //     0.01, 0.03,        // X0_IDX = 7;
    //     0.009, 1.2e-4      // RAD_IDX = 9;
    //     );

    // Vec3<Real> X = vec(0.03, 0.11, -0.7);
    double cam[] = { 0.1, 0.1, 0.1,     // ROT_IDX = 0;    
        0.2,0.1,0.3,       // CENTER_IDX = 3;
        1.2,               // FOCAL_IDX = 6;
        0.01, 0.03,        // X0_IDX = 7;
        0.009, 1.2e-4      // RAD_IDX = 9;
        };
    double X[] = {0.03, 0.11, -0.7};

    // boost::timer::auto_cpu_timer t;
    timer_t t = tic();

    // Debug 150s 
    // Release 1s
    double total = 0;
    int N = 10000000;
#ifdef _DEBUG
    N = N / 100;  // Debug is roughly this much slower than release -- multiply timings.
#endif
    for (int count = 0; count < N; ++count) {
        X[0] = 1.0 / (2.0 + count);
        cam[5] = 1.0 + count * 1e-6;

        double proj[2];
        double proj_d[2];
        project_d(cam, cam , X, X, proj, proj_d);

        total += sqsum(2, proj_d);
    }

    // std::cout << "total =" << total << ", time per call = " << t.elapsed().wall/double(N) << "ns" << std::endl;
    // std::cout << "total =" << total << std::endl;
    auto elapsed = toc(t);
    printf("total =%f, time per call = %f ms\n", total, elapsed / double(N));
    
    return 0;
}


#elif defined DO_MICRO

Real dist(int seed) {
  return ((double)rand()/(double)RAND_MAX);
}

#ifdef ADD3
#define DIM 100
#elif DOT
#include "tapanade/dot_prod_d-all.h"
#define DIM 100
#elif CROSS
#define DIM 3
#endif

array_number_t vector_fill(card_t rows, number_t value) {
  array_number_t macroDef82 = (array_number_t)malloc(sizeof(int) * 2);
  macroDef82->length=rows;
  macroDef82->arr = (number_t*)malloc(sizeof(number_t) * rows);
  for(int i =0; i<rows; i++) {
    macroDef82->arr[i] = 0;
  }
  return macroDef82;
}

void test_micro(cardinality_t N)
{
  int rng = 42;
  srand(rng);
  array_number_t vec1 = vector_fill(DIM, 0.0);
  array_number_t vec2 = vector_fill(DIM, 0.0);
  array_number_t vec3 = vector_fill(DIM, 0.0);

  for (cardinality_t k = 0; k < DIM; ++k) {
    vec1->arr[k] = dist(rng);
    vec2->arr[k] = dist(rng);
    vec3->arr[k] = dist(rng);
  }

  timer_t t = tic();

  double total = 0;

  for (cardinality_t count = 0; count < N; ++count) {
    vec1->arr[0] += 1.0 / (2.0 + vec1->arr[0]);
    vec2->arr[1] += 1.0 / (2.0 + vec2->arr[1]);
#ifdef ADD3
#elif DOT
    double realResult;
    total +=  dot_prod_d(vec1, vec1, vec2, vec2, &realResult);
#elif CROSS
#endif
  }

  auto elapsed = toc(t);
  printf("total =%f, time per call = %f ms\n", total, elapsed / double(N));
}

#endif

int main(int argc, char *argv[])
{
#if defined DO_BA
  test_ba();
#elif defined DO_MICRO
  if(argc != 2) {
    printf("You should use the following format for running this program: %s <Number of Iterations>\n", argv[0]);
    exit(1);
  }
  cardinality_t N = atoi(argv[1]);
  test_micro(N);
#endif
}


