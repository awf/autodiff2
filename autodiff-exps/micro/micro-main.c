#include <stdio.h>
#include <string.h>
#include <math.h>
#include "../diffsmooth/fsharp.h"
#include "../diffsmooth/timer.h"
// #include "../diffsmooth/ba_rod_fused.h"
// #include "../tapanade/submitted/9/ba_rod.h"

#if defined BA_ROD || BA_PROJ
  #if defined TAPENADE
    #if defined REV_MODE
      #include "../tapanade/submitted/9/ba_rod_b-all.h"
    #else
      #include "../tapanade/submitted/9/ba_rod_d-all.h"
    #endif
  #elif defined FUSED && defined NOUNROLL
    #include "../diffsmooth/ba_rod_jac_nounroll.h"
  #elif defined FUSED && defined DPS
    #include "../diffsmooth/ba_rod_jac_aos_dps.h"
  #elif defined FUSED && defined NOMOTION
    #include "../diffsmooth/ba_rod_jac_nomotion.h"
  #elif defined FUSED
    #include "../diffsmooth/ba_rod_jac_aos.h"
  #endif
#else
  #if defined TAPENADE
    #if defined REV_MODE
        #include "../tapanade/submitted/8/micro_b-all.h"
    #else
        #include "../tapanade/submitted/8/micro_d-all.h"
    #endif
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
  index_t x16761 = (v)->length;
  index_t x16766 = 0;
  for (int x15843 = 0; x15843 < x16761; x15843++) {
    index_t x15903 = x16766;
    number_t x16762 = (v->arr[x15903]);
    number_t x16763 = (v->arr[x15843]);
    index_t x16764 = (x16762) > (x16763);
    index_t x16765;
    if (x16764) {
      x16765 = x15903;
    } else {
      x16765 = x15843;
    }
    x15903 = x16765;
    x16766 = x15903;
  }
  
  number_t x16767 = (v->arr[x16766]);
  number_t x16773 = 0;
  for (int x15849 = 0; x15849 < x16761; x15849++) {
    number_t x15882 = x16773;
    number_t x16768 = (v->arr[x15849]);
    number_t x16770 = (x16768) - (x16767);
    number_t x16771 = exp(x16770);
    number_t x16772 = (x15882) + (x16771);
    x15882 = x16772;
    x16773 = x15882;
  }
  
  array_number_t x16790 = (array_number_t)storage_alloc(sizeof(int) * 2);x16790->length=x16761;x16790->arr = (number_t*)storage_alloc(sizeof(number_t) * x16761);
  for(int i = 0; i < x16790->length; i++){
    index_t x16774 = (i) == (x16766);
    number_t x16789;
    if (x16774) {
      number_t x16782 = 0;
      for (int x15849 = 0; x15849 < x16761; x15849++) {
        number_t x15883 = x16782;
        index_t x16775 = (i) == (x15849);
        number_t x16781;
        if (x16775) {
          x16781 = x15883;
        } else {
          number_t x16776 = (v->arr[x15849]);
          number_t x16777 = (x16776) - (x16767);
          number_t x16778 = exp(x16777);
          number_t x16779 = (-1) * (x16778);
          number_t x16780 = (x15883) + (x16779);
          x16781 = x16780;
        }
        x15883 = x16781;
        x16782 = x15883;
      }
      
      number_t x16783 = (x16782) / (x16773);
      number_t x16784 = (x16783) + (1);
      x16789 = x16784;
    } else {
      number_t x16785 = (v->arr[i]);
      number_t x16786 = (x16785) - (x16767);
      number_t x16787 = exp(x16786);
      number_t x16788 = (x16787) / (x16773);
      x16789 = x16788;
    }
    x16790->arr[i] = x16789;
    
  }
  return x16790;
}

array_number_t vectorLogsumexp_dps(storage_t st, array_number_t v) {
  index_t x16761 = (v)->length;
  index_t x16766 = 0;
  for (int x15843 = 0; x15843 < x16761; x15843++) {
    index_t x15903 = x16766;
    number_t x16762 = (v->arr[x15903]);
    number_t x16763 = (v->arr[x15843]);
    index_t x16764 = (x16762) > (x16763);
    index_t x16765;
    if (x16764) {
      x16765 = x15903;
    } else {
      x16765 = x15843;
    }
    x15903 = x16765;
    x16766 = x15903;
  }
  
  number_t x16767 = (v->arr[x16766]);
  number_t x16773 = 0;
  for (int x15849 = 0; x15849 < x16761; x15849++) {
    number_t x15882 = x16773;
    number_t x16768 = (v->arr[x15849]);
    number_t x16770 = (x16768) - (x16767);
    number_t x16771 = exp(x16770);
    number_t x16772 = (x15882) + (x16771);
    x15882 = x16772;
    x16773 = x15882;
  }
  
  array_number_t x16790 = (array_number_t)st;
  for(int i = 0; i < x16790->length; i++){
    index_t x16774 = (i) == (x16766);
    number_t x16789;
    if (x16774) {
      number_t x16782 = 0;
      for (int x15849 = 0; x15849 < x16761; x15849++) {
        number_t x15883 = x16782;
        index_t x16775 = (i) == (x15849);
        number_t x16781;
        if (x16775) {
          x16781 = x15883;
        } else {
          number_t x16776 = (v->arr[x15849]);
          number_t x16777 = (x16776) - (x16767);
          number_t x16778 = exp(x16777);
          number_t x16779 = (-1) * (x16778);
          number_t x16780 = (x15883) + (x16779);
          x16781 = x16780;
        }
        x15883 = x16781;
        x16782 = x15883;
      }
      
      number_t x16783 = (x16782) / (x16773);
      number_t x16784 = (x16783) + (1);
      x16789 = x16784;
    } else {
      number_t x16785 = (v->arr[i]);
      number_t x16786 = (x16785) - (x16767);
      number_t x16787 = exp(x16786);
      number_t x16788 = (x16787) / (x16773);
      x16789 = x16788;
    }
    x16790->arr[i] = x16789;
    
  }
  return x16790;
}

void vectorLogsumexp_dps_native(storage_t st, int n, double* v) {
  index_t x16761 = n;
  index_t x16766 = 0;
  for (int x15843 = 0; x15843 < x16761; x15843++) {
    index_t x15903 = x16766;
    number_t x16762 = (v[x15903]);
    number_t x16763 = (v[x15843]);
    index_t x16764 = (x16762) > (x16763);
    index_t x16765;
    if (x16764) {
      x16765 = x15903;
    } else {
      x16765 = x15843;
    }
    x15903 = x16765;
    x16766 = x15903;
  }
  
  number_t x16767 = (v[x16766]);
  number_t x16773 = 0;
  for (int x15849 = 0; x15849 < x16761; x15849++) {
    number_t x15882 = x16773;
    number_t x16768 = (v[x15849]);
    number_t x16770 = (x16768) - (x16767);
    number_t x16771 = exp(x16770);
    number_t x16772 = (x15882) + (x16771);
    x15882 = x16772;
    x16773 = x15882;
  }
  
  double* x16790 = (double*)st;
  for(int i = 0; i < n; i++){
    index_t x16774 = (i) == (x16766);
    number_t x16789;
    if (x16774) {
      number_t x16782 = 0;
      for (int x15849 = 0; x15849 < x16761; x15849++) {
        number_t x15883 = x16782;
        index_t x16775 = (i) == (x15849);
        number_t x16781;
        if (x16775) {
          x16781 = x15883;
        } else {
          number_t x16776 = (v[x15849]);
          number_t x16777 = (x16776) - (x16767);
          number_t x16778 = exp(x16777);
          number_t x16779 = (-1) * (x16778);
          number_t x16780 = (x15883) + (x16779);
          x16781 = x16780;
        }
        x15883 = x16781;
        x16782 = x15883;
      }
      
      number_t x16783 = (x16782) / (x16773);
      number_t x16784 = (x16783) + (1);
      x16789 = x16784;
    } else {
      number_t x16785 = (v[i]);
      number_t x16786 = (x16785) - (x16767);
      number_t x16787 = exp(x16786);
      number_t x16788 = (x16787) / (x16773);
      x16789 = x16788;
    }
    x16790[i] = x16789;
    
  }
}

double dist(int seed) {
  return ((double)rand()/(double)RAND_MAX);
}

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

array_array_array_number_t matrix3_fill(card_t rows, card_t cols, card_t cols3, number_t value) {
  array_array_array_number_t res = (array_array_array_number_t)storage_alloc(sizeof(int) * 2);
  res->length=rows;
  res->arr = (array_array_number_t*)storage_alloc(sizeof(array_number_t) * rows);
  for(int i = 0; i<rows; i++) {
    res->arr[i] = matrix_fill(cols, cols3, value);
  }
  return res;
}


double*** matrix3_pointer(array_array_array_number_t mat3) {
  double*** mat3_st = (double***)malloc(sizeof(double**) * mat3->length);
  for(int i = 0; i<mat3->length; i++) {
    double** mat3_st_r = (double**)malloc(sizeof(double*) * mat3->arr[0]->length);
    mat3_st[i] = mat3_st_r;
    for(int j = 0; j<mat3->arr[0]->length; j++) {
      mat3_st[i][j] = mat3->arr[i]->arr[j]->arr;
    }
  }
  return mat3_st;
}

double** matrix_pointer(array_array_number_t mat) {
  double** mat_st = (double**)malloc(sizeof(double*) * mat->length);
  for(int j = 0; j<mat->length; j++) {
    mat_st[j] = mat->arr[j]->arr;
  }
  return mat_st;
}

void vector_print(array_number_t arr) {
  printf("[");
  for (int i = 0; i < arr->length; i++) {
    printf("%f", arr->arr[i]);
    if (i != arr->length - 1)
      printf(", ");
  }
  printf("]\n");
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

number_t matrix3Sum(array_array_array_number_t m) {
  number_t result = 0;
  for(int i=0; i<m->length; i++) {
    for(int j=0; j<m->arr[0]->length; j++) {
      for(int k=0; k<m->arr[0]->arr[0]->length; k++) {
        result += m->arr[i]->arr[j]->arr[k];
      }
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
#if defined BA_ROD || defined BA_PROJ
  card_t OUT_N = (DIM - 11)/ 3;
  #if defined BA_ROD
    card_t OUT_DIM = 3;
  #else
    card_t OUT_DIM = 2;
  #endif
  array_array_array_number_t mat3_result = matrix3_fill(DIM, OUT_N, OUT_DIM, 0.0);
  // double*** mat3_result_st = (double***)malloc(sizeof(double**) * DIM);
  // for(int i = 0; i<DIM; i++) {
  //   double** mat3_result_st_r = (double**)malloc(sizeof(double*) * OUT_N);
  //   mat3_result_st[i] = mat3_result_st_r;
  //   for(int j = 0; j<OUT_N; j++) {
  //     mat3_result_st[i][j] = mat3_result->arr[i]->arr[j]->arr;
  //   }
  // }
  double*** mat3_result_st = matrix3_pointer(mat3_result);
  array_array_number_t mat2_result = matrix_fill(DIM, OUT_DIM, 0.0);
  // double** mat2_result_st = (double**)malloc(sizeof(double*) * DIM);
  // for(int i = 0; i<DIM; i++) {
  //   mat2_result_st[i] = mat2_result->arr[i]->arr;
  // }
  double** mat2_result_st = matrix_pointer(mat2_result);
  array_array_number_t mat2_result_2 = matrix_fill(DIM, OUT_DIM, 0.0);
  double** mat2_result_2_st = matrix_pointer(mat2_result_2);
  array_array_number_t mat4_result = matrix_fill(OUT_N, OUT_DIM, 0.0);
  double** mat4_result_st = matrix_pointer(mat4_result);
#endif

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
#elif defined LSE
  #if defined TAPENADE && defined REV_MODE
    memset(vec_result->arr, 0, DIM * sizeof(double));
    #if defined FUSED
    vec_logsumexp_b(DIM, vec1->arr, vec_result->arr, 1);
    #else
    vec_logsumexp_unfused_b(DIM, vec1->arr, vec_result->arr, 1);
    #endif
  #elif defined TAPENADE
    for(int i=0; i<DIM; i++) {
      double tmp_res;
      vec_tmp->arr[i] = 1;
      #if defined FUSED
      vec_result->arr[i] = vec_logsumexp_d(DIM, vec1->arr, vec_tmp->arr, &tmp_res);
      #else
      vec_result->arr[i] = vec_logsumexp_unfused_d(DIM, vec1->arr, vec_tmp->arr, &tmp_res);
      #endif
      vec_tmp->arr[i] = 0;
    }
  #elif defined DPS
    vectorLogsumexp_dps(vec_result, vec1);
    // vectorLogsumexp_dps_native(vec_result->arr, vec1->length, vec1->arr);
  #else
    vec_result = vectorLogsumexp(vec1);
  #endif
    total += vector_sum(vec_result);
#elif defined BA_ROD || defined BA_PROJ
    #if defined TAPENADE && defined REV_MODE
    for(int j=0; j<OUT_N; j++) {
      for(int k=0; k<OUT_DIM; k++) {
        memset(vec_result->arr, 0, DIM * sizeof(double));
        mat2_result_2_st[j][k] = 1;
        #if defined BA_ROD
          ba_rod_native_b(3, vec1->arr, vec_result->arr, OUT_N, mat2_result_st, mat2_result_2_st);
        #else
          ba_proj_native_b(3, vec1->arr, vec_result->arr, OUT_N, mat2_result_st, mat2_result_2_st);
        #endif
        mat2_result_2_st[j][k] = 0;
        for(int i=0; i<DIM; i++) {
          mat3_result_st[i][j][k] = vec_result->arr[i];
        }
      }
    }
    #elif defined TAPENADE
    double** tmp = mat2_result_st;
    for(int i=0; i<DIM; i++) {
      vec_tmp->arr[i] = 1;
      #if defined BA_ROD
        ba_rod_native_d(3, vec1->arr, vec_tmp->arr, OUT_N, tmp, mat3_result_st[i]);
      #else
        ba_proj_native_d(3, vec1->arr, vec_tmp->arr, OUT_N, tmp, mat3_result_st[i]);
      #endif
      vec_tmp->arr[i] = 0;
    }
    // ba_proj_native(3, vec1->arr, OUT_N, mat4_result_st);
    #elif defined DPS
    #if defined BA_ROD
        ba_rod_jac_dps(mat3_result, vec1, OUT_N);
      #else
        ba_proj_jac_dps(mat3_result, vec1, OUT_N);
      #endif
    #else
      #if defined BA_ROD
        mat3_result = ba_rod_jac(vec1, OUT_N);
      #else
        mat3_result = ba_proj_jac(vec1, OUT_N);
      #endif
      // mat4_result = ba_proj(vec1, OUT_N);
    #endif
    // matrix_print(mat3_result->arr[0]);
    total += matrix3Sum(mat3_result);
    // matrix_print(mat4_result);
    // total += matrixSum(mat4_result);
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
