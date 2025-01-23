#include <stdlib.h>
#include <string.h>

#include "associative_array.h"

typedef struct
{
    char *key;
    int value;
} data_t;

typedef struct node_t node_t;

struct node_t
{
    data_t *data;
    struct node_t *next;
};

typedef struct assoc_array_type assoc_array_type;

struct assoc_array_type
{
    node_t *head;
};

assoc_array_t assoc_array_create(void)
{
    assoc_array_t arr = (assoc_array_t) malloc(sizeof(struct assoc_array_type));
    if (!arr)
        return NULL;

    arr->head = NULL;

    return arr;
}

void assoc_array_destroy(assoc_array_t *arr)
{
    if (arr == NULL || *arr == NULL)
        return;

    if (assoc_array_clear(*arr))
        return;

    free(*arr);
    *arr = NULL;
}

assoc_array_error_t assoc_array_insert(assoc_array_type *arr, const char *key, int num)
{
    if (!arr || !key || strlen(key) == 0)
        return ASSOC_ARRAY_INVALID_PARAM;

    node_t *tmp = arr->head;
    while (tmp)
    {
        if (strcmp(tmp->data->key, key) == 0)
            return ASSOC_ARRAY_KEY_EXISTS;

        tmp = tmp->next;
    }

    node_t *new_node = (node_t *) malloc(sizeof(node_t));
    if (new_node == NULL)
        return ASSOC_ARRAY_MEM;

    data_t *new_data = (data_t *) malloc(sizeof(data_t));
    if (new_data == NULL)
    {
        free(new_node);
        return ASSOC_ARRAY_MEM;
    }

    new_data->key = strdup(key);
    if (new_data->key == NULL)
    {
        free(new_node);
        free(new_data);
        return ASSOC_ARRAY_MEM;
    }
    new_data->value = num;

    new_node->data = new_data;
    new_node->next = arr->head;
    arr->head = new_node;

    return ASSOC_ARRAY_OK;
}

assoc_array_error_t assoc_array_find(const assoc_array_t arr, const char *key, int **num)
{
    if (!arr || !key || strlen(key) == 0 || !num)
        return ASSOC_ARRAY_INVALID_PARAM;

    node_t *tmp = arr->head;
    while (tmp)
    {
        if (strcmp(tmp->data->key, key) == 0)
        {
            *num = &(tmp->data->value);
            return ASSOC_ARRAY_OK;
        }

        tmp = tmp->next;
    }

    return ASSOC_ARRAY_NOT_FOUND;
}

assoc_array_error_t assoc_array_remove(assoc_array_t arr, const char *key)
{
    if (!arr || !key || strlen(key) == 0)
        return ASSOC_ARRAY_INVALID_PARAM;

    node_t *prev = NULL;
    node_t *tmp = arr->head;

    while (tmp)
    {
        if (strcmp(tmp->data->key, key) == 0)
        {
            if (!prev)
                arr->head = tmp->next;
            else
                prev->next = tmp->next;

            free(tmp->data->key);
            free(tmp->data);
            free(tmp);

            return ASSOC_ARRAY_OK;
        }

        prev = tmp;
        tmp = tmp->next;
    }

    return ASSOC_ARRAY_NOT_FOUND;
}

assoc_array_error_t assoc_array_clear(assoc_array_t arr)
{
    if (!arr)
        return ASSOC_ARRAY_INVALID_PARAM;

    node_t *cur = arr->head;
    while (cur)
    {
        node_t *tmp = cur;
        cur = cur->next;

        free(tmp->data->key);
        free(tmp->data);
        free(tmp);
    }

    arr->head = NULL;

    return ASSOC_ARRAY_OK;
}

assoc_array_error_t assoc_array_each(const assoc_array_t arr, void (*action)(const char *key, int *num, void *param), void *param)
{
    if (!arr || !action)
        return ASSOC_ARRAY_INVALID_PARAM;

    node_t *tmp = arr->head;
    while (tmp)
    {
        action(tmp->data->key, &(tmp->data->value), param);

        tmp = tmp->next;
    }

    return ASSOC_ARRAY_OK;
}

assoc_array_error_t assoc_array_min(const assoc_array_t arr, int **num)
{
    if (!arr || !num)
        return ASSOC_ARRAY_INVALID_PARAM;

    if (!(arr->head))
        return ASSOC_ARRAY_NOT_FOUND;

    node_t *tmp = arr->head;
    char *min_key = tmp->data->key;
    *num = &(tmp->data->value);

    while (tmp)
    {
        if (strcmp(tmp->data->key, min_key) < 0)
        {
            min_key = tmp->data->key;
            *num = &(tmp->data->value);
        }

        tmp = tmp->next;
    }

    return ASSOC_ARRAY_OK;
}

assoc_array_error_t assoc_array_max(const assoc_array_t arr, int **num)
{
    if (!arr || !num)
        return ASSOC_ARRAY_INVALID_PARAM;

    if (!(arr->head))
        return ASSOC_ARRAY_NOT_FOUND;

    node_t *tmp = arr->head;
    char *max_key = tmp->data->key;
    *num = &(tmp->data->value);

    while (tmp)
    {
        if (strcmp(tmp->data->key, max_key) > 0)
        {
            max_key = tmp->data->key;
            *num = &(tmp->data->value);
        }

        tmp = tmp->next;
    }

    return ASSOC_ARRAY_OK;
}
