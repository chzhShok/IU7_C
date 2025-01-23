#include "binfile_utils.h"
#include <stdio.h>
#include <string.h>
#include <limits.h>

#define NOT_ENOUGH_ARGUMENTS 100
#define INCORRECT_ARGUMENTS 200
#define INCORRECT_NUM_INPUT 300

int main(int argc, char **argv)
{
    if (argc == 1)
        return NOT_ENOUGH_ARGUMENTS;
    else if ((argc == 4) && (strcmp(argv[1], "c") == 0))
    {
        FILE *f = fopen(argv[3], "wb");
        if (f == NULL)
            return IO_ERROR;

        long num = strtol(argv[2], NULL, 10);
        if ((num == LONG_MIN) || (num == LONG_MAX) || (num == 0))
            return INCORRECT_NUM_INPUT;

        if (fill_file_randomly(f, num) != 0)
            return IO_ERROR;

        fclose(f);
    }
    else if ((argc == 3) && (strcmp(argv[1], "p") == 0))
    {
        FILE *f = fopen(argv[2], "rb");
        if (f == NULL)
            return IO_ERROR;

        int rc = print_file(f);
        if (rc == IO_ERROR)
            return IO_ERROR;
        else if (rc == EMPTY_FILE)
            return EMPTY_FILE;

        fclose(f);
    }
    else if ((argc == 3) && (strcmp(argv[1], "s") == 0))
    {
        FILE *f = fopen(argv[2], "rb+");
        if (f == NULL)
            return IO_ERROR;

        int rc = sort_file(f);
        if (rc == IO_ERROR)
            return IO_ERROR;
        else if (rc == EMPTY_FILE)
            return EMPTY_FILE;

        fclose(f);
    }
    else if ((argc == 4) && (strcmp(argv[1], "import") == 0))
    {
        FILE *f_txt = fopen(argv[2], "r");
        if (f_txt == NULL)
            return IO_ERROR;

        FILE *f_bin = fopen(argv[3], "w");
        if (f_bin == NULL)
            return IO_ERROR;

        if (import(f_txt, f_bin) == IO_ERROR)
            return IO_ERROR;

        fclose(f_txt);
        fclose(f_bin);
    }
    else if ((argc == 4) && (strcmp(argv[1], "export") == 0))
    {
        FILE *f_bin = fopen(argv[2], "r");
        if (f_bin == NULL)
            return IO_ERROR;

        FILE *f_txt = fopen(argv[3], "w");
        if (f_txt == NULL)
            return IO_ERROR;

        if (export(f_bin, f_txt) == IO_ERROR)
            return IO_ERROR;

        fclose(f_txt);
        fclose(f_bin);
    }
    else
        return INCORRECT_ARGUMENTS;

    return 0;
}
