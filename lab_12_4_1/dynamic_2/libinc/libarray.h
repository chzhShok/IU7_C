#ifndef LIBARRAY_H
#define LIBARRAY_H

#include <stdio.h>

void print_nums(FILE *f, int *pb, const int *pe);
int count_file_elements(FILE *f, int return_position);
int fill_array(FILE *f, const int *start_ptr, const int *end_ptr);

int key(const int *pb_src, const int *pe_src, int **pb_dst, int **pe_dst);
void mysort(void *first, size_t number, size_t size, int (*comparator)(const void *, const void *));

int int_comparator(const void *a, const void *b);
int double_comparator(const void *a, const void *b);

#endif//LIBARRAY_H
