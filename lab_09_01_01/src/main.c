#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "array_funcs.h"
#include "common_funcs.h"
#include "errors.h"
#include "text_file_funcs.h"

int main(int argc, char **argv)
{
    int rc;

    if (argc < MIN_ARGS || argc > MAX_ARGS)
        return INCORRECT_ARGUMENTS_COUNT;

    FILE *f = fopen(argv[1], "r");
    if (f == NULL)
        return IO_ERROR;

    rc = is_file_empty(f);
    if (rc)
    {
        fclose(f);
        return rc;
    }

    movie_t *movies = NULL;

    int cmd = get_command(argc, argv);
    if (!cmd)
    {
        fclose(f);
        return INCORRECT_ARGUMENTS;
    }

    char *field = NULL;
    rc = preprocess_arg(argv[2], &field, FIELD_LEN);
    if (rc)
    {
        fclose(f);
        return rc;
    }

    //    char *field = (char *) malloc(sizeof(char) * (FIELD_LEN + 1));
    //    if (!field)
    //    {
    //        fclose(f);
    //        return MEMORY_ERROR;
    //    }
    //
    //    strncpy(field, argv[2], FIELD_LEN);
    //    field[FIELD_LEN] = '\0';

    int lines_count = count_lines(f);
    int movies_count = lines_count / NUM_FIELDS;
    if (lines_count % NUM_FIELDS != 0)
    {
        fclose(f);
        free(field);
        return INCORRECT_NUM_OF_LINES;
    }

    rc = allocate_movies(&movies, movies_count);
    if (rc)
    {
        fclose(f);
        free(field);
        return rc;
    }

    rc = read_and_sort(f, movies, field, movies_count);
    if (rc)
    {
        fclose(f);
        free(field);
        free_movies(movies, movies_count);
        return rc;
    }
    fclose(f);

    char *key = NULL;
    if (cmd == 1)
    {
        rc = preprocess_arg(argv[3], &key, KEY_LEN);
        if (rc)
        {
            free(field);
            free_movies(movies, movies_count);
            return rc;
        }

        //        key = (char *) malloc(sizeof(char) * (KEY_LEN + 1));
        //        strncpy(key, argv[3], KEY_LEN);
        //        key[KEY_LEN] = '\0';

        if (strlen(key) == 0)
        {
            free(field);
            free(key);
            free_movies(movies, movies_count);
            return KEY_ERROR;
        }

        int ind;
        rc = bin_search_by_key(movies, movies_count, key, field, &ind);
        if (rc == NOT_FOUND)
        {
            printf("Not found\n");
            free_movies(movies, movies_count);
            free(field);
            free(key);
            return OK;
        }
        else if (rc)
        {
            free(field);
            free(key);
            free_movies(movies, movies_count);
            return rc;
        }
        else
        {
            print_movie(&movies[ind]);
        }
    }
    else
    {
        print_movies_array(movies, movies_count);
    }

    free_movies(movies, movies_count);
    free(field);
    free(key);

    return OK;
}
