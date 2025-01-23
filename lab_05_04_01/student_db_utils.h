#ifndef STUDENT_DATA_BASE_UTILS_H
#define STUDENT_DATA_BASE_UTILS_H

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#ifdef _WIN32
#include <io.h>
#else
#include <fcntl.h>
#endif

#define LASTNAME_LENGTH 26
#define NAME_LENGTH 11
#define CLASS_COUNT 4
#define STUDENTS_LEN 100

#define OK 0
#define IO_ERROR 1
#define EMPTY_FILE 2


typedef struct
{
    char lastname_t[LASTNAME_LENGTH];
    char name_t[NAME_LENGTH];
    uint32_t marks_t[CLASS_COUNT];
} student_t;

int file_size(FILE *f, size_t *size);
void print_file(FILE *f);
int import(FILE *f_txt, FILE *f_bin);
int export(FILE *f_bin, FILE *f_txt);
int my_ftruncate(FILE *f);

int sort_students(FILE *f);

int print_bd_in_another_file(FILE *f_src, FILE *f_dst, char substr[LASTNAME_LENGTH], int *write);

int delete_by_condition(FILE *f);

#endif//STUDENT_DATA_BASE_UTILS_H
