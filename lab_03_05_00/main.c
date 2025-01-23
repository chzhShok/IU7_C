#include "matrix.h"
#include <stdio.h>

void reverse_array(int array[], size_t n)
{
    int temp;
    for (size_t i = 0; i < n / 2; i++)
    {
        temp = array[i];
        array[i] = array[n - 1 - i];
        array[n - 1 - i] = temp;
    }
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

    int prime_numbers[N_MAX * M_MAX];
    int len_array = find_primes(matrix, prime_numbers, n, m);
    if (len_array == 0)
    {
        printf("Error: no prime numbers in the matrix\n");
        return ERR_PRIME;
    }

    reverse_array(prime_numbers, len_array);

    replace_prime_elements(matrix, prime_numbers, n, m);

    printf("Matrix:\n");
    print_matrix(matrix, n, m);

    return OK;
}
