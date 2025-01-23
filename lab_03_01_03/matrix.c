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

int is_row_monotonous(matrix_t matrix, size_t m, size_t k)
{
    int increasing = 1;
    int decreasing = 1;

    for (size_t i = 1; i < m; ++i)
    {
        if (matrix[k][i] > matrix[k][i - 1])
            decreasing = 0;

        if (matrix[k][i] < matrix[k][i - 1])
            increasing = 0;
    }

    if ((increasing + decreasing) == 0)
        return 0;

    return 1;
}

void fill_array_by_monotonous(matrix_t matrix, array_t result_array, size_t n, size_t m)
{
    size_t array_ind = 0;

    if (n == 1 && m == 1)
        result_array[0] = 0;
    else
        for (size_t i = 0; i < n; i++)
        {
            result_array[array_ind] = is_row_monotonous(matrix, m, i);
            array_ind++;
        }
}
