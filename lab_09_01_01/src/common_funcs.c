#include <stdlib.h>
#include <string.h>

#include "common_funcs.h"
#include "text_file_funcs.h"
#include "errors.h"

int str_to_int(char *s, int *num)
{
    char *endptr;
    *num = (int) strtol(s, &endptr, 10);
    if (*s == '\0' || *endptr != '\0')
        return IO_ERROR;

    return OK;
}

int get_command(int argc, char **argv)
{
    int cmd;

    if (strncmp(argv[2], "title", FIELD_LEN + 1) == 0 || strncmp(argv[2], "name", FIELD_LEN + 1) == 0 || strncmp(argv[2], "year", FIELD_LEN + 1) == 0)
    {
        if (argc == 4)
            cmd = 1;
        else
            cmd = 2;
    }
    else
    {
        cmd = 0;
    }

    return cmd;
}

int preprocess_arg(char *src, char **dst, int len)
{
    *dst = (char *) malloc(sizeof(char) * (len + 1));
    if (!(*dst))
        return MEMORY_ERROR;

    strncpy(*dst, src, len);
    (*dst)[len] = '\0';

    return OK;
}
