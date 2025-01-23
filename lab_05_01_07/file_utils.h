#ifndef FILE_UTILS_H
#define FILE_UTILS_H

#include <stdio.h>

#define OK 0
#define NOT_ENOUGH_DATA (-1)

int process(FILE *f, int *count);

#endif//FILE_UTILS_H
