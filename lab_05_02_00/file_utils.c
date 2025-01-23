#include "file_utils.h"

int average(FILE *f, double sum, int count, double *average)
{
    double num;
    while (fscanf(f, "%lf", &num) == 1)
    {
        sum += num;
        count++;
    }

    if (count == 0)
        return NOT_ENOUGH_DATA;

    *average = sum / count;
    return OK;
}

int nearest_to_average(FILE *f, double average, double *answer)
{
    double num;
    double diff;
    if (fscanf(f, "%lf", &num) != 1)
        return NOT_ENOUGH_DATA;

    diff = fabs(num - average);
    *answer = num;

    while (fscanf(f, "%lf", &num) == 1)
        if ((fabs(num - average) - diff) < EPS)
        {
            *answer = num;
            diff = fabs(num - average);
        }

    return OK;
}
