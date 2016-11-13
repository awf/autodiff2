#ifndef __LINALG_H__ 
#define __LINALG_H__ 
#include "runtime/fsharp.h"
#include <stdio.h>
#include <math.h>

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

array_number_t TOP_LEVEL_linalg_vectorAdd3(array_number_t x, array_number_t y, array_number_t z) {
	card_t macroDef102 = x->length;
	array_number_t macroDef103 = (array_number_t)storage_alloc(sizeof(int) * 2);
	macroDef103->length=macroDef102;
	macroDef103->arr = (number_t*)storage_alloc(sizeof(number_t) * macroDef102);
		for(int i = 0; i < macroDef103->length; i++){
			number_t x0 = x->arr[i];
			number_t y0 = y->arr[i];
			number_t x1 = (x0) + (y0);
			number_t y1 = z->arr[i];
			macroDef103->arr[i] = (x1) + (y1);;
		}
	return macroDef103;
}

#endif