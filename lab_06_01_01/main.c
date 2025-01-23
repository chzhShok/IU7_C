#include <stdio.h>
#include <string.h>

#include "text_file_funcs.h"

static int rc = OK;

int main(int argc, char **argv)
{
    if (argc < MIN_ARGS || argc > MAX_ARGS)
    {
        rc = INCORRECT_ARGUMENTS_COUNT;
        goto exit;
    }

    FILE *f = fopen(argv[1], "r");
    if (f == NULL)
    {
        rc = IO_ERROR;
        goto exit;
    }

    rc = is_file_empty(f);
    if (rc)
        goto close;

    movie_t movies[MOVIES_LEN];

    if (strncmp(argv[2], "title", FIELD_LEN + 1) == 0 || strncmp(argv[2], "name", FIELD_LEN + 1) == 0 || strncmp(argv[2], "year", FIELD_LEN + 1) == 0)
    {
        char field[FIELD_LEN + 1];
        strncpy(field, argv[2], FIELD_LEN);

        int array_len;
        rc = read_and_sort(f, movies, field, &array_len);
        if (rc)
            goto close;

        if (argc == 4)
        {
            char key[MOVIE_TITLE + 1];
            strncpy(key, argv[3], MOVIE_TITLE);
            if (strlen(key) == 0)
            {
                rc = KEY_ERROR;
                goto close;
            }

            int ind;
            rc = bin_search_by_key(movies, array_len, key, field, &ind);
            if (rc == NOT_FOUND)
            {
                printf("Not found\n");
                rc = OK;
            }
            else if (rc)
                goto close;
            else
                print_movie(movies[ind]);
        }
        else
        {
            print_movies_array(movies, array_len);
        }
    }
    else
    {
        rc = INCORRECT_ARGUMENTS;
        goto close;
    }

    close:
        fclose(f);

    exit:
        return rc;
}
