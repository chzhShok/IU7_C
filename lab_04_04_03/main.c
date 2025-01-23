#include "string_funcs.h"
#include <stdio.h>
#include <string.h>

#define OK 0
#define BUFFER_ERROR 1
#define IO_ERROR 2

int main(void)
{
    string_t phone_number;

    if (!fgets(phone_number, STRING_LENGTH, stdin))
        return IO_ERROR;

    size_t pos = strcspn(phone_number, "\n");
    if (pos == strlen(phone_number))
        return BUFFER_ERROR;
    else
        phone_number[pos] = '\0';

    size_t start = 0, end = pos - 1;
    trim(phone_number, &start, &end);

//    for (size_t i = start; i <= end; i++)
//        printf("%c", phone_number[i]);

//    is_phone_number(phone_number + start);
    int rc = is_phone_number(phone_number + start);

    if (rc != 0)
        printf("NO\n");
    else
        printf("YES\n");

    return OK;
}
