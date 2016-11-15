// benchmark_gmm.cpp : Defines the entry point for the console application.
//


#include "stdafx.h"
#include <random>

#include "usecases_ht.h"

std::mt19937 rng(42);

template <class T, size_t Size, class DIST>
void fillrand(Vec<T, Size>* vec, DIST& dist)
{
  for (int k = 0; k < vec->size(); ++k)
    (*vec)[k] = dist(rng);
}

int main()
{
  std::uniform_real_distribution<Real> dist(0, 1);
  auto rand = [&dist] { return dist(rng); };

  Vec<Real> theta{ 26 };
  size_t n_bones = 15;
  size_t n_verts = 500;

  fillrand(&theta, std::uniform_real_distribution<Real>(-1, 1));

  Mat<Real, 3, N_VERTS> base_positions{ 3, n_verts };
  for (int i = 0; i < n_verts; ++i)
    fillrand(&base_positions[i], std::uniform_real_distribution<Real>(1, 10));

  std::vector<Real4x4> base_relatives{ n_bones };
  for (int i = 0; i < n_bones; ++i) {
    Vec<Real, 3> rvec; fillrand(&rvec, std::uniform_real_distribution<Real>(-2, 2));
    Vec<Real, 3> tvec; fillrand(&tvec, std::uniform_real_distribution<Real>(1, 2));
    base_relatives[i] = Rt_to_transform(angle_axis_to_rotation_matrix(rvec), tvec);
  }
    
  std::vector<int> parents{ 
    -1,  0,  1, 
    -1,  3,  4,
    -1,  6,  7,
    -1,  9, 10,
    -1, 12, 13,
    };

  Mat<Real, N_VERTS, N_BONES> weights{ n_verts, n_bones };
  for (int i = 0; i < n_verts; ++i) 
    for (int j = 0; j < n_bones; ++j) {
      if (rand() < 4.0 / n_bones)
        weights[j][i] = rand();
    }


  boost::timer::auto_cpu_timer t;

  // Debug 150s 
  // Release 1s
  double total = 0;
  size_t N = 1000;
#ifdef _DEBUG
  N = N / 10;  // Debug is roughly this much slower than release -- multiply timings.
#endif
  for (size_t count = 0; count < N; ++count) {
    std::vector<Vec3<Real>> pose_params = to_pose_params(theta, n_bones);
      
    Mat<Real, 3, N_VERTS> verts = get_skinned_vertex_positions(base_relatives, parents, base_positions, weights, pose_params);

    total += sumsq(verts[1]);
  }

  std::cout << "total =" << total << ", time per call = " << t.elapsed().wall / double(N) / 1e6 << "ms" << std::endl;

  return 0;
}
