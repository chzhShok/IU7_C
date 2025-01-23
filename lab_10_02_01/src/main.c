#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "list.h"
#include "common.h"

#define OPERATION_LEN 10

int main(void)
{
    node_t *list = NULL;

    char *operation = malloc(sizeof(char) * OPERATION_LEN);

    if (fgets(operation, OPERATION_LEN, stdin) == NULL)
        return IO_ERROR;
    operation[strcspn(operation, "\n")] = '\0';

    int rc = process_operation(operation, &list);
    if (rc != 0)
        return rc;

    free_list(list);
    free(operation);

    return OK;
}
