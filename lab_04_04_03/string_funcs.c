#include "string_funcs.h"
#include <ctype.h>

void trim(string_t string, size_t *start, size_t *end)
{
    while (isspace(string[*start]))
        (*start)++;

    while (isspace(string[*end]))
        (*end)--;
}

int start_from_operator_code(char string[], size_t ind)
{
    size_t i = ind;

    for (size_t j = i; j < i + 3; j++)
        if (isdigit(string[i]) == 0)
            return -1;
    i += 3;

    if (string[i] != ')')
        return -1;
    i++;

    if (string[i] != '-')
        return -1;
    i++;

    for (size_t j = i; j < i + 3; j++)
        if (isdigit(string[j]) == 0)
            return -1;
    i += 3;

    for (size_t k = 0; k < 2; k++)
    {
        if (string[i] != '-')
            return -1;
        i++;

        for (size_t j = i; j < i + 2; j++)
            if (isdigit(string[j]) == 0)
                return -1;
        i += 2;
    }

    return (int) i;
}

int start_from_country_code(char string[], size_t ind)
{
    size_t i = ind;
    int is_digit = 0;
    while (isdigit(string[i]) != 0)
    {
        is_digit++;
        i++;
    }

    if (is_digit == 0)
        return -1;

    if (string[i] != '(')
        return -1;

    i++;
    int j = start_from_operator_code(string, i);

    if (j == -1)
        return -1;

    return j;
}

int check_end(string_t string, size_t position)
{
    for (size_t i = position; string[i] != '\0'; i++)
        if (!isspace((unsigned char) string[i]))
            return 1;

    return 0;
}

int is_phone_number(char string[])
{
    if (string[0] == '+')
    {
        int ind = start_from_country_code(string, 1);
        if (ind == -1)
            return 1;

        int rc = check_end(string, ind);
        if (rc != 0)
            return 1;
    }
    else if (string[0] == '(')
    {
        int ind = start_from_operator_code(string, 1);
        if (ind == -1)
            return 1;

        int rc = check_end(string, ind);
        if (rc != 0)
            return 1;
    }
    else
        return 1;

    return 0;
}
