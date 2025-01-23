#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "list.h"
#include "common.h"

/***
./app.exe FILE OPERATION

FILE:
 - FILM
 - YEAR
 - RATING

OPERATION:
 - pf: pop_front
 - pb: pop_back
 - c: copy
 - s: sort
***/

int main(int argc, char **argv)
{
    if (argc > 3)
    {
        fprintf(stderr, "Error: incorrect number of arguments");
        return ARGUMENT_ERROR;
    }

    node_t *head = NULL;

    FILE *f = fopen(argv[1], "r");
    if (!f)
    {
        fprintf(stderr, "I/O error\n");
        return IO_ERROR;
    }

    if (read_data(f, &head))
    {
        fprintf(stderr, "Error reading data\n");
        fclose(f);
        return IO_ERROR;
    }
    fclose(f);

    char *operation = argv[2];

    int rc = process_operation(operation, &head);

    if (rc != 0)
    {
        process_error(rc);
        return rc;
    }

    f = fopen("out.txt", "w");
    if (!f)
    {
        fprintf(stderr, "I/O error\n");
        return IO_ERROR;
    }

    fprint_list(f, head);

    free_list(head);

    return OK;
}
