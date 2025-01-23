#include "matrix.h"
#include <stdio.h>

void print_matrix(matrix_t matrix, size_t n, size_t m)
{
    for (size_t i = 0; i < n; i++)
    {
        for (size_t j = 0; j < m; j++)
            printf("%d ", matrix[i][j]);
        printf("\n");
    }
}

void fill_spiral(matrix_t matrix, int n)
{
    int value = 1;
    int row_start = 0, row_end = n;
    int column_start = 0, column_end = n;

    while (value <= n * n)
    {
        for (int i = row_start; i < row_end; i++)
        {
            matrix[i][column_start] = value;
            value++;
        }
        column_start++;

        for (int i = column_start; i < column_end; i++)
        {
            matrix[row_end - 1][i] = value;
            value++;
        }
        row_end--;

        for (int i = row_end - 1; i >= row_start; i--)
        {
            matrix[i][column_end - 1] = value;
            value++;
        }
        column_end--;

        for (int i = column_end - 1; i >= column_start; i--)
        {
            matrix[row_start][i] = value;
            value++;
        }
        row_start++;
    }
}
