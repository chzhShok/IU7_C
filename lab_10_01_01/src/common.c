#include <stdio.h>
#include <string.h>

#include "common.h"
#include "error.h"
#include "list.h"

int process_operation(char *operation, node_t **head)
{
    if (strcmp(operation, "pf") == 0)
    {
        if (!pop_front(head))
            return EMPTY_LIST;
    }
    else if (strcmp(operation, "pb") == 0)
    {
        if (!pop_back(head))
            return EMPTY_LIST;
    }
    else if (strcmp(operation, "c") == 0)
    {
        node_t *new_head = NULL;

        copy(*head, &new_head);

        FILE *f_new = fopen("out_new.txt", "w");
        if (!f_new)
            return IO_ERROR;

        fprint_list(f_new, new_head);

        fclose(f_new);
    }
    else if (strcmp(operation, "s") == 0)
    {
        *head = sort(*head, comparator);
    }
    else
    {
        return INCORRECT_OPERATION;
    }

    return OK;
}

int process_error(int rc)
{
    if (rc == EMPTY_LIST)
        fprintf(stderr, "Error: list is empty\n");
    else if (rc == IO_ERROR)
        fprintf(stderr, "I/O error\n");
    else if (rc == INCORRECT_OPERATION)
        fprintf(stderr, "Error: incorrect operation");

    return OK;
}
