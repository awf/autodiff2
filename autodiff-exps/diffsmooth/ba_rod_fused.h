#pragma once

#include "fsharp.h"
#include <stdio.h>
#include <math.h>

array_array_number_t ba_rod(array_number_t xs, index_t n) {
  array_array_number_t x5985 = (array_array_number_t)storage_alloc(sizeof(int) * 2);x5985->length=n;x5985->arr = (array_number_t*)storage_alloc(sizeof(array_number_t) * n);
  for(int idx = 0; idx < x5985->length; idx++){
    index_t offset = (11) + ((3) * (idx));
    number_t sqtheta = 0;
    for (int idx0 = 0; idx0 < 3; idx0++) {
      number_t acc = sqtheta;
      number_t x10 = (xs->arr[idx0]);
      number_t cur = (x10) * (x10);
      acc = (acc) + (cur);
      sqtheta = acc;
    }
    
    number_t theta = sqrt(sqtheta);
    number_t costheta = cos(theta);
    number_t sintheta = sin(theta);
    number_t theta_inv = (1) / (theta);
    number_t x5957 = (xs->arr[1]);
    number_t x5967 = (xs->arr[2]);
    number_t x5971 = (xs->arr[2]);
    number_t x5975 = (xs->arr[0]);
    number_t x5979 = (xs->arr[0]);
    number_t x5983 = (xs->arr[1]);
    array_number_t w_cross_X = (array_number_t)storage_alloc(sizeof(int) * 2);w_cross_X->length=3;w_cross_X->arr = (number_t*)storage_alloc(sizeof(number_t) * 3);
    w_cross_X->arr[0] = (((x5957) * (theta_inv)) * ((xs->arr[(2) + (offset)]))) - (((x5967) * (theta_inv)) * ((xs->arr[(1) + (offset)])));
    w_cross_X->arr[1] = (((x5971) * (theta_inv)) * ((xs->arr[offset]))) - (((x5975) * (theta_inv)) * ((xs->arr[(2) + (offset)])));
    w_cross_X->arr[2] = (((x5979) * (theta_inv)) * ((xs->arr[(1) + (offset)]))) - (((x5983) * (theta_inv)) * ((xs->arr[offset])));
    number_t x5984 = 0;
    for (int idx0 = 0; idx0 < 3; idx0++) {
      number_t acc = x5984;
      number_t xi = (xs->arr[idx0]);
      number_t x00 = (xi) * (theta_inv);
      number_t y0 = (xs->arr[(idx0) + (offset)]);
      number_t cur = (x00) * (y0);
      acc = (acc) + (cur);
      x5984 = acc;
    }
    
    number_t tmp = (x5984) * ((1) - (costheta));
    array_number_t m = (array_number_t)storage_alloc(sizeof(int) * 2);m->length=3;m->arr = (number_t*)storage_alloc(sizeof(number_t) * 3);
    for(int i = 0; i < m->length; i++){
      number_t xi = (xs->arr[(i) + (offset)]);
      number_t x00 = (xi) * (costheta);
      number_t xi0 = (w_cross_X->arr[i]);
      number_t y0 = (xi0) * (sintheta);
      number_t x000 = (x00) + (y0);
      number_t xi00 = (xs->arr[i]);
      number_t xi000 = (xi00) * (theta_inv);
      number_t y00 = (xi000) * (tmp);
      m->arr[i] = (x000) + (y00);
      
    }
    x5985->arr[idx] = m;
    
  }
  return x5985;
}
