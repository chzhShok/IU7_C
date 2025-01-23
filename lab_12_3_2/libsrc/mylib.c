#include "mylib.h"

static int is_prime(int num)
{
    if (num == 0 || num == 1)
        return 0;

    for (int i = 2; i < num; i++)
        if (num % i == 0)
            return 0;

    return 1;
}

static int next_prime(int prime)
{
    int not_found = 1;

    while (not_found)
    {
        prime++;
        if (is_prime(prime))
            not_found = 0;
    }

    return prime;
}

int fill_prime_numbers(int *arr, int n)
{
    if (n <= 0)
        return FAIL;

    int prime = 2;

    for (int i = 0; i < n; i++)
    {
        arr[i] = prime;
        prime = next_prime(prime);
    }

    return SUCCESS;
}

int insert_after_even(const int *src, int src_len, int *dst, int k)
{
    if (src_len <= 0)
        return FAIL;

    int dst_ind = 0;

    for (int i = 0; i < src_len; i++, dst_ind++)
    {
        if (dst)
            dst[dst_ind] = src[i];

        if (src[i] % 2 == 0)
        {
            dst_ind++;
            if (dst)
                dst[dst_ind] = k;
        }
    }

    return dst_ind;
}
