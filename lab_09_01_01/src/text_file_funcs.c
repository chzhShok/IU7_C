#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "array_funcs.h"
#include "common_funcs.h"
#include "errors.h"
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

void insert_sort_title(movie_t *movies, size_t len, const movie_t *new_movie)
{
    size_t i = len;

    while (i > 0 && strcmp(movies[i - 1].title, new_movie->title) > 0)
    {
        movies[i] = movies[i - 1];
        i--;
    }

    movies[i].title = malloc((strlen(new_movie->title) + 1) * sizeof(char));
    if (!movies[i].title)
    {
        free(movies[i].title);
        free(movies[i].name);
        return;
    }

    movies[i].name = malloc((strlen(new_movie->name) + 1) * sizeof(char));
    if (!movies[i].name)
    {
        free(movies[i].title);
        free(movies[i].name);
        return;
    }

    strncpy(movies[i].title, new_movie->title, strlen(new_movie->title) + 1);
    strncpy(movies[i].name, new_movie->name, strlen(new_movie->name) + 1);
    movies[i].year = new_movie->year;
}

void insert_sort_name(movie_t *movies, size_t len, const movie_t *new_movie)
{
    size_t i = len;

    while (i > 0 && strcmp(movies[i - 1].name, new_movie->name) > 0)
    {
        movies[i] = movies[i - 1];
        i--;
    }

    movies[i].title = malloc((strlen(new_movie->title) + 1) * sizeof(char));
    if (!movies[i].title)
    {
        free(movies[i].title);
        free(movies[i].name);
        return;
    }

    movies[i].name = malloc((strlen(new_movie->name) + 1) * sizeof(char));
    if (!movies[i].name)
    {
        free(movies[i].title);
        free(movies[i].name);
        return;
    }

    strncpy(movies[i].title, new_movie->title, strlen(new_movie->title) + 1);
    strncpy(movies[i].name, new_movie->name, strlen(new_movie->name) + 1);
    movies[i].year = new_movie->year;
}

void insert_sort_year(movie_t *movies, size_t len, const movie_t *new_movie)
{
    size_t i = len;

    while (i > 0 && movies[i - 1].year > new_movie->year)
    {
        movies[i] = movies[i - 1];
        i--;
    }

    movies[i].title = malloc((strlen(new_movie->title) + 1) * sizeof(char));
    if (!movies[i].title)
    {
        free(movies[i].title);
        free(movies[i].name);
        return;
    }

    movies[i].name = malloc((strlen(new_movie->name) + 1) * sizeof(char));
    if (!movies[i].name)
    {
        free(movies[i].title);
        free(movies[i].name);
        return;
    }

    strncpy(movies[i].title, new_movie->title, strlen(new_movie->title) + 1);
    strncpy(movies[i].name, new_movie->name, strlen(new_movie->name) + 1);
    movies[i].year = new_movie->year;
}

void insert_sort_by_field(movie_t *movies, size_t len, const movie_t *new_movie, const char *field)
{
    if (strncmp(field, "title", FIELD_LEN) == 0)
        insert_sort_title(movies, len, new_movie);
    else if (strncmp(field, "name", FIELD_LEN) == 0)
        insert_sort_name(movies, len, new_movie);
    else
        insert_sort_year(movies, len, new_movie);
}

int count_lines(FILE *file)
{
    int ind = 0;
    char *line = NULL;
    size_t len = 0;

    int cur_pos = ftell(file);

    while (getline(&line, &len, file) > 0)
    {
        ind++;
        free(line);
        line = NULL;
    }

    if (line)
        free(line);

    fseek(file, cur_pos, SEEK_SET);

    return ind;
}

static int year_preprocess(int *year, char *year_str, FILE *file)
{
    size_t pos = strcspn(year_str, "\n");
    if (pos < strlen(year_str))
        year_str[pos] = '\0';
    else if (pos == strlen(year_str) && !feof(file))
        return BUFFER_ERROR;

    if (strlen(year_str) != 4)
        return IO_ERROR;

    int rc = str_to_int(year_str, year);
    if (rc)
        return IO_ERROR;

    return OK;
}

static int title_preprocess(char *title)
{
    size_t pos = strcspn(title, "\n");
    if (pos == strlen(title))
        return IO_ERROR;
    title[pos] = '\0';

    if (strlen(title) == 0)
        return IO_ERROR;

    return OK;
}

static int name_preprocess(char *name)
{
    size_t pos = strcspn(name, "\n");
    if (pos == strlen(name))
        return IO_ERROR;
    name[pos] = '\0';

    if (strlen(name) == 0)
        return IO_ERROR;

    return OK;
}

int read_and_sort(FILE *file, movie_t *movies, const char *field, int len)
{
    char *title = NULL, *name = NULL, *year_str = NULL;
    size_t title_len = 0, name_len = 0, year_len = 0;

    for (int ind = 0; ind < len; ind++)
    {
        if (getline(&title, &title_len, file) == -1)
        {
            free(title);
            free(name);
            free(year_str);
            return IO_ERROR;
        }

        if (getline(&name, &name_len, file) == -1)
        {
            free(title);
            free(name);
            free(year_str);
            return IO_ERROR;
        }

        if (getline(&year_str, &year_len, file) == -1)
        {
            free(title);
            free(name);
            free(year_str);
            return IO_ERROR;
        }

        int rc;

        int year;
        rc = year_preprocess(&year, year_str, file);
        if (rc)
        {
            free(title);
            free(name);
            free(year_str);
            return rc;
        }

        rc = title_preprocess(title);
        if (rc)
        {
            free(title);
            free(name);
            free(year_str);
            return rc;
        }

        rc = name_preprocess(name);
        if (rc)
        {
            free(title);
            free(name);
            free(year_str);
            return rc;
        }

        movie_t new_movie;
        new_movie.title = malloc((strlen(title) + 1) * sizeof(char));
        if (!new_movie.title)
        {
            free_movie(new_movie);
            free(title);
            free(name);
            free(year_str);
            return MEMORY_ERROR;
        }

        new_movie.name = malloc((strlen(name) + 1) * sizeof(char));
        if (!new_movie.name)
        {
            free_movie(new_movie);
            free(title);
            free(name);
            free(year_str);
            return MEMORY_ERROR;
        }

        strncpy(new_movie.title, title, strlen(title) + 1);
        strncpy(new_movie.name, name, strlen(name) + 1);
        new_movie.year = year;

        insert_sort_by_field(movies, ind, &new_movie, field);

        free(new_movie.title);
        free(new_movie.name);
    }

    free(title);
    free(name);
    free(year_str);

    return OK;
}
