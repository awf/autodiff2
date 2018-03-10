#include <stdio.h>

#include "../diffsmooth/fsharp.h"
#include "../diffsmooth/timer.h"


double dist(int seed) {
  return ((double)rand()/(double)RAND_MAX);
}

array_array_number_t TOP_LEVEL_linalg_matrixFill(card_t rows, card_t cols, number_t value) {
  array_array_number_t macroDef79 = (array_array_number_t)malloc(sizeof(int) * 2);
  macroDef79->length=rows;
  macroDef79->arr = (array_number_t*)malloc(sizeof(array_number_t) * rows);
    for(int r = 0; r < macroDef79->length; r++){
      array_number_t macroDef78 = (array_number_t)malloc(sizeof(int) * 2);
  macroDef78->length=cols;
  macroDef78->arr = (number_t*)malloc(sizeof(number_t) * cols);
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

number_t matrix_sum(array_array_number_t m) {
  number_t result = 0;
  for(int i=0; i<m->length; i++) {
    for(int j=0; j<m->arr[0]->length; j++) {
      result += m->arr[i]->arr[j];
    }
  }
  return result;
}

array_array_number_t update1(array_array_number_t m1, array_array_number_t m2, array_array_number_t m3) {
  array_array_number_t x11230 = (array_array_number_t)storage_alloc(sizeof(int) * 2);x11230->length=(m1)->length;x11230->arr = (array_number_t*)storage_alloc(sizeof(array_number_t) * (m1)->length);
  for(int ii = 0; ii < x11230->length; ii++){
    array_number_t x11229 = (array_number_t)storage_alloc(sizeof(int) * 2);x11229->length=((m1->arr[0]))->length;x11229->arr = (number_t*)storage_alloc(sizeof(number_t) * ((m1->arr[0]))->length);
    for(int jj = 0; jj < x11229->length; jj++){
      number_t x11072 = 0;
      for (int x10994 = 0; x10994 < (m2)->length; x10994++) {
        array_number_t x11178 = (m2->arr[x10994]);
        number_t x11063 = 0;
        for (int x11028 = 0; x11028 < (x11178)->length; x11028++) {
          x11063 = (x11063) + (((x11178->arr[x11028])) * (((m1->arr[x11028])->arr[jj])));
        }
        number_t x11227 = x11063;
        x11072 = (x11072) + (((x11178->arr[ii])) * ((1) * ((1) / (x11227))));
      }
      number_t x11228 = x11072;
      
      x11229->arr[jj] = x11228;
      
    }
    x11230->arr[ii] = x11229;
    
  }
  return x11230;
}

array_array_number_t update2(array_array_number_t m1, array_array_number_t m2, array_array_number_t m3) {
  array_array_number_t x11635 = (array_array_number_t)storage_alloc(sizeof(int) * 2);x11635->length=(m1)->length;x11635->arr = (array_number_t*)storage_alloc(sizeof(array_number_t) * (m1)->length);
  for(int ii = 0; ii < x11635->length; ii++){
    array_number_t x11634 = (array_number_t)storage_alloc(sizeof(int) * 2);x11634->length=((m1->arr[0]))->length;x11634->arr = (number_t*)storage_alloc(sizeof(number_t) * ((m1->arr[0]))->length);
    for(int jj = 0; jj < x11634->length; jj++){
      number_t x11402 = 0;
      for (int x11264 = 0; x11264 < (m3)->length; x11264++) {
        array_number_t x11630 = (m2->arr[x11264]);
        number_t x11379 = 0;
        for (int x11332 = 0; x11332 < (x11630)->length; x11332++) {
          x11379 = (x11379) + (((x11630->arr[x11332])) * (((m1->arr[x11332])->arr[jj])));
        }
        number_t x11632 = x11379;
        
        x11402 = (x11402) + ((((m3->arr[x11264])->arr[jj])) * (((0) - ((x11630->arr[ii]))) * ((1) * ((1) / ((x11632) * (x11632))))));
      }
      number_t x11633 = x11402;
      
      x11634->arr[jj] = x11633;
      
    }
    x11635->arr[ii] = x11634;
    
  }
  return x11635;
}

void test_nmf(card_t M, card_t N, card_t K, card_t iters)
{
  int rng = 42;
  srand(rng);
  array_array_number_t A = matrix_fill(M, N, 0.0);
  array_array_number_t W = matrix_fill(M, K, 0.0);
  array_array_number_t H = matrix_fill(K, N, 0.0);

  for (card_t m = 0; m < M; ++m) {
    for (card_t n = 0; n < N; ++n) {
      A->arr[m]->arr[n] = dist(rng);
    }
    for (card_t k = 0; k < K; ++k) {
      W->arr[m]->arr[k] = dist(rng);
    }
  }
  for (card_t k = 0; k < K; ++k) {
    for (card_t n = 0; n < N; ++n) {
      H->arr[k]->arr[n] = dist(rng);
    }
  }

  timer_t t = tic();

  double total = 0;

  for (card_t count = 0; count < iters; ++count) {
    H->arr[0]->arr[0] += 1.0 / (2.0 + H->arr[0]->arr[0]);
    W->arr[0]->arr[0] += 1.0 / (2.0 + W->arr[0]->arr[0]);
    total +=  matrix_sum(update1(H, W, A)) + matrix_sum(update2(H, W, A));
  }

  double elapsed = toc2(t);
  printf("total =%f, time per call = %f ms\n", total, elapsed / (double)(iters));
}

int main(int argc, char *argv[])
{
  if(argc != 5) {
    printf("You should use the following format for running this program: %s <M> <N> <K> <Number of Iterations>\n", argv[0]);
    exit(1);
  }
  card_t M = atoi(argv[1]);
  card_t N = atoi(argv[2]);
  card_t K = atoi(argv[3]);
  card_t iters = atoi(argv[4]);
  test_nmf(M, N, K, iters);
}


