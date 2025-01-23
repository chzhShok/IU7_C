#include "matrix.h"
#include <stdio.h>

int main(void)
{
    size_t n, m;

    printf("Enter the number of rows and the number of columns of the matrix: ");
    if (scanf("%zu", &n) != 1)
    {
        printf("I/O error\n");
        return ERR_IO;
    }

    if (n > N_MAX || n < N_MIN)
    {
        printf("Input error\n");
        return ERR_INPUT;
    }

    if (scanf("%zu", &m) != 1)
    {
        printf("I/O error\n");
        return ERR_IO;
    }

    if (m > M_MAX || m < M_MIN)
    {
        printf("Input error\n");
        return ERR_INPUT;
    }

    if (n != m)
    {
        printf("Error: n must be equal to m\n");
        return ERR_INPUT;
    }

    matrix_t matrix;
    fill_spiral(matrix, (int)n);

    printf("Matrix:\n");
    print_matrix(matrix, n, n);

    return OK;
}
