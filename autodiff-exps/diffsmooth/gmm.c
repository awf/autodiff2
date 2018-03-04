#include <stdlib.h>
#include <math.h>
#include <float.h>
#include "gmm.h"
#include "usecases_gmm_opt.h"


#ifdef FUSED
#include "usecases_gmm_opt_d.h"
#else
// #include "usecases_gmm_d.h" // TODO
#endif

array_array_number_t TOP_LEVEL_linalg_matrixFill(card_t rows, card_t cols, number_t value) {
	array_array_number_t macroDef79 = (array_array_number_t)storage_alloc(sizeof(int) * 2);
	macroDef79->length=rows;
	macroDef79->arr = (array_number_t*)storage_alloc(sizeof(array_number_t) * rows);
		for(int r = 0; r < macroDef79->length; r++){
			array_number_t macroDef78 = (array_number_t)storage_alloc(sizeof(int) * 2);
	macroDef78->length=cols;
	macroDef78->arr = (number_t*)storage_alloc(sizeof(number_t) * cols);
		for(int c = 0; c < macroDef78->length; c++){
			
			macroDef78->arr[c] = value;;
		}
			macroDef79->arr[r] = macroDef78;;
		}
	return macroDef79;
}

array_array_number_t matrix_fill(card_t rows, card_t cols, number_t value) {
  return TOP_LEVEL_linalg_matrixFill(rows, cols, value);
}

array_number_t vector_fill(card_t rows, number_t value) {
  return matrix_fill(1, rows, value)->arr[0];
}

int K, d, n;
size_t td;
array_number_t alphas;
array_array_number_t means;
array_array_number_t qs;
array_array_number_t ls;
array_array_number_t xs;
array_number_t alphasd;
array_array_number_t meansd;
array_array_number_t qsd;
array_array_number_t lsd;
array_array_number_t xsd;

void gmm_init(int d_p, int k_p, int n_p) {
  K = k_p;
  d = d_p;
  n = n_p;
  printf("gmm_init K=%d, d=%d, n=%d\n", K, d, n);
  td = TOP_LEVEL_usecases_gmm_tri(d);
  alphas = vector_fill(K, 0);
  means = matrix_fill(K, d, 0);
  qs = matrix_fill(K, d, 0);
  ls = matrix_fill(K, td, 0);
  xs = matrix_fill(n, d, 0);
  alphasd = vector_fill(K, 0);
  meansd = matrix_fill(K, d, 0);
  qsd = matrix_fill(K, d, 0);
  lsd = matrix_fill(K, td, 0);
  xsd = matrix_fill(n, d, 0);
}

void gmm_objective(int d_p, int k_p, int n_p,
  double* alphas_arr, 
  double* means_arr,
  double* icf_arr, 
  double* x_arr,
  double wishart_gamma, 
  double wishart_m,
  double *err) {
  // alphas->arr = alphas_arr;
  // for (int k = 0; k < K; ++k) {
  // 	means->arr[k]->arr = &means_arr[k*d];
  // 	qs->arr[k]->arr = &means_arr[k*d];
  // 	ls->arr[k]->arr = &means_arr[k*d];
  // }
  *err = TOP_LEVEL_usecases_gmm_gmm_objective(xs, alphas, means, qs, ls, wishart_gamma, wishart_m);
}
void gmm_objective_d(int d, int k, int n, double *alphas_arr, double *alphasd_arr, 
        double *means_arr, double *meansd_arr, double *icf_arr, double *icfd_arr, double *x_arr, 
        double *xd_arr, double wishart_gamma, double wishart_m, double *err, 
        double *errd) {
  // alphas->arr = alphas_arr;
  // for (int k = 0; k < K; ++k) {
  // 	means->arr[k]->arr = &means_arr[k*d];
  // 	qs->arr[k]->arr = &means_arr[k*d];
  // 	ls->arr[k]->arr = &means_arr[k*d];
  // }
  *errd = TOP_LEVEL_usecases_gmm_gmm_objective_d(xs, alphas, means, qs, ls, wishart_gamma, wishart_m, xsd, alphasd, meansd, qsd, lsd, 0, 0);
}
