#ifndef STRING_FUNCS_H
#define STRING_FUNCS_H

#include <stdlib.h>

#define STRING_LENGTH 257
#define WORD_LENGTH 17

typedef char string_t[STRING_LENGTH];
typedef char words_t[STRING_LENGTH][WORD_LENGTH];
typedef char word_t[WORD_LENGTH];

size_t split(string_t sentence, words_t words);
void join(string_t result_string, words_t words, size_t length_array);
void modify_word(char word[], char new_word[]);
size_t array_without_last_word(words_t words, word_t last_word, size_t length_array, words_t result_array);
size_t reverse_array(words_t array, words_t reversed_array, size_t length);

#endif //STRING_FUNCS_H
