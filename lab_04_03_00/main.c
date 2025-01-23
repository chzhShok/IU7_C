#include "string_funcs.h"
#include <stdio.h>
#include <string.h>

#define OK 0
#define RESULT_ERROR 1
#define IO_ERROR 2
#define BUFFER_ERROR 3

int main(void)
{
    string_t input_string;

    if (!fgets(input_string, STRING_LENGTH, stdin))
        return IO_ERROR;

    size_t pos = strcspn(input_string, "\n");
    if (pos == strlen(input_string))
        return BUFFER_ERROR;
    else
        input_string[pos] = '\0';

    words_t words;
    size_t length_array = split(input_string, words);

    word_t last_word;
    strncpy(last_word, words[length_array - 1], WORD_LENGTH - 1);
    last_word[WORD_LENGTH - 1] = '\0';

    words_t new_words;
    size_t new_length = array_without_last_word(words, last_word, length_array, new_words);

    words_t reversed_words;
    size_t length_reversed = reverse_array(new_words, reversed_words, new_length);

    string_t new_string = "";
    if (new_length != 0)
        join(new_string, reversed_words, length_reversed);

    if (strcmp(new_string, "") == 0)
    {
        printf("Result string is empty\n");
        return RESULT_ERROR;
    }

    printf("Result: %s\n", new_string);

    return OK;
}
