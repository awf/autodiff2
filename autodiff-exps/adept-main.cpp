#include <iostream>
#include <string>
#include <chrono>
#include <set>

//#define DO_GMM_FULL
//#define DO_GMM_SPLIT
// #define DO_BA
// #define DO_HAND
//#define DO_HAND_COMPLICATED

#define DO_LIGHT_MATRIX
//#define DO_VXL // this is experimental - vxl does not compile with adouble

#include "adept.h"
#include "shared/utils.h"
#include "shared/defs.h"

#if defined DO_GMM_FULL || defined DO_GMM_SPLIT
#define ADEPT_COMPILATION
#include "../gmm.h"
#elif defined DO_BA
#include "shared/ba.h"
#elif (defined DO_HAND || defined DO_HAND_COMPLICATED)
#ifdef DO_LIGHT_MATRIX
#include "../hand_light_matrix.h"
typedef HandDataLightMatrix HandDataType;
#elif defined DO_VXL
#include "hand_vxl.h"
#include "utils_vxl.h"
typedef HandDataVXL HandDataType;
#endif
#endif

using adept::adouble;
using std::cout;
using std::endl;
using std::string;
using namespace std::chrono;

#if defined DO_BA

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
    vector<double> cam, X;
    cam = { 0.1, 0.1, 0.1,     // ROT_IDX = 0;    
        0.2,0.1,0.3,       // CENTER_IDX = 3;
        1.2,               // FOCAL_IDX = 6;
        0.01, 0.03,        // X0_IDX = 7;
        0.009, 1.2e-4      // RAD_IDX = 9;
        };
    X = {0.03, 0.11, -0.7};

    adept::Stack stack;
    adouble acam[BA_NCAMPARAMS],
      aX[3];

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
        adept::set_values(acam, BA_NCAMPARAMS, cam.data());
        adept::set_values(aX, 3, X.data());

        stack.new_recording();

        adouble aproj[2];
        double proj[2];
        project(acam, aX, aproj);
        stack.independent(acam, BA_NCAMPARAMS);
        stack.independent(aX, 3);
        stack.dependent(aproj, 2);
        double init[2] = {1.0, 1.0};
        adept::set_gradients(acam, BA_NCAMPARAMS, cam.data());
        adept::set_gradients(aX, 3, X.data());
        stack.compute_tangent_linear();
        adept::get_gradients(aproj, 2, proj);

        total += sqsum(2, proj);
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
#define DIM 100
#elif CROSS
#define DIM 3
#endif

void test_micro(cardinality_t N)
{
  int rng = 42;
  srand(rng);
  double vec1[DIM], vec2[DIM], vec3[DIM];
  adept::Stack stack;
  adouble avec1[DIM], avec2[DIM], avec3[DIM];

  for (cardinality_t k = 0; k < DIM; ++k) {
    vec1[k] = dist(rng);
    vec2[k] = dist(rng);
    vec3[k] = dist(rng);
  }

  timer_t t = tic();

  double total = 0;

  for (cardinality_t count = 0; count < N; ++count) {
    vec1[0] += 1.0 / (2.0 + vec1[0]);
    vec2[1] += 1.0 / (2.0 + vec2[1]);
    adept::set_values(avec1, DIM, vec1);
    adept::set_values(avec2, DIM, vec2);
    stack.new_recording();
#ifdef ADD3
  // #ifdef EIGEN
  //   total += sum((vec1 + vec2 + vec3).eval());
  // #else
  //   total += sum((vec1 + vec2 + vec3));
  // #endif
#elif DOT
    adouble result = dot(DIM, avec1, avec2);
    // stack.independent(avec1, DIM);
    // stack.independent(avec2, DIM);
    // stack.dependent(result);
    adept::set_gradients(avec1, DIM, vec1);
    adept::set_gradients(avec2, DIM, vec2);
    stack.compute_tangent_linear();
    total += result.get_gradient();
#elif CROSS
    // total += sum(cross(vec1, vec2));
#endif
  }

  auto elapsed = toc(t);
  printf("total =%f, time per call = %f ms\n", total, elapsed / double(N));
}

#endif

int main(int argc, char *argv[])
{
#if defined DO_BA
  // test_ba_old(dir_in + fn, dir_out + fn, nruns_f, nruns_J);
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


