#pragma once

#include "fsharp.h"
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

void ba_rod_single(double *rot, double *pt, double *rotatedPt)
{
  int i;
  double sqtheta, theta, costheta, sintheta, theta_inverse,
    w[3], cross_[3], tmp;

  sqtheta = sqsum(3, rot);
  theta = sqrt(sqtheta);
  costheta = cos(theta);
  sintheta = sin(theta);
  theta_inverse = 1.0 / theta;

  for (i = 0; i < 3; i++)
    w[i] = rot[i] * theta_inverse;

  cross(w, pt, cross_);

  tmp = (w[0] * pt[0] + w[1] * pt[1] + w[2] * pt[2]) *
    (1. - costheta);

  for (i = 0; i < 3; i++)
    rotatedPt[i] = pt[i] * costheta + cross_[i] * sintheta + w[i] * tmp;
}

array_array_number_t ba_rod(array_number_t xs, index_t n) {
  array_array_number_t x5937 = (array_array_number_t)storage_alloc(sizeof(int) * 2);x5937->length=n;x5937->arr = (array_number_t*)storage_alloc(sizeof(array_number_t) * n);
  for(int idx = 0; idx < x5937->length; idx++){
    array_number_t m = (array_number_t)storage_alloc(sizeof(int) * 2);m->length=3;m->arr = (number_t*)storage_alloc(sizeof(number_t) * 3);
    index_t offset = (11) + ((3) * (idx));
    ba_rod_single(xs->arr, &xs->arr[offset], m->arr);
    x5937->arr[idx] = m;
  }
  return x5937;
}