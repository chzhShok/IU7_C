#include "matrix.h"
#include <stdio.h>

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

    int digit;
    printf("Enter digit: ");
    if (scanf("%d", &digit) != 1)
    {
        printf("I/O error\n");
        return ERR_IO;
    }
    if ((digit < 0) || (digit > 9))
    {
        printf("Input error\n");
        return ERR_INPUT;
    }

    matrix_t new_matrix;
    int new_m = delete_columns_contain_digit(matrix, new_matrix, n, m, digit);

    if (new_m == 0)
    {
        printf("Error: new matrix doesn't contain digits\n");
        return ERR_DELETE;
    }

    printf("Result matrix:\n");
    print_matrix(new_matrix, n, new_m);

    return OK;
}
