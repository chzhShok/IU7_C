#include <stdlib.h>
#include <string.h>

#include "associative_array.h"

#define INIT_SIZE 32
#define STEP_SIZE 2

typedef struct
{
    char *key;
    int value;
} data_t;

typedef struct assoc_array_type assoc_array_type;

struct assoc_array_type
{
    data_t *data;
    size_t len;
    size_t allocated;
};

assoc_array_t assoc_array_create(void)
{
    assoc_array_t arr = (assoc_array_t) malloc(sizeof(struct assoc_array_type));
    if (!arr)
        return NULL;

    arr->len = 0;
    arr->allocated = 0;
    arr->data = NULL;

    return arr;
}

void assoc_array_destroy(assoc_array_t *arr)
{
    if (!(*arr))
        return;

    if (assoc_array_clear(*arr))
        return;

    free(*arr);

    *arr = NULL;
}

static int is_key_in_array(assoc_array_t arr, const char *key)
{
    for (size_t i = 0; i < arr->len; i++)
        if (strcmp((arr->data[i]).key, key) == 0)
            return 1;

    return 0;
}

assoc_array_error_t assoc_array_insert(assoc_array_t arr, const char *key, int num)
{
    if (!arr || !key || strlen(key) == 0)
        return ASSOC_ARRAY_INVALID_PARAM;

    if (is_key_in_array(arr, key))
        return ASSOC_ARRAY_KEY_EXISTS;

    if (!arr->data)
    {
        arr->data = malloc(INIT_SIZE * sizeof(arr->data[0]));
        if (!arr->data)
            return ASSOC_ARRAY_MEM;

        arr->allocated = INIT_SIZE;
    }
    else if (arr->len == arr->allocated)
    {
        data_t *tmp = realloc(arr->data, arr->allocated * STEP_SIZE * sizeof(arr->data[0]));

        if (!tmp)
            return ASSOC_ARRAY_MEM;

        arr->data = tmp;
        arr->allocated *= STEP_SIZE;
    }

    (arr->data[arr->len]).value = num;
    (arr->data[arr->len]).key = strdup(key);
    arr->len++;

    return ASSOC_ARRAY_OK;
}

assoc_array_error_t assoc_array_find(const assoc_array_t arr, const char *key, int **num)
{
    if (!arr || !key || !num || strlen(key) == 0)
        return ASSOC_ARRAY_INVALID_PARAM;

    for (size_t i = 0; i < arr->len; i++)
        if (strcmp((arr->data[i]).key, key) == 0)
        {
            *num = &((arr->data[i]).value);
            return ASSOC_ARRAY_OK;
        }

    return ASSOC_ARRAY_NOT_FOUND;
}

assoc_array_error_t assoc_array_remove(assoc_array_t arr, const char *key)
{
    if (!arr || !key || strlen(key) == 0)
        return ASSOC_ARRAY_INVALID_PARAM;

    for (size_t i = 0; i < arr->len; i++)
        if (strcmp((arr->data[i]).key, key) == 0)
        {
            free((arr->data[i]).key);
            memmove(arr->data + i, arr->data + i + 1, (arr->len - i - 1) * sizeof(arr->data[0]));
            arr->len--;

            return ASSOC_ARRAY_OK;
        }

    return ASSOC_ARRAY_NOT_FOUND;
}

assoc_array_error_t assoc_array_clear(assoc_array_t arr)
{
    if (!arr)
        return ASSOC_ARRAY_INVALID_PARAM;

    for (size_t i = 0; i < arr->len; i++)
        free((arr->data[i]).key);

    arr->len = 0;
    arr->allocated = 0;

    free(arr->data);

    return ASSOC_ARRAY_OK;
}

assoc_array_error_t assoc_array_each(const assoc_array_t arr, void (*action)(const char *key, int *num, void *param), void *param)
{
    if (!arr || !action)
        return ASSOC_ARRAY_INVALID_PARAM;

    for (size_t i = 0; i < arr->len; i++)
        action((arr->data[i]).key, &((arr->data[i]).value), param);

    return ASSOC_ARRAY_OK;
}

assoc_array_error_t assoc_array_min(const assoc_array_t arr, int **num)
{
    if (!arr || !num)
        return ASSOC_ARRAY_INVALID_PARAM;

    if (arr->len == 0)
        return ASSOC_ARRAY_NOT_FOUND;

    char *min_key = (arr->data[0]).key;
    *num = &((arr->data[0]).value);

    for (size_t i = 1; i < arr->len; i++)
        if (strcmp((arr->data[i]).key, min_key) < 0)
        {
            min_key = (arr->data[i]).key;
            *num = &((arr->data[i]).value);
        }

    return ASSOC_ARRAY_OK;
}

assoc_array_error_t assoc_array_max(const assoc_array_t arr, int **num)
{
    if (!arr || !num)
        return ASSOC_ARRAY_INVALID_PARAM;

    if (arr->len == 0)
        return ASSOC_ARRAY_NOT_FOUND;

    char *max_key = (arr->data[0]).key;
    *num = &((arr->data[0]).value);

    for (size_t i = 1; i < arr->len; i++)
        if (strcmp((arr->data[i]).key, max_key) > 0)
        {
            max_key = (arr->data[i]).key;
            *num = &((arr->data[i]).value);
        }

    return ASSOC_ARRAY_OK;
}
