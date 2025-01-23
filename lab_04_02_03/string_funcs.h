#ifndef STRING_FUNCS_H
#define STRING_FUNCS_H

#include <stdlib.h>

#define STRING_LENGTH 257
#define WORD_LENGTH 17

typedef char string_t[STRING_LENGTH];
typedef char words_t[STRING_LENGTH][WORD_LENGTH];

size_t split(string_t s, words_t words);
size_t find_unique_words(words_t words, words_t unique_words, size_t length);
void cat_strings(string_t string1, string_t string2, string_t result_string);

#endif //STRING_FUNCS_H
