#include <dlfcn.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include "errors.h"

#define MIN_ARGS 3
#define MAX_ARGS 4

typedef int (*int_comparator_t)(const void *a, const void *b);
typedef int (*count_file_elements_t)(FILE *f, int return_position);
typedef int (*fill_array_t)(FILE *f, const int *start_ptr, const int *end_ptr);
typedef int (*my_key_t)(const int *pb_src, const int *pe_src, int **pb_dst, int **pe_dst);
typedef void (*mysort_t)(void *first, size_t number, size_t size, int (*comparator)(const void *, const void *));
typedef void (*print_nums_t)(FILE *f, int *pb, const int *pe);

int main(int argc, char *argv[])
{
    int_comparator_t int_comparator = NULL;
    count_file_elements_t count_file_elements = NULL;
    fill_array_t fill_array = NULL;
    my_key_t key = NULL;
    mysort_t mysort = NULL;
    print_nums_t print_nums = NULL;

    void *lib = dlopen("./out/libarr.so", RTLD_LAZY);
    if (!lib)
    {
        fprintf(stderr, "dlopen error: %s\n", dlerror());
        return LIB_ERROR;
    }

    int_comparator = (int_comparator_t) (uintptr_t) dlsym(lib, "int_comparator");
    count_file_elements = (count_file_elements_t) (uintptr_t) dlsym(lib, "count_file_elements");
    fill_array = (fill_array_t) (uintptr_t) dlsym(lib, "fill_array");
    key = (my_key_t) (uintptr_t) dlsym(lib, "key");
    mysort = (mysort_t) (uintptr_t) dlsym(lib, "mysort");
    print_nums = (print_nums_t) (uintptr_t) dlsym(lib, "print_nums");

    int rc = OK;
    int filter = 0;

    if (argc < MIN_ARGS || argc > MAX_ARGS)
        return INCORRECT_ARGUMENTS_COUNT;

    if (argc == 4)
    {
        if (strncmp(argv[3], "f", 2) != 0)
            return INCORRECT_ARGUMENTS;
        filter = 1;
    }

    FILE *f = fopen(argv[1], "r");
    if (f == NULL)
        return IO_ERROR;

    int elements_count = count_file_elements(f, SEEK_SET);
    if (elements_count == 0)
    {
        fclose(f);
        return EMPTY_FILE;
    }

    int *pb = malloc(elements_count * sizeof(int));
    if (pb == NULL)
    {
        fclose(f);
        return MEMORY_ERROR;
    }

    int *pe = pb + elements_count;
    rc = fill_array(f, pb, pe);
    if (rc)
    {
        fclose(f);
        free(pb);
        return rc;
    }
    fclose(f);

    if (filter)
    {
        int *pb_filtered = NULL, *pe_filtered = NULL;
        pb_filtered = malloc(elements_count * sizeof(int));
        if (!pb_filtered)
        {
            free(pb);
            return MEMORY_ERROR;
        }

        rc = key(pb, pe, &pb_filtered, &pe_filtered);
        if (rc)
        {
            free(pb_filtered);
            free(pb);
            return rc;
        }

        free(pb);
        pb = pb_filtered;
        pe = pe_filtered;

        elements_count = pe_filtered - pb_filtered;
    }

    mysort(pb, elements_count, sizeof(int), int_comparator);

    f = fopen(argv[2], "w");
    if (f == NULL)
    {
        free(pb);
        return IO_ERROR;
    }

    print_nums(f, pb, pe);

    fclose(f);
    free(pb);

    return rc;
}
