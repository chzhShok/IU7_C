#ifndef MATRIX_H_
#define MATRIX_H_

#define N_MAX 10
#define M_MAX 10
#define N_MIN 1
#define M_MIN 1
#define OK 0
#define ERR_IO 1
#define ERR_INPUT 2
#define ERR_DELETE 3

#include <stdlib.h>

typedef int matrix_t[N_MAX][M_MAX];

int scan_matrix(matrix_t matrix, size_t n, size_t m);
void print_matrix(matrix_t matrix, size_t n, size_t m);
int delete_columns_contain_digit(matrix_t matrix, matrix_t new_matrix, size_t n, size_t m, int digit);

#endif// MATRIX_H_
