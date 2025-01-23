#ifndef MATRIX_H_
#define MATRIX_H_

#define N_MAX 10
#define M_MAX 10
#define N_MIN 1
#define M_MIN 1
#define OK        0
#define ERR_IO    1
#define ERR_INPUT 2

#include <stdlib.h>

typedef int matrix_t[N_MAX][M_MAX];
typedef int array_t[N_MAX];

int scan_matrix(matrix_t matrix, size_t n, size_t m);
void fill_array_by_monotonous(matrix_t matrix, array_t array, size_t n, size_t m);

#endif // MATRIX_H_
