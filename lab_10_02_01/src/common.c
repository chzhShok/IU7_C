#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "common.h"
#include "error.h"
#include "list.h"

int process_operation(char *operation, node_t **list)
{
    if (strcmp(operation, "val") == 0)
    {
        if (read_polynomial(list))
        {
            free(operation);
            return IO_ERROR;
        }

        int value;

        if (scanf("%d", &value) != 1)
        {
            free_list(*list);
            free(operation);
            return IO_ERROR;
        }

        int ans = calculate_val(list, value);
        printf("%d\n", ans);
    }
    else if (strcmp(operation, "ddx") == 0)
    {
        if (read_polynomial(list))
        {
            free(operation);
            return IO_ERROR;
        }

        node_t *d_list = NULL;
        if (derivative(list, &d_list))
        {
            free_list(*list);
            free(operation);
            return MEMORY_ERROR;
        }

        print_polynomial(d_list);

        free_list(d_list);
    }
    else if (strcmp(operation, "sum") == 0)
    {
        if (read_polynomial(list))
        {
            free(operation);
            return IO_ERROR;
        }

        node_t *list_2 = NULL;

        if (read_polynomial(&list_2))
        {
            free_list(*list);
            free(operation);
            return IO_ERROR;
        }

        node_t *res_list = sum_polynomials(list, &list_2);

        print_polynomial(res_list);

        free_list(list_2);
        free_list(res_list);
    }
    else if (strcmp(operation, "dvd") == 0)
    {
        if (read_polynomial(list))
        {
            free(operation);
            return IO_ERROR;
        }

        node_t *even = NULL;
        node_t *odd = NULL;

        if (odd_even_polynomial(list, &even, &odd))
        {
            free_list(*list);
            free(operation);
            return MEMORY_ERROR;
        }

        print_polynomial(even);
        print_polynomial(odd);

        free_list(even);
        free_list(odd);
    }
    else
    {
        free(operation);
        return OPERATION_ERROR;
    }

    return OK;
}
