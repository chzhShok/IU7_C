#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "array.h"

int int_comparator(const void *a, const void *b)
{
    int arg1 = *(const int *) a;
    int arg2 = *(const int *) b;

    return arg1 - arg2;
}

int main(int argc, char *argv[])
{
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
