#include "string_funcs.h"
#include <string.h>

size_t split(string_t s, words_t words)
{
    char delimiters[] = ",;:-.!? ";
    size_t word_start = 0, word_length = 0;
    size_t word_i = 0;

    for (size_t i = 0; s[i] != '\0'; i++)
    {
        if (strchr(delimiters, s[i]) == NULL)
            word_length++;
        else
        {
            if (word_length != 0)
            {
                strncpy(words[word_i], s + word_start, word_length);
                words[word_i][word_length] = '\0';
                word_i++;
                word_length = 0;
            }
            word_start = i + 1;
        }
    }

    if (word_length != 0)
    {
        strncpy(words[word_i], s + word_start, word_length);
        words[word_i][word_length] = '\0';
        word_i++;
    }

    return word_i;
}

void cat_strings(string_t string1, string_t string2, string_t result_string)
{
    size_t ind = 0;
    for (size_t i = 0; string1[i] != '\0'; i++)
        result_string[ind++] = string1[i];

    result_string[ind++] = ' ';

    for (size_t i = 0; string2[i] != '\0'; i++)
        result_string[ind++] = string2[i];

    result_string[ind] = '\0';
}

size_t find_unique_words(words_t words, words_t unique_words, size_t length)
{
    size_t ind = 0;
    for (size_t i = 0; i < length; i++)
    {
        int is_unique = 1;
        for (size_t j = 0; j < length; j++)
            if ((i != j) && strcmp(words[i], words[j]) == 0)
                is_unique = 0;

        if (is_unique)
            strcpy(unique_words[ind++], words[i]);
    }

    return ind;
}
