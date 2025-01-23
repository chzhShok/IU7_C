#ifndef FILE_UTILS_H
#define FILE_UTILS_H

#include <stdio.h>
#include <math.h>

#define OK 0
#define NOT_ENOUGH_ARGUMENTS 1
#define IO_ERROR 2
#define NOT_ENOUGH_DATA 2
#define EPS 1e-8

int average(FILE *f, double sum, int count, double *average);
int nearest_to_average(FILE *f, double average, double *answer);

#endif//FILE_UTILS_H
