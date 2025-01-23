#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "list.h"

node_t *create_node(int degree, int coeff)
{
    node_t *new_node = (node_t *) malloc(sizeof(node_t));
    if (!new_node)
        return NULL;

    new_node->degree = degree;
    new_node->coeff = coeff;
    new_node->next = NULL;

    return new_node;
}

void free_list(node_t *head)
{
    while (head)
    {
        node_t *tmp = head;
        head = head->next;

        free(tmp);
    }
}

void push_back(node_t **head, node_t *new_node)
{
    if (!new_node)
        return;

    if (!(*head))
    {
        *head = new_node;
        return;
    }

    node_t *tmp = *head;
    while (tmp->next)
        tmp = tmp->next;

    tmp->next = new_node;
}

int read_polynomial(node_t **head)
{
    char *line = NULL;
    size_t linecap = 0;
    if (getline(&line, &linecap, stdin) <= 0)
    {
        free(line);
        return EIO;
    }
    line[strcspn(line, "\n")] = '\0';

    char *degree_str, *val_str;
    char *sep = " ";

    val_str = strtok(line, sep);
    if (!val_str)
    {
        free(line);
        return EIO;
    }
    degree_str = strtok(NULL, sep);

    while (degree_str)
    {
        char *endptr;
        int val = (int) strtol(val_str, &endptr, 10);
        if (endptr == val_str)
        {
            free(line);
            free_list(*head);
            return EIO;
        }

        int degree = (int) strtol(degree_str, &endptr, 10);
        if (endptr == degree_str)
        {
            free(line);
            free_list(*head);
            return EIO;
        }

        node_t *new_node = create_node(degree, val);
        if (!new_node)
        {
            free(line);
            free_list(*head);
            return ENOMEM;
        }

        push_back(head, new_node);

        val_str = strtok(NULL, sep);
        if (!val_str)
            break;

        degree_str = strtok(NULL, sep);
    }

    free(line);

    return 0;
}

int calculate_val(node_t **head, int val)
{
    int ans = 0;
    node_t *tmp = *head;

    while (tmp)
    {
        ans += tmp->coeff * (int) pow(val, tmp->degree);
        tmp = tmp->next;
    }

    return ans;
}

int derivative(node_t **head, node_t **d_head)
{
    node_t *tmp = *head;

    while (tmp)
    {
        int new_coeff, new_degree;

        new_coeff = tmp->coeff * tmp->degree;
        if (new_coeff == 0)
        {
            tmp = tmp->next;
            continue;
        }

        new_degree = tmp->degree - 1;

        node_t *new_node = create_node(new_degree, new_coeff);
        if (!new_node)
        {
            free_list(*d_head);
            *d_head = NULL;
            return ENOMEM;
        }

        push_back(d_head, new_node);

        tmp = tmp->next;
    }

    return 0;
}

void print_polynomial(const node_t *head)
{
    node_t *tmp = (node_t *) head;

    while (tmp)
    {
        printf("%d %d ", tmp->coeff, tmp->degree);
        tmp = tmp->next;
    }

    printf("L\n");
}

node_t *sum_polynomials(node_t **head1, node_t **head2)
{
    node_t *tmp1 = *head1;
    node_t *tmp2 = *head2;

    node_t *res = NULL;

    while (tmp1 && tmp2)
    {
        if (tmp1->degree == tmp2->degree)
        {
            node_t *new_node = create_node(tmp1->degree, tmp1->coeff + tmp2->coeff);
            if (!new_node)
            {
                free_list(res);
                return NULL;
            }

            push_back(&res, new_node);

            tmp1 = tmp1->next;
            tmp2 = tmp2->next;
        }
        else if (tmp1->degree > tmp2->degree)
        {
            node_t *new_node = create_node(tmp1->degree, tmp1->coeff);
            if (!new_node)
            {
                free_list(res);
                return NULL;
            }

            push_back(&res, new_node);

            tmp1 = tmp1->next;
        }
        else
        {
            node_t *new_node = create_node(tmp2->degree, tmp2->coeff);
            if (!new_node)
            {
                free_list(res);
                return NULL;
            }

            push_back(&res, new_node);

            tmp2 = tmp2->next;
        }
    }

    while (tmp1)
    {
        node_t *new_node = create_node(tmp1->degree, tmp1->coeff);
        if (!new_node)
        {
            free_list(res);
            return NULL;
        }

        push_back(&res, new_node);

        tmp1 = tmp1->next;
    }

    while (tmp2)
    {
        node_t *new_node = create_node(tmp2->degree, tmp2->coeff);
        if (!new_node)
        {
            free_list(res);
            return NULL;
        }

        push_back(&res, new_node);

        tmp2 = tmp2->next;
    }

    return res;
}

int odd_even_polynomial(node_t **head, node_t **even, node_t **odd)
{
    node_t *tmp = *head;

    while (tmp)
    {
        node_t *new_node = create_node(tmp->degree, tmp->coeff);
        if (!new_node)
            return ENOMEM;

        if (tmp->degree % 2 == 0)
            push_back(even, new_node);
        else
            push_back(odd, new_node);

        tmp = tmp->next;
    }

    return 0;
}
