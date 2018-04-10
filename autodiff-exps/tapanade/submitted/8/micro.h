#pragma once
#include <math.h>

double* vec_add(int n, double* x, double* y) {
  double* res = malloc(n * sizeof(double));
  for(int i = 0; i< n; i++) {
  	res[i] = x[i] + y[i];
  }
  return res;
}

double* vec_elem_mult(int n, double* x, double* y) {
  double* res = malloc(n * sizeof(double));
  for(int i = 0; i< n; i++) {
  	res[i] = x[i] * y[i];
  }
  return res;
}

double* vec_scal_mult(int n, double* x, double y) {
  double* res = malloc(n * sizeof(double));
  for(int i = 0; i< n; i++) {
  	res[i] = x[i] * y * y;
  }
  return res;
}

double vec_dot(int n, double* x, double* y) {
  double res = 0;
  for(int i = 0; i< n; i++) {
    res += x[i] * y[i];
  }
  return res;
}

double vec_max(int n, double* v) {
  int x25608 = 0;
  for (int idx = 0; idx < n; idx++) {
    int acc = x25608;
    int x25607;
    if (v[acc] > v[idx]) {
      x25607 = acc;
    } else {
      x25607 = idx;
    }
    acc = x25607;
    x25608 = acc;
  }
  return v[x25608];
}

double vec_logsumexp(int n, double* v) {
  double mx = vec_max(n, v);
  double x25609 = 0;
  for (int idx = 0; idx < n; idx++) {
    double acc = x25609;
    acc = (acc) + (exp(((v[idx])) - (mx)));
    x25609 = acc;
  }
  return (log(x25609)) + (mx);
}

