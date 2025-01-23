#ifndef STRING_FUNCS_H
#define STRING_FUNCS_H

#include <stdlib.h>

#define STRING_LENGTH 257
//#define WORD_LENGTH 16

typedef char string_t[STRING_LENGTH];

void trim(string_t string, size_t *start, size_t *end);
int is_phone_number(char string[]);

#endif //STRING_FUNCS_H
