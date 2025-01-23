#include "matrix.h"
#include <stdio.h>

int scan_matrix(matrix_t matrix, size_t n, size_t m)
{
    for (size_t i = 0; i < n; i++)
        for (size_t j = 0; j < m; j++)
            if (scanf("%d", &matrix[i][j]) != 1)
                return ERR_IO;
    return OK;
}

void print_matrix(matrix_t matrix, size_t n, size_t m)
{
    for (size_t i = 0; i < n; i++)
    {
        for (size_t j = 0; j < m; j++)
            printf("%d ", matrix[i][j]);
        printf("\n");
    }
}

void swap_columns(matrix_t matrix, size_t n)
{
    int temp;
    for (size_t i = 0; i < n / 2; i++)
        for (size_t j = i; j < n - i; j++)
        {
            temp = matrix[j][i];
            matrix[j][i] = matrix[j][n - i - 1];
            matrix[j][n - i - 1] = temp;
        }
}
