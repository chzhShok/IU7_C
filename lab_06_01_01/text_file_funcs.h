#ifndef TEXT_FILE_FUNCS_H
#define TEXT_FILE_FUNCS_H

#include <stdio.h>

#define MIN_ARGS 3
#define MAX_ARGS 4

#define MOVIE_TITLE 25
#define DIRECTOR_NAME 25
#define YEAR_LEN 5

#define MOVIES_LEN 15
#define FIELD_LEN 5

enum errors
{
    OK,
    INCORRECT_ARGUMENTS_COUNT,
    IO_ERROR,
    INCORRECT_ARGUMENTS,
    BUFFER_ERROR,
    EMPTY_FILE,
    KEY_ERROR,
    OUT_OF_RANGE,
    NOT_FOUND,
};

typedef struct
{
    char title[MOVIE_TITLE + 1];
    char name[DIRECTOR_NAME + 1];
    int year;
} movie_t;

int is_file_empty(FILE *file);

void print_movies_array(movie_t movies[], size_t len);
void print_movie(movie_t movie);

int read_and_sort(FILE *file, movie_t movies[], char field[], int *ind);
int bin_search_by_key(movie_t movies[], size_t len, char *key, char *field, int *ind);

#endif // TEXT_FILE_FUNCS_H
