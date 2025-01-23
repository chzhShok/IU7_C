#include "string_funcs.h"
#include <string.h>

size_t split(string_t sentence, words_t words)
{
    char delimiters[] = ",;:-.!? ";
    char *token = strtok(sentence, delimiters);
    size_t word_i = 0;

    while (token != NULL)
    {
        strncpy(words[word_i], token, WORD_LENGTH);
        words[word_i][WORD_LENGTH - 1] = '\0';
        word_i++;
        token = strtok(NULL, delimiters);
    }

    return word_i;
}

void join(string_t result_string, words_t words, size_t length_array)
{
    for (size_t i = 0; i < length_array - 1; i++)
    {
        strncat(result_string, words[i], WORD_LENGTH);
        strcat(result_string, " ");
    }
    strncat(result_string, words[length_array - 1], WORD_LENGTH);
}

void modify_word(char word[], char new_word[])
{
    size_t ind = 1;
    char first_letter = word[0];
    new_word[0] = first_letter;
    for (size_t i = 1; i < strlen(word); i++)
        if (word[i] != first_letter)
        {
            new_word[ind] = word[i];
            ind++;
        }
    new_word[ind] = '\0';
}

size_t array_without_last_word(words_t words, word_t last_word, size_t length_array, words_t result_array)
{
    size_t ind = 0;

    for (size_t i = 0; i < length_array; i++)
    {
        if (strncmp(last_word, words[i], WORD_LENGTH) != 0)
        {
            word_t modified_word;
            modify_word(words[i], modified_word);
            strncpy(result_array[ind], modified_word, WORD_LENGTH);
            ind++;
        }
    }

    return ind;
}

size_t reverse_array(words_t array, words_t reversed_array, size_t length)
{
    size_t ind = 0;
    for (int i = (int) length - 1; i >= 0; i--)
        strcpy(reversed_array[ind++], array[i]);

    return ind;
}
