#include <stdlib.h>
#include <string.h>

#include "array_funcs.h"
#include "common_funcs.h"
#include "errors.h"
#include "text_file_funcs.h"

int allocate_movies(movie_t **movies, int movies_count)
{
    *movies = (movie_t *) malloc(sizeof(movie_t) * movies_count);
    if (!*movies)
        return MEMORY_ERROR;

    for (int i = 0; i < movies_count; i++)
    {
        (*movies)[i].title = NULL;
        (*movies)[i].name = NULL;
    }

    return OK;
}

void print_movies_array(movie_t *movies, size_t len)
{
    for (size_t i = 0; i < len; i++)
        print_movie(&movies[i]);
}

void print_movie(const movie_t *movie)
{
    if (!movie || !movie->title || !movie->name)
        return;

    printf("%s\n%s\n%d\n", movie->title, movie->name, movie->year);
}

int bin_search_title(movie_t *movies, size_t len, char *key)
{
    int l = 0;
    int r = (int) len - 1;

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

int bin_search_name(movie_t *movies, size_t len, char *key)
{
    int l = 0;
    int r = (int) len - 1;

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

int bin_search_year(movie_t *movies, size_t len, int key)
{
    int l = 0;
    int r = (int) len - 1;

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

int bin_search_by_key(movie_t *movies, size_t len, char *key, char *field, int *ind)
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
        int key_int;
        int rc = str_to_int(key, &key_int);
        if (rc)
            return rc;

        *ind = bin_search_year(movies, len, key_int);
    }

    if (*ind == -1)
        return NOT_FOUND;

    return OK;
}

void free_movie(movie_t movie)
{
    free(movie.title);
    free(movie.name);
}

void free_movies(movie_t *movies, size_t count)
{
    if (!movies)
        return;

    for (size_t i = 0; i < count; i++)
        free_movie(movies[i]);

    free(movies);
}
