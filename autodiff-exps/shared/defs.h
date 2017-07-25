#pragma once

#ifndef NBDirsMax
#define NBDirsMax 1650
#endif

#define NBDirsMaxReproj_BV 2

#ifndef PI
#define PI 3.14159265359
#endif

typedef struct
{
  double gamma;
  int m;
} Wishart;

#define BA_NCAMPARAMS 11
#define BA_ROT_IDX 0
#define BA_C_IDX 3
#define BA_F_IDX 6
#define BA_X0_IDX 7
#define BA_RAD_IDX 9

//# Flexion, Abduction, Twist = 'xzy'
#define HAND_XYZ_TO_ROTATIONAL_PARAMETERIZATION {0, 2, 1} 

template<typename T>
T dot(int n, const T* const x, const T* const y)
{
  T res = 0;
  for (int i = 0; i < n; i++)
    res = res + x[i] * y[i];
  return res;
}

