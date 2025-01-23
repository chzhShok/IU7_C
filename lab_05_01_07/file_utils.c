#include "file_utils.h"

int process(FILE *f, int *count)
{
    int prev_num;
    if (fscanf(f, "%d", &prev_num) != 1)
        return NOT_ENOUGH_DATA;

    int num;
    if (fscanf(f, "%d", &num) != 1)
        return NOT_ENOUGH_DATA;

    int next_num;
    if (fscanf(f, "%d", &next_num) != 1)
        return NOT_ENOUGH_DATA;

    do
    {
        if ((num > next_num) && (num > prev_num))
            (*count)++;

        prev_num = num;
        num = next_num;
    }
    while (fscanf(f, "%d", &next_num) == 1);

    return OK;
}
