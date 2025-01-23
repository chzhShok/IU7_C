#ifndef LAB_07_1_4_ARRAY_H
#define LAB_07_1_4_ARRAY_H

#include <stdio.h>

#define MIN_ARGS 3
#define MAX_ARGS 4

enum error
{
    OK,
    INCORRECT_ARGUMENTS_COUNT,
    INCORRECT_ARGUMENTS,
    IO_ERROR,
    EMPTY_FILE,
    MEMORY_ERROR,
    EMPTY_FILTERED_ARRAY,
    INCORRECT_PARAMETERS,
};

int count_file_elements(FILE *f, int return_position);
int fill_array(FILE *f, const int *start_ptr, const int *end_ptr);
void print_nums(FILE *f, int *pb, const int *pe);

int key(const int *pb_src, const int *pe_src, int **pb_dst, int **pe_dst);
void mysort(void *first, size_t number, size_t size, int (*comparator)(const void *, const void *));

#endif//LAB_07_1_4_ARRAY_H
