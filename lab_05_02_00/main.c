#include "file_utils.h"

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        printf("Not enough arguments\n");
        return NOT_ENOUGH_ARGUMENTS;
    }

    FILE *f;
    f = fopen(argv[1], "r");
    if (f == NULL)
    {
        printf("I/O error\n");
        return IO_ERROR;
    }

    double sum = 0.0;
    int count = 0;
    double avg;
    if (average(f, sum, count, &avg) == NOT_ENOUGH_DATA)
    {
        printf("Not enough data\n");
        return NOT_ENOUGH_DATA;
    }

    fseek(f, 0, SEEK_SET);

    double answer;
    if (nearest_to_average(f, avg, &answer) == NOT_ENOUGH_DATA)
    {
        printf("Not enough data\n");
        return NOT_ENOUGH_DATA;
    }
    printf("Nearest to average: %.6lf\n", answer);

    fclose(f);

    return OK;
}
