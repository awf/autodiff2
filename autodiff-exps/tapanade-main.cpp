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

#elif defined DO_GMM
// #include "tapanade/gmm.h"
#include "tapanade/gmm_d-all.h"

typedef double number_t;
typedef struct array_number_t_struct {
    number_t *arr;
    int length;
} * array_number_t;

typedef struct array_array_number_t_struct {
    array_number_t *arr;
    int length;
} * array_array_number_t;

const size_t GMM_K = 5;
const size_t GMM_D = 3;

double dist(int seed) {
  return ((double)rand()/(double)RAND_MAX);
}

array_array_number_t matrix_fill(card_t rows, card_t cols, number_t value) {
  array_array_number_t macroDef83 = (array_array_number_t)malloc(sizeof(int) * 2);
  macroDef83->length=rows;
  macroDef83->arr = (array_number_t*)malloc(sizeof(array_number_t) * rows);
    for(int r = 0; r < macroDef83->length; r++){
      array_number_t macroDef82 = (array_number_t)malloc(sizeof(int) * 2);
  macroDef82->length=cols;
  macroDef82->arr = (number_t*)malloc(sizeof(number_t) * cols);
    for(int c = 0; c < macroDef82->length; c++){
      
      macroDef82->arr[c] = value;;
    }
      macroDef83->arr[r] = macroDef82;;
    }
  return macroDef83;
}

array_number_t vector_fill(card_t rows, number_t value) {
  return matrix_fill(1, rows, value)->arr[0];
}

void array_print(array_number_t arr) {
  printf("[");
  for (int i = 0; i < arr->length; i++) {
    printf("%f", arr->arr[i]);
    if (i != arr->length - 1)
      printf(", ");
  }
  printf("]\n");
}


void test_gmm()
{
  int rng = 42;
  srand(rng);
  // std::mt19937 rng(42);
  // std::uniform_real_distribution<Real> dist(0, 1);

  // Problem size
  size_t n = 100;
  size_t d = GMM_D;
  size_t K = GMM_K;
  size_t td = ((d) * ((d) + (1))) / (2);
  

  // Declare and fill GMM coeffs
  // Vector alphas{ K };
  // Vec<VectorD> means{ K, VectorD{ d } };
  // Vec<VectorD> qs{ K, VectorD{ d } };
  // Vector l0{ size_t(tri(d)) };
  // Vec<Vector> ls{ K, l0 };
  array_number_t alphas = vector_fill(K, 0);
  array_number_t means = vector_fill(K * d, 0);
  array_number_t qs = vector_fill(K * d, 0);
  array_number_t ls = vector_fill(K * td, 0);
  array_number_t icf = vector_fill(K * td, 0);
  for (int k = 0; k < K; ++k) {
    alphas->arr[k] = dist(rng);
    for (int j = 0; j < d; ++j) {
      means->arr[k * d + j] = dist(rng) - 0.5;
      qs->arr[k * d + j] = 10.0*dist(rng) - 5.0;
    }
    for (int j = 0; j < td; ++j) {
      ls->arr[k * td + j] = dist(rng) - 0.5;
      if(j >= td - d)
        ls->arr[k * td + j] = 0;
      if(j < d) {
        icf->arr[k * td + j] = qs->arr[k * d + j];
      } else {
        icf->arr[k * td + j] = ls->arr[k * td + j - d];
      }
    }
  }

  // Declare and fill xs
  // Vec<VectorD> xs{ n, Vector{ d } };
  array_number_t xs = vector_fill(n * d, 0);
  for (int i = 0; i < n; ++i)
    for (int j = 0; j < d; ++j)
      xs->arr[i * d + j] = dist(rng);

  // TOP_LEVEL_usecases_gmm_Qtimesv_test(0);

  // boost::timer::auto_cpu_timer t;
  timer_t t = tic();

  // Debug 150s 
    // Release 1s
  double total = 0;
  int N = 10000;
#ifdef _DEBUG
  N = N / 10;  // Debug is roughly this much slower than release -- multiply timings.
#endif
  double wishart_m = 2.0;
  for (int count = 0; count < N; ++count) {
    double wishart_gamma = 1.0 / (1.0 + count);
    double res, tmp;

    // TODO icf instead of qs and ls
    // gmm_objective(d, K, n, alphas->arr, means->arr, icf->arr, xs->arr, wishart_gamma, wishart_m, &res);
    // total += res;
    gmm_objective_d(d, K, n, alphas->arr, alphas->arr, means->arr, means->arr, icf->arr, icf->arr, xs->arr, xs->arr, wishart_gamma, wishart_m, &tmp, &res);
    total += res;
  }

  // std::cout << "total =" << total << ", time per call = " << t.elapsed().wall / double(N) / 1000.0 << "us" << std::endl;
  double elapsed = toc(t);
  printf("total =%f, time per call = %f ms\n", total, elapsed / (double)(N));
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
#elif defined DO_GMM
  test_gmm();
#elif defined DO_MICRO
  if(argc != 2) {
    printf("You should use the following format for running this program: %s <Number of Iterations>\n", argv[0]);
    exit(1);
  }
  cardinality_t N = atoi(argv[1]);
  test_micro(N);
#endif
}


