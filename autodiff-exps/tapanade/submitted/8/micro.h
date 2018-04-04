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
