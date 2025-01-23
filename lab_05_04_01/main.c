#include "student_db_utils.h"

#include <stdio.h>
#include <string.h>

#define INCORRECT_ARGUMENTS 53
#define NOT_ENOUGH_ARGUMENTS 200
#define LARGE_SUBSTR 300

int main(int argc, char **argv)
{
    if (argc == 1)
        return NOT_ENOUGH_ARGUMENTS;
    // SORT: ./app.exe sb FILE
    else if ((argc == 3) && (strcmp(argv[1], "sb") == 0))
    {
        FILE *f = fopen(argv[2], "rb+");
        if (f == NULL)
            return IO_ERROR;

        int rc = sort_students(f);
        if (rc == IO_ERROR)
            return IO_ERROR;
        else if (rc == EMPTY_FILE)
            return EMPTY_FILE;

        print_file(f);

        fclose(f);
    }
    // PRINT: ./app.exe fb FILE_SRC FILE_DST SUBSTR
    else if ((argc == 5) && (strcmp(argv[1], "fb") == 0))
    {
        FILE *f_src = fopen(argv[2], "rb");
        if (f_src == NULL)
            return IO_ERROR;

        FILE *f_dst = fopen(argv[3], "wb");
        if (f_dst == NULL)
            return IO_ERROR;

        if (strlen(argv[4]) > LASTNAME_LENGTH)
            return LARGE_SUBSTR;

        int write = 0;
        int rc = print_bd_in_another_file(f_src, f_dst, argv[4], &write);
        if (write == 0)
            return EMPTY_FILE;

        if (rc == IO_ERROR)
            return IO_ERROR;
        else if (rc == EMPTY_FILE)
            return EMPTY_FILE;

        fclose(f_dst);
        fclose(f_src);
    }
    // DELETE: ./app.exe db FILE
    else if ((argc == 3) && (strcmp(argv[1], "db") == 0))
    {
        FILE *f = fopen(argv[2], "rb+");
        if (f == NULL)
            return IO_ERROR;

        int rc = delete_by_condition(f);
        if (rc == IO_ERROR)
            return IO_ERROR;
        else if (rc == EMPTY_FILE)
            return EMPTY_FILE;

        fclose(f);
    }
    // IMPORT: ./app.exe import FILE_TXT FILE_BIN
    else if ((argc == 4) && (strcmp(argv[1], "import") == 0))
    {
        FILE *f_txt = fopen(argv[2], "r");
        if (f_txt == NULL)
            return IO_ERROR;

        FILE *f_bin = fopen(argv[3], "wb");
        if (f_bin == NULL)
            return IO_ERROR;

        if (import(f_txt, f_bin) == IO_ERROR)
            return IO_ERROR;

        fclose(f_txt);
        fclose(f_bin);
    }
    // EXPORT: ./app.exe export FILE_BIN FILE_TXT
    else if ((argc == 4) && (strcmp(argv[1], "export") == 0))
    {
        FILE *f_bin = fopen(argv[2], "rb");
        if (f_bin == NULL)
            return IO_ERROR;

        FILE *f_txt = fopen(argv[3], "w");
        if (f_txt == NULL)
            return IO_ERROR;

        if (export(f_bin, f_txt) == IO_ERROR)
            return IO_ERROR;

        fclose(f_bin);
        fclose(f_txt);
    }
    else
        return INCORRECT_ARGUMENTS;

    return 0;
}
