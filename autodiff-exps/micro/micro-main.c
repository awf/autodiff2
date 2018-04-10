#include <stdio.h>
#include <string.h>
#include <math.h>
#include "../diffsmooth/fsharp.h"
#include "../diffsmooth/timer.h"

#if defined TAPENADE
  #if defined REV_MODE
    // #if defined UNFUSED
    //   #include "../tapanade/submitted/4/nmf_unfused_b-all.h"
    // #else
      #include "../tapanade/submitted/8/micro_b-all.h"
    // #endif
  #else
    // #if defined UNFUSED
    //   #include "../tapanade/submitted/4/nmf_unfused_d-all.h"
    // #else
      #include "../tapanade/submitted/8/micro_d-all.h"
    // #endif
  #endif
#endif

array_array_number_t vectorElemProd(array_number_t v1, array_number_t v2) {
  array_array_number_t x21447 = (array_array_number_t)storage_alloc(sizeof(int) * 2);x21447->length=(v1)->length;x21447->arr = (array_number_t*)storage_alloc(sizeof(array_number_t) * (v1)->length);
  for(int i = 0; i < x21447->length; i++){
    array_number_t x21446 = (array_number_t)storage_alloc(sizeof(int) * 2);x21446->length=(v1)->length;x21446->arr = (number_t*)storage_alloc(sizeof(number_t) * (v1)->length);
    for(int i0 = 0; i0 < x21446->length; i0++){
      number_t x21445;
      if ((i) == (i0)) {
        x21445 = (v2->arr[i0]);
      } else {
        x21445 = 0;
      }
      x21446->arr[i0] = x21445;
      
    }
    x21447->arr[i] = x21446;
    
  }
  return x21447;
}

array_array_number_t vectorAdd(array_number_t v1, array_number_t v2) {
  array_array_number_t x21413 = (array_array_number_t)storage_alloc(sizeof(int) * 2);x21413->length=(v1)->length;x21413->arr = (array_number_t*)storage_alloc(sizeof(array_number_t) * (v1)->length);
  for(int i = 0; i < x21413->length; i++){
    array_number_t x21412 = (array_number_t)storage_alloc(sizeof(int) * 2);x21412->length=(v1)->length;x21412->arr = (number_t*)storage_alloc(sizeof(number_t) * (v1)->length);
    for(int i0 = 0; i0 < x21412->length; i0++){
      number_t x21411;
      if ((i) == (i0)) {
        x21411 = 1;
      } else {
        x21411 = 0;
      }
      x21412->arr[i0] = x21411;
      
    }
    x21413->arr[i] = x21412;
    
  }
  return x21413;
}

array_array_number_t vectorAdd_dps(storage_t s, array_number_t v1, array_number_t v2) {
  array_array_number_t x21413 = (array_array_number_t)s;
  for(int i = 0; i < x21413->length; i++){
    array_number_t x21412 = (array_number_t)x21413->arr[i];
    for(int i0 = 0; i0 < x21412->length; i0++){
      number_t x21411;
      if ((i) == (i0)) {
        x21411 = 1;
      } else {
        x21411 = 0;
      }
      x21412->arr[i0] = x21411;
      
    }
  }
  return x21413;
}

array_number_t vectorMultScalar(array_number_t v, number_t s) {
  array_number_t x21495 = (array_number_t)storage_alloc(sizeof(int) * 2);x21495->length=(v)->length;x21495->arr = (number_t*)storage_alloc(sizeof(number_t) * (v)->length);
  for(int i = 0; i < x21495->length; i++){
    x21495->arr[i] = ((v->arr[i])) * ((s) + (s));
    
  }
  return x21495;
}

array_number_t vectorMultScalar_dps(storage_t st, array_number_t v, number_t s) {
  array_number_t x21495 = (array_number_t)st;
  for(int i = 0; i < x21495->length; i++){
    x21495->arr[i] = ((v->arr[i])) * ((s) + (s));
    
  }
  return x21495;
}

array_number_t vectorDot(array_number_t v1, array_number_t v2) {
  array_number_t x21819 = (array_number_t)storage_alloc(sizeof(int) * 2);x21819->length=(v1)->length;x21819->arr = (number_t*)storage_alloc(sizeof(number_t) * (v1)->length);
  for(int i = 0; i < x21819->length; i++){
    x21819->arr[i] = (v2->arr[i]);
    
  }
  return x21819;
}

array_number_t vectorDot_dps(storage_t st, array_number_t v1, array_number_t v2) {
  array_number_t x21819 = (array_number_t)st;
  for(int i = 0; i < x21819->length; i++){
    x21819->arr[i] = (v2->arr[i]);
    
  }
  return x21819;
}

array_number_t vectorMax(array_number_t v) {
  index_t x24497 = 0;
  for (int x24485 = 0; x24485 < (v)->length; x24485++) {
    index_t x24495 = x24497;
    index_t x24496;
    if (((v->arr[x24495])) > ((v->arr[x24485]))) {
      x24496 = x24495;
    } else {
      x24496 = x24485;
    }
    x24495 = x24496;
    x24497 = x24495;
  }
  
  array_number_t x24499 = (array_number_t)storage_alloc(sizeof(int) * 2);x24499->length=(v)->length;x24499->arr = (number_t*)storage_alloc(sizeof(number_t) * (v)->length);
  for(int i = 0; i < x24499->length; i++){
    number_t x24498;
    if ((i) == (x24497)) {
      x24498 = 1;
    } else {
      x24498 = 0;
    }
    x24499->arr[i] = x24498;
    
  }
  return x24499;
}

array_number_t vectorMax_dps(storage_t st, array_number_t v) {
  index_t x24497 = 0;
  for (int x24485 = 0; x24485 < (v)->length; x24485++) {
    index_t x24495 = x24497;
    index_t x24496;
    if (((v->arr[x24495])) > ((v->arr[x24485]))) {
      x24496 = x24495;
    } else {
      x24496 = x24485;
    }
    x24495 = x24496;
    x24497 = x24495;
  }
  
  array_number_t x24499 = (array_number_t)st;
  for(int i = 0; i < x24499->length; i++){
    number_t x24498;
    if ((i) == (x24497)) {
      x24498 = 1;
    } else {
      x24498 = 0;
    }
    x24499->arr[i] = x24498;
    
  }
  return x24499;
}



array_number_t vectorLogsumexp(array_number_t v) {
  index_t x25581 = (v)->length;
  index_t x25586 = 0;
  for (int x24663 = 0; x24663 < x25581; x24663++) {
    index_t x24723 = x25586;
    number_t x25582 = (v->arr[x24723]);
    number_t x25583 = (v->arr[x24663]);
    index_t x25584 = (x25582) > (x25583);
    index_t x25585;
    if (x25584) {
      x25585 = x24723;
    } else {
      x25585 = x24663;
    }
    x24723 = x25585;
    x25586 = x24723;
  }
  
  number_t x25587 = (v->arr[x25586]);
  number_t x25593 = 0;
  for (int x24669 = 0; x24669 < x25581; x24669++) {
    number_t x24702 = x25593;
    number_t x25588 = (v->arr[x24669]);
    number_t x25590 = (x25588) - (x25587);
    number_t x25591 = exp(x25590);
    number_t x25592 = (x24702) + (x25591);
    x24702 = x25592;
    x25593 = x24702;
  }
  
  array_number_t x25606 = (array_number_t)storage_alloc(sizeof(int) * 2);x25606->length=x25581;x25606->arr = (number_t*)storage_alloc(sizeof(number_t) * x25581);
  for(int i = 0; i < x25606->length; i++){
    index_t x25594 = (i) == (x25586);
    number_t x25601 = (v->arr[i]);
    number_t x25602 = (x25601) - (x25587);
    number_t x25603 = exp(x25602);
    number_t x25605;
    if (x25594) {
      number_t x25598 = (-1) * (x25603);
      number_t x25599 = (x25598) / (x25593);
      number_t x25600 = (x25599) + (1);
      x25605 = x25600;
    } else {
      number_t x25604 = (x25603) / (x25593);
      x25605 = x25604;
    }
    x25606->arr[i] = x25605;
    
  }
  return x25606;
}

array_number_t vectorLogsumexp_dps(storage_t st, array_number_t v) {
  index_t x25581 = (v)->length;
  index_t x25586 = 0;
  for (int x24663 = 0; x24663 < x25581; x24663++) {
    index_t x24723 = x25586;
    number_t x25582 = (v->arr[x24723]);
    number_t x25583 = (v->arr[x24663]);
    index_t x25584 = (x25582) > (x25583);
    index_t x25585;
    if (x25584) {
      x25585 = x24723;
    } else {
      x25585 = x24663;
    }
    x24723 = x25585;
    x25586 = x24723;
  }
  
  number_t x25587 = (v->arr[x25586]);
  number_t x25593 = 0;
  for (int x24669 = 0; x24669 < x25581; x24669++) {
    number_t x24702 = x25593;
    number_t x25588 = (v->arr[x24669]);
    number_t x25590 = (x25588) - (x25587);
    number_t x25591 = exp(x25590);
    number_t x25592 = (x24702) + (x25591);
    x24702 = x25592;
    x25593 = x24702;
  }
  
  array_number_t x25606 = (array_number_t)st;
  for(int i = 0; i < x25606->length; i++){
    index_t x25594 = (i) == (x25586);
    number_t x25601 = (v->arr[i]);
    number_t x25602 = (x25601) - (x25587);
    number_t x25603 = exp(x25602);
    number_t x25605;
    if (x25594) {
      number_t x25598 = (-1) * (x25603);
      number_t x25599 = (x25598) / (x25593);
      number_t x25600 = (x25599) + (1);
      x25605 = x25600;
    } else {
      number_t x25604 = (x25603) / (x25593);
      x25605 = x25604;
    }
    x25606->arr[i] = x25605;
    
  }
  return x25606;
}


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

number_t matrixSum(array_array_number_t m) {
  number_t result = 0;
  for(int i=0; i<m->length; i++) {
    for(int j=0; j<m->arr[0]->length; j++) {
      result += m->arr[i]->arr[j];
    }
  }
  return result;
}

void test_micro(card_t DIM, card_t iters)
{
  int rng = 42;
  srand(rng);
  array_number_t vec1 = vector_fill(DIM, 0.0);
  array_number_t vec2 = vector_fill(DIM, 0.0);
  array_number_t vec_result = vector_fill(DIM, 0.0);
  array_array_number_t mat_result = matrix_fill(DIM, DIM, 0.0);
  array_number_t vec_tmp = vector_fill(DIM, 0.0);
  array_number_t vec_tmp2 = vector_fill(DIM, 0.0);

  for (card_t k = 0; k < DIM; ++k) {
    vec1->arr[k] = dist(rng);
    vec2->arr[k] = dist(rng);
  }

  timer_t t = tic();

  double total = 0;

  for (card_t count = 0; count < iters; ++count) {
    vec1->arr[0] += 1.0 / (2.0 + vec1->arr[0]);
    vec2->arr[1] += 1.0 / (2.0 + vec2->arr[1]);
#if defined MULTS
  #if defined TAPENADE && defined REV_MODE
    for(int i=0; i<DIM; i++) {
      double tmp = 0;
      vec_tmp->arr[i] = 1;
      vec_scal_mult_b(DIM, vec1->arr, vec2->arr[1], &tmp, vec_tmp->arr);
      vec_result->arr[i] = tmp;
      vec_tmp->arr[i] = 0;
    }
  #elif defined TAPENADE
    double** tmp = &vec_tmp->arr;
    vec_result->arr = vec_scal_mult_d(DIM, vec1->arr, vec2->arr[1], 1, tmp);
  #elif defined DPS
    vectorMultScalar_dps(vec_result, vec1, vec2->arr[1]);
  #else
    vec_result = vectorMultScalar(vec1, vec2->arr[1]);
  #endif
    total += vector_sum(vec_result);
#elif defined ADD
  #if defined TAPENADE && defined REV_MODE
    double** tmp = &vec_result->arr;
    for(int i=0; i<DIM; i++) {
      memset(mat_result->arr[i]->arr, 0, DIM * sizeof(double));
      vec_tmp->arr[i] = 1;
      vec_add_b(DIM, vec1->arr, mat_result->arr[i]->arr, vec2->arr, vec_tmp->arr);
      vec_tmp->arr[i] = 0;
    }
  #elif defined TAPENADE
    double** tmp = &vec_result->arr;
    for(int i=0; i<DIM; i++) {
      vec_tmp->arr[i] = 1;
      mat_result->arr[i]->arr = vec_add_d(DIM, vec1->arr, vec_tmp->arr, vec2->arr, tmp);
      vec_tmp->arr[i] = 0;
    }
  #elif defined DPS
    vectorAdd_dps(mat_result, vec1, vec2);
  #else
    mat_result = vectorAdd(vec1, vec2);
    // vec_result = vectorMultScalar(vec1, vec2->arr[1]);
  #endif
    total += matrixSum(mat_result);
#elif defined DOT
  #if defined TAPENADE && defined REV_MODE
    memset(vec_result->arr, 0, DIM * sizeof(double));
    vec_dot_b(DIM, vec1->arr, vec_result->arr, vec2->arr, 1);
  #elif defined TAPENADE
    for(int i=0; i<DIM; i++) {
      double tmp_res;
      vec_tmp->arr[i] = 1;
      vec_result->arr[i] = vec_dot_d(DIM, vec1->arr, vec_tmp->arr, vec2->arr, &tmp_res);
      vec_tmp->arr[i] = 0;
    }
  #elif defined DPS
    vectorDot_dps(vec_result, vec1, vec2);
  #else
    vec_result = vectorDot(vec1, vec2);
  #endif
    total += vector_sum(vec_result);
#elif defined VEC_MAX
  #if defined TAPENADE && defined REV_MODE
    memset(vec_result->arr, 0, DIM * sizeof(double));
    vec_max_b(DIM, vec1->arr, vec_result->arr, 1);
  #elif defined TAPENADE
    for(int i=0; i<DIM; i++) {
      double tmp_res;
      vec_tmp->arr[i] = 1;
      vec_result->arr[i] = vec_max_d(DIM, vec1->arr, vec_tmp->arr, &tmp_res);
      vec_tmp->arr[i] = 0;
    }
  #elif defined DPS
    vectorMax_dps(vec_result, vec1);
  #else
    vec_result = vectorMax(vec1);
  #endif
    total += vector_sum(vec_result);
#endif
  }

  double elapsed = toc2(t);
  printf("total =%f, time per call = %f ms\n", total, elapsed / (double)(iters));
}

int main(int argc, char *argv[])
{
  if(argc != 3) {
    printf("You should use the following format for running this program: %s <DIM> <Number of Iterations>\n", argv[0]);
    exit(1);
  }
  card_t DIM = atoi(argv[1]);
  card_t iters = atoi(argv[2]);
  test_micro(DIM, iters);
}
