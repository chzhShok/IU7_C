#include <stdlib.h>
#include <string.h>

#include "text_file_funcs.h"

void print_movies_array(movie_t movies[], size_t len)
{
    for (size_t i = 0; i < len; i++)
        print_movie(movies[i]);
}

void print_movie(movie_t movie)
{
    printf("%s\n%s\n%d\n", movie.title, movie.name, movie.year);
}

static int bin_search_title(movie_t movies[], size_t len, char *key)
{
    int l = 0;
    int r = (int)len - 1;

    while (l <= r)
    {
        int mid = (l + r) / 2;
        if (strcmp(movies[mid].title, key) == 0)
            return mid;

        if (strcmp(movies[mid].title, key) < 0)
            l = mid + 1;
        else
            r = mid - 1;
    }

    return -1;
}

static int bin_search_name(movie_t movies[], size_t len, char *key)
{
    int l = 0;
    int r = (int)len - 1;

    while (l <= r)
    {
        int mid = (l + r) / 2;
        if (strcmp(movies[mid].name, key) == 0)
            return mid;

        if (strcmp(movies[mid].name, key) < 0)
            l = mid + 1;
        else
            r = mid - 1;
    }

    return -1;
}

static int bin_search_year(movie_t movies[], size_t len, int key)
{
    int l = 0;
    int r = (int)len - 1;

    while (l <= r)
    {
        int mid = (l + r) / 2;
        if (movies[mid].year == key)
            return mid;

        if (movies[mid].year < key)
            l = mid + 1;
        else
            r = mid - 1;
    }

    return -1;
}

int bin_search_by_key(movie_t movies[], size_t len, char *key, char *field, int *ind)
{
    if (strncmp(field, "title", FIELD_LEN) == 0)
    {
        *ind = bin_search_title(movies, len, key);
    }
    else if (strncmp(field, "name", FIELD_LEN) == 0)
    {
        *ind = bin_search_name(movies, len, key);
    }
    else
    {
        char *endptr;
        int key_int = (int)strtol(key, &endptr, 10);
        if (*key == '\0' || *endptr != '\0')
            return IO_ERROR;

        *ind = bin_search_year(movies, len, key_int);
    }

    if (*ind == -1)
        return NOT_FOUND;

    return OK;
}
