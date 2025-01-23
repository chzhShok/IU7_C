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

int compare_min_elements(matrix_t matrix, size_t m, size_t i1, size_t i2)
{
    int min1 = matrix[i1][0];
    int min2 = matrix[i2][0];

    for (size_t j = 1; j < m; j++)
    {
        if (matrix[i1][j] < min1)
            min1 = matrix[i1][j];

        if (matrix[i2][j] < min2)
            min2 = matrix[i2][j];
    }
    return min2 - min1;
}

void sort_rows_by_min_elements(matrix_t matrix, size_t n, size_t m)
{
    for (size_t i = 0; i < n; i++)
        for (size_t j = 0; j < n - i - 1; j++)
            if (compare_min_elements(matrix, m, j, j + 1) > 0)
                for (size_t k = 0; k < m; k++)
                {
                    int temp = matrix[j][k];
                    matrix[j][k] = matrix[j + 1][k];
                    matrix[j + 1][k] = temp;
                }
}
