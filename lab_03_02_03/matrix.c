#include "matrix.h"
#include <stdio.h>
#include <stdlib.h>

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

int int_contain_digit(int element, int digit)
{
    if ((digit == 0) && (element % 10 == 0))
        return 1;

    while (element > 0)
    {
        if (element % 10 == digit)
            return 1;
        element /= 10;
    }

    return 0;
}

int delete_columns_contain_digit(matrix_t matrix, matrix_t new_matrix, size_t n, size_t m, int digit)
{
    int matrix_element;
    int not_delete = 1;
    int ind_new = 0;

    for (size_t i = 0; i < m; i++)
    {
        for (size_t j = 0; j < n; j++)
        {
            matrix_element = abs(matrix[j][i]);

            int res = int_contain_digit(matrix_element, digit);
            if (res == 1)
                not_delete = 0;
        }

        if (not_delete)
        {
            for (size_t k = 0; k < n; k++)
                new_matrix[k][ind_new] = matrix[k][i];
            ind_new++;
        }

        not_delete = 1;
    }

    return ind_new;
}
