#include "matrix.h"
#include <math.h>
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

int is_prime(int number)
{
    if (number <= 1)
        return 0;

    if (number % 2 == 0 && number != 2)
        return 0;

    for (int i = 3; i < ((int) sqrt(number) + 1); i += 2)
        if (number % i == 0)
            return 0;

    return 1;
}

int find_primes(matrix_t matrix, int primes[], size_t n, size_t m)
{
    int array_ind = 0;
    int count_prime_numbers = 0;

    for (size_t i = 0; i < n; i++)
        for (size_t j = 0; j < m; j++)
            if (is_prime(matrix[i][j]))
            {
                primes[array_ind] = matrix[i][j];
                array_ind++;
                count_prime_numbers++;
            }

    return count_prime_numbers;
}

void replace_prime_elements(matrix_t matrix, int source[], size_t n, size_t m)
{
    int array_ind = 0;

    for (size_t i = 0; i < n; i++)
        for (size_t j = 0; j < m; j++)
            if (is_prime(matrix[i][j]))
            {
                matrix[i][j] = source[array_ind];
                array_ind++;
            }
}
