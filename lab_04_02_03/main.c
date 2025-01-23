#include "string_funcs.h"
#include <stdio.h>
#include <string.h>

#define OK 0
#define NO_UNIQUE 1
#define IO_ERROR 2
#define BUFFER_ERROR 3

int main(void)
{
    string_t string1;

    printf("Enter first string: ");
    if (!fgets(string1, STRING_LENGTH, stdin))
    {
        printf("String wasn't entered\n");
        return IO_ERROR;
    }

    size_t pos = strcspn(string1, "\n");
    if (pos == strlen(string1))
    {
        printf("Buffer overflow\n");
        return BUFFER_ERROR;
    }
    else
        string1[pos] = '\0';

    string_t string2;

    printf("Enter second string: ");
    if (!fgets(string2, STRING_LENGTH, stdin))
    {
        printf("String wasn't entered\n");
        return IO_ERROR;
    }

    pos = strcspn(string2, "\n");
    if (pos == strlen(string2))
    {
        printf("Buffer overflow\n");
        return BUFFER_ERROR;
    }
    else
        string2[pos] = '\0';

    string_t result_string;
    cat_strings(string1, string2, result_string);

    words_t words;
    size_t length = split(result_string, words);

    words_t unique_words;
    size_t length_unique = find_unique_words(words, unique_words, length);

    if (length_unique == 0)
        return NO_UNIQUE;

    printf("Result:");
    for (size_t i = 0; i < length_unique; i++)
        printf(" %s", unique_words[i]);
    printf("\n");

    return OK;
}
