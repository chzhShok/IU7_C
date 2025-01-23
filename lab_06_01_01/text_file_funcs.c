#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "text_file_funcs.h"

int is_file_empty(FILE *file)
{
    long size;

    if (fseek(file, 0, SEEK_END))
        return IO_ERROR;

    size = ftell(file);

    if (size < 0)
        return IO_ERROR;

    if (fseek(file, 0, SEEK_SET))
        return IO_ERROR;

    if (size / sizeof(int) == 0)
        return EMPTY_FILE;

    return OK;
}

static void insert_sort_title(movie_t movies[], size_t len, movie_t new_movie)
{
    size_t i = len;

    while (i > 0 && strcmp(movies[i - 1].title, new_movie.title) > 0)
    {
        movies[i] = movies[i - 1];
        i--;
    }

    movies[i] = new_movie;
}

static void insert_sort_name(movie_t movies[], size_t len, movie_t new_movie)
{
    size_t i = len;

    while (i > 0 && strcmp(movies[i - 1].name, new_movie.name) > 0)
    {
        movies[i] = movies[i - 1];
        i--;
    }

    movies[i] = new_movie;
}

static void insert_sort_year(movie_t movies[], size_t len, movie_t new_movie)
{
    size_t i = len;

    while (i > 0 && movies[i - 1].year > new_movie.year)
    {
        movies[i] = movies[i - 1];
        i--;
    }

    movies[i] = new_movie;
}

static void insert_sort_by_field(movie_t movies[], size_t len, movie_t new_movie, char field[])
{
    if (strncmp(field, "title", FIELD_LEN) == 0)
        insert_sort_title(movies, len, new_movie);
    else if (strncmp(field, "name", FIELD_LEN) == 0)
        insert_sort_name(movies, len, new_movie);
    else
        insert_sort_year(movies, len, new_movie);
}

int read_and_sort(FILE *file, movie_t movies[], char field[], int *ind)
{
    char title[MOVIE_TITLE + 1];
    char name[DIRECTOR_NAME + 1];
    char year_str[YEAR_LEN + 1];
    *ind = 0;

    while (fgets(title, MOVIE_TITLE + 1, file) && fgets(name, DIRECTOR_NAME + 1, file) && fgets(year_str, YEAR_LEN + 1, file))
    {
        if (*ind > (MOVIES_LEN - 1))
            return OUT_OF_RANGE;

        if (strchr(year_str, '\n') == NULL)
        {
            if (!feof(file))
                return IO_ERROR;
            year_str[YEAR_LEN - 1] = '\0';
        }
        else
        {
            size_t pos = strcspn(year_str, "\n");
            if (pos == strlen(year_str))
                return BUFFER_ERROR;
            year_str[pos] = '\0';
        }

        if (strlen(year_str) != 4)
            return IO_ERROR;

        char *endptr;
        int year = (int)strtol(year_str, &endptr, 10);
        if (*year_str == '\0' || *endptr != '\0')
            return IO_ERROR;

        size_t pos = strcspn(title, "\n");
        if (pos == strlen(title))
            return BUFFER_ERROR;
        title[pos] = '\0';

        pos = strcspn(name, "\n");
        if (pos == strlen(name))
            return BUFFER_ERROR;
        name[pos] = '\0';

        if (strlen(title) == 0 || strlen(name) == 0)
            return IO_ERROR;

        movie_t new_movie;
        strncpy(new_movie.title, title, MOVIE_TITLE + 1);
        strncpy(new_movie.name, name, DIRECTOR_NAME + 1);
        new_movie.year = year;

        insert_sort_by_field(movies, *ind, new_movie, field);

        (*ind)++;
    }

    return OK;
}
