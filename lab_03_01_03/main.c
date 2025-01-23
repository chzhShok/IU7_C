#include "matrix.h"
#include <stdio.h>
#include <stdlib.h>

void print_array(array_t array, int n)
{
    for (int i = 0; i < n; i++)
        printf("%d ", array[i]);
    printf("\n");
}

int main(void)
{
    matrix_t matrix;
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

    printf("Enter the elements of the matrix: ");
    int rc = scan_matrix(matrix, n, m);
    if (rc == ERR_IO)
    {
        printf("I/O error\n");
        return ERR_IO;
    }

    array_t array;

    fill_array_by_monotonous(matrix, array, n, m);

    printf("Result array: ");
    print_array(array, n);

    return OK;
}
