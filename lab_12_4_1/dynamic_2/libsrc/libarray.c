#include <stdio.h>
#include <stdlib.h>

#include "libarray.h"
#include "errors.h"

int int_comparator(const void *a, const void *b)
{
    int arg1 = *(const int *) a;
    int arg2 = *(const int *) b;

    return arg1 - arg2;
}

int double_comparator(const void *a, const void *b)
{
    double arg1 = *(const double *) a;
    double arg2 = *(const double *) b;

    if (arg1 < arg2) return -1;
    if (arg1 > arg2) return 1;
    return 0;
}

int count_file_elements(FILE *f, int return_position)
{
    int count = 0;
    int num;

    while (fscanf(f, "%d", &num) == 1)
        count++;

    fseek(f, 0, return_position);
    return count;
}

int fill_array(FILE *f, const int *start_ptr, const int *end_ptr)
{
    int num;

    int *p = (int *) start_ptr;
    while (fscanf(f, "%d", &num) == 1 && p < end_ptr)
    {
        *p = num;
        p++;
    }

    if (p != end_ptr)
        return IO_ERROR;

    return OK;
}

void print_nums(FILE *f, int *pb, const int *pe)
{
    int *p = pb;
    fprintf(f, "%d", *p);
    ++p;

    for (; p < pe; ++p)
        fprintf(f, " %d", *p);
}

static double calc_avg(const int *pb, const int *pe)
{
    int len = 0, sum = 0;
    for (const int *p = pb; p < pe; p++)
    {
        len++;
        sum += *p;
    }

    return len > 0 ? (double) sum / len : 0.0;
}

// В массиве остаются элементы, которые больше среднего арифметического всех элементов массива
int key(const int *pb_src, const int *pe_src, int **pb_dst, int **pe_dst)
{
    if (!pb_src || !pe_src || !pb_dst || !pe_dst || pb_src >= pe_src)
        return INCORRECT_PARAMETERS;

    double avg = calc_avg(pb_src, pe_src);

    int len = 0;
    for (const int *p = pb_src; p < pe_src; p++)
        if ((double) *p > avg)
            len++;

    if (len == 0)
        return EMPTY_FILTERED_ARRAY;

    int *p_dst = *pb_dst;
    for (const int *p = pb_src; p < pe_src; p++)
        if ((double) *p > avg)
        {
            *p_dst = *p;
            p_dst++;
        }

    *pe_dst = p_dst;

    return OK;
}

static void swap(void *a, void *b, size_t size)
{
    unsigned char tmp;
    unsigned char *pa = (unsigned char *) a;
    unsigned char *pb = (unsigned char *) b;

    while (size--)
    {
        tmp = *pa;
        *pa++ = *pb;
        *pb++ = tmp;
    }
}

void mysort(void *first, size_t number, size_t size, int (*comparator)(const void *, const void *))
{
    if (!first || number < 2 || size == 0 || !comparator)
        return;

    int left = 0;
    int right = (int) number - 1;
    unsigned char *p = (unsigned char *) first;

    while (left < right)
    {
        int last_swap = 0;
        for (int i = left; i < right; i++)
            if (comparator(p + i * size, p + (i + 1) * size) > 0)
            {
                swap(p + i * size, p + (i + 1) * size, size);
                last_swap = i;
            }

        right = last_swap;

        for (int i = right; i > left; i--)
            if (comparator(p + (i - 1) * size, p + i * size) > 0)
            {
                swap(p + (i - 1) * size, p + i * size, size);
                last_swap = i;
            }

        left = last_swap;
    }
}
