#pragma once

#include <stdio.h>
#include <math.h>

double sqsum(int n, double *x)
{
  int i;
  double res;
  res = 0;
  for (i = 0; i < n; i++)
    res = res + x[i] * x[i];
  return res;
}

void cross(double *a, double *b, double *out)
{
  out[0] = a[1] * b[2] - a[2] * b[1];
  out[1] = a[2] * b[0] - a[0] * b[2];
  out[2] = a[0] * b[1] - a[1] * b[0];
}

double dot_prod(int n, double *x, double *y) {
  double res = 0;
  for (int i = 0; i < n; i++)
    res += x[i] * y[i];
  return res;
}

void ba_rod_single(double *rot, double *pt, double *rotatedPt)
{
  int i;
  double sqtheta, theta, costheta, sintheta, theta_inverse, tmp;
  double *w = (double*)malloc(sizeof(double) * 3);
  double *cross_ = (double*)malloc(sizeof(double) * 3);

  sqtheta = sqsum(3, rot);
  theta = sqrt(sqtheta);
  costheta = cos(theta);
  sintheta = sin(theta);
  theta_inverse = 1.0 / theta;

  for (i = 0; i < 3; i++)
    w[i] = rot[i] * theta_inverse;

  cross(w, pt, cross_);

  tmp = dot_prod(3, w, pt) *
    (1. - costheta);

  for (i = 0; i < 3; i++)
    rotatedPt[i] = pt[i] * costheta + cross_[i] * sintheta + w[i] * tmp;
  free(w);
  free(cross_);
}

void ba_rod_native(int d, double* xs, int n, double** res) {
  for(int idx = 0; idx < n; idx++){
    int offset = (11) + ((d) * (idx));
    ba_rod_single(xs, &xs[offset], res[idx]);
  }
}
