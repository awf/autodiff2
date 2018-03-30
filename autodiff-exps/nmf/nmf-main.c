#include <stdio.h>
#include <string.h>
#include "../diffsmooth/fsharp.h"
#include "../diffsmooth/timer.h"

#if defined TAPENADE
  #if defined REV_MODE
    #include "../tapanade/submitted/3/nmf_b-all.h"
  #else
    #include "../tapanade/submitted/3/nmf_d-all.h"
  #endif
#endif

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

number_t vector_sum(array_number_t m) {
  number_t result = 0;
  for(int i=0; i<m->length; i++) {
    result += m->arr[i];
  }
  return result;
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
  array_array_number_t x15325 = (array_array_number_t)storage_alloc(sizeof(int) * 2);x15325->length=(m1)->length;x15325->arr = (array_number_t*)storage_alloc(sizeof(array_number_t) * (m1)->length);
  for(int ii = 0; ii < x15325->length; ii++){
    array_number_t x15324 = (array_number_t)storage_alloc(sizeof(int) * 2);x15324->length=((m1->arr[0]))->length;x15324->arr = (number_t*)storage_alloc(sizeof(number_t) * ((m1->arr[0]))->length);
    for(int jj = 0; jj < x15324->length; jj++){
      number_t x15323 = 0;
      for (int x15089 = 0; x15089 < (m2)->length; x15089++) {
        number_t x15167 = x15323;
        array_number_t x15273 = (m2->arr[x15089]);
        number_t x15322 = 0;
        for (int x15123 = 0; x15123 < (x15273)->length; x15123++) {
          number_t x15158 = x15322;
          x15158 = (x15158) + (((x15273->arr[x15123])) * (((m1->arr[x15123])->arr[jj])));
          x15322 = x15158;
        }
        
        x15167 = (x15167) + (((x15273->arr[ii])) / (x15322));
        x15323 = x15167;
      }
      
      x15324->arr[jj] = x15323;
      
    }
    x15325->arr[ii] = x15324;
    
  }
  return x15325;
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

array_array_number_t update3(array_array_number_t m1, array_array_number_t m2, array_array_number_t m3) {
  array_array_number_t x17885 = (array_array_number_t)storage_alloc(sizeof(int) * 2);x17885->length=(m1)->length;x17885->arr = (array_number_t*)storage_alloc(sizeof(array_number_t) * (m1)->length);
  for(int ii = 0; ii < x17885->length; ii++){
    array_number_t x17884 = (array_number_t)storage_alloc(sizeof(int) * 2);x17884->length=((m1->arr[0]))->length;x17884->arr = (number_t*)storage_alloc(sizeof(number_t) * ((m1->arr[0]))->length);
    for(int jj = 0; jj < x17884->length; jj++){
      number_t x17882 = 0;
      for (int x17308 = 0; x17308 < (m2)->length; x17308++) {
        number_t x17484 = x17882;
        array_number_t x17702 = (m2->arr[x17308]);
        number_t x17881 = 0;
        for (int x17370 = 0; x17370 < (x17702)->length; x17370++) {
          number_t x17475 = x17881;
          x17475 = (x17475) + (((x17702->arr[x17370])) * (((m1->arr[x17370])->arr[jj])));
          x17881 = x17475;
        }
        
        x17484 = (x17484) + (((x17702->arr[ii])) / (x17881));
        x17882 = x17484;
      }
      
      number_t x17883 = 0;
      for (int x17304 = 0; x17304 < (m3)->length; x17304++) {
        number_t x17464 = x17883;
        array_number_t x17878 = (m2->arr[x17304]);
        number_t x17880 = 0;
        for (int x17386 = 0; x17386 < (x17878)->length; x17386++) {
          number_t x17449 = x17880;
          x17449 = (x17449) + (((x17878->arr[x17386])) * (((m1->arr[x17386])->arr[jj])));
          x17880 = x17449;
        }
        
        x17464 = (x17464) + (((0) - ((((m3->arr[x17304])->arr[jj])) * ((x17878->arr[ii])))) / ((x17880) * (x17880)));
        // x17883 = x17464 + (((x17878->arr[ii])) / (x17880));
        x17883 = x17464;
      }
      
      // x17884->arr[jj] = x17883;
      x17884->arr[jj] = (x17882) + (x17883);
      
    }
    x17885->arr[ii] = x17884;
    
  }
  return x17885;
}

array_number_t nmf_uv(array_number_t u, array_number_t v, array_array_number_t AA) {
  array_number_t x20434 = (array_number_t)storage_alloc(sizeof(int) * 2);x20434->length=(u)->length;x20434->arr = (number_t*)storage_alloc(sizeof(number_t) * (u)->length);
  for(int i = 0; i < x20434->length; i++){
    number_t x20433 = 0;
    for (int x19178 = 0; x19178 < (v)->length; x19178++) {
      number_t x19286 = x20433;
      number_t x20430 = (v->arr[x19178]);
      number_t x20432 = (x20430) * ((u->arr[i]));
      number_t x20428 = (v->arr[x19178]);
      x19286 = (x19286) + (((x20428) / ((x20428) * ((u->arr[i])))) + (((0) - ((((AA->arr[x19178])->arr[i])) * (x20430))) / ((x20432) * (x20432))));
      x20433 = x19286;
    }
    
    x20434->arr[i] = x20433;
    
  }
  return x20434;
}

// I'm manually optimizing this code.
array_number_t nmf_uv_dps(storage_t s, int m, int n, array_number_t u, array_number_t v, array_array_number_t AA) {
  array_number_t x20434 = (array_number_t)s;
  for(int i = 0; i < n; i++){
    number_t x20433 = 0;
    number_t ui = u->arr[i];
    for (int x19178 = 0; x19178 < m; x19178++) {
      number_t x19286 = x20433;
      number_t x20430 = (v->arr[x19178]);
      number_t x20432 = (x20430) * ((ui));
      number_t x20428 = x20430;
      x19286 = (x19286) + ((1) / (((ui)))) + (((0) - ((((AA->arr[x19178])->arr[i]))) / ((ui) * (x20432))));
      x20433 = x19286;
    }
    
    x20434->arr[i] = x20433;
    
  }
  return x20434;
}

void test_nmf(card_t M, card_t N, card_t K, card_t iters)
{
  int rng = 42;
  srand(rng);
  array_array_number_t A = matrix_fill(M, N, 0.0);
  array_array_number_t W = matrix_fill(M, K, 0.0);
  array_array_number_t H = matrix_fill(K, N, 0.0);
  array_number_t v = vector_fill(M, 0.0);
  array_number_t ud = vector_fill(N, 0.0);
  double** A_arr = malloc(M * sizeof(double*));

  for (card_t m = 0; m < M; ++m) {
    for (card_t n = 0; n < N; ++n) {
      A->arr[m]->arr[n] = dist(rng);
    }
    A_arr[m] = A->arr[m]->arr;
    for (card_t k = 0; k < K; ++k) {
      W->arr[m]->arr[k] = dist(rng);
    }
    v->arr[m] = W->arr[m]->arr[0];
  }
  for (card_t k = 0; k < K; ++k) {
    for (card_t n = 0; n < N; ++n) {
      H->arr[k]->arr[n] = dist(rng);
    }
  }

  timer_t t = tic();

  double total = 0;

  array_number_t s = (array_number_t)storage_alloc(sizeof(int) * 2);s->length=N;s->arr = (number_t*)storage_alloc(sizeof(number_t) * N);
  for (card_t count = 0; count < iters; ++count) {
    H->arr[0]->arr[0] += 1.0 / (2.0 + H->arr[0]->arr[0]);
    W->arr[0]->arr[0] += 1.0 / (2.0 + W->arr[0]->arr[0]);
    v->arr[0] = W->arr[0]->arr[0];
    memset(ud->arr, 0, sizeof(double) * N);
    // total +=  matrix_sum(update1(H, W, A)) + matrix_sum(update2(H, W, A));
    // total += matrix_sum(update3(H, W, A));
    if(K == 1) {
      #if defined TAPENADE
        #if defined REV_MODE
          double eb = 1;
          nmfMain_b(N, M, H->arr[0]->arr, ud->arr, v->arr, A_arr, eb);
          total += vector_sum(ud);
        #else
          double sum = 0;
          double tmp;
          for(int i = 0; i<N; i++) {
            ud->arr[i] = 1;
            sum += nmfMain_d(N, M, H->arr[0]->arr, ud->arr, v->arr, A_arr, &tmp);
            ud->arr[i] = 0;
          }
          total += sum;
        #endif
      #else
        array_number_t tmp = nmf_uv(H->arr[0], v, A);
        total += vector_sum(tmp);
        // total += vector_sum(nmf_uv_dps(s, N, M, H->arr[0], v, A));
      #endif
    } else {
      total += matrix_sum(update3(H, W, A));
    }
  }

  double elapsed = toc2(t);
  printf("total =%f, time per call = %f s\n", total, elapsed / (double)(iters) / 1000.0);
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


