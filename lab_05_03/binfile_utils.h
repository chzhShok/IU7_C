#ifndef FILE_UTILS_H
#define FILE_UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define OK 0
#define IO_ERROR 1
#define EMPTY_FILE 2

int fill_file_randomly(FILE *f, long num);
int print_file(FILE *f);
int sort_file(FILE *f);
int import(FILE *f_txt, FILE *f_bin);
int export(FILE *f_bin, FILE *f_txt);

#endif// FILE_UTILS_H
