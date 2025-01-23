#ifndef MATRIX_H
#define MATRIX_H

#include <stdio.h>

#define EPS 0.00001

typedef struct
{
    double **data;
    int n;
    int m;
    int not_zero;
} matrix_t;

int allocate_matrix(matrix_t *matrix);
int init_matrix(char *filepath, matrix_t *matrix);
void free_matrix(double **ptrs);
void write_matrix(FILE *f, matrix_t *matrix);
void print_matrix(double **matrix, size_t n, size_t m);

void matrix_addition(matrix_t *result_matrix, matrix_t *matrix1, matrix_t *matrix2);
void matrix_multiplication(matrix_t *result_matrix, matrix_t *matrix1, matrix_t *matrix2);
int inverse_matrix(matrix_t *inv_matrix, matrix_t *matrix);

#endif//MATRIX_H
