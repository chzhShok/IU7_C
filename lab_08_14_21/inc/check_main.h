#ifndef CHECK_MAIN_H
#define CHECK_MAIN_H

#define N1 1
#define N2 2
#define N3 3
#define N4 4

int cmp_matrix(double **matrix1, double **matrix2, size_t n, size_t m);

Suite *add_suite(void);
Suite *multiplication_suite(void);

#endif//CHECK_MAIN_H
