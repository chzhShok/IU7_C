#ifndef TEXT_FILE_FUNCS_H
#define TEXT_FILE_FUNCS_H

#include <stdio.h>

#include "array_funcs.h"

#define MIN_ARGS 3
#define MAX_ARGS 4

#define FIELD_LEN 5
#define KEY_LEN 25

#define NUM_FIELDS 3

int is_file_empty(FILE *file);

int count_lines(FILE *file);
int read_and_sort(FILE *file, movie_t *movies, const char *field, int len);

void insert_sort_title(movie_t *movies, size_t len, const movie_t *new_movie);
void insert_sort_name(movie_t *movies, size_t len, const movie_t *new_movie);
void insert_sort_year(movie_t *movies, size_t len, const movie_t *new_movie);
void insert_sort_by_field(movie_t *movies, size_t len, const movie_t *new_movie, const char *field);

#endif // TEXT_FILE_FUNCS_H
