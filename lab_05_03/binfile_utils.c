#include "binfile_utils.h"

int file_size(FILE *f, size_t *size)
{
    long sz;

    if (fseek(f, 0, SEEK_END))
        return 1;

    sz = ftell(f);

    if (sz < 0)
        return 1;

    *size = sz;

    return fseek(f, 0, SEEK_SET);
}

int fill_file_randomly(FILE *f, long count)
{
    srand(time(NULL));
    for (int i = 1; i <= count; i++)
    {
        int num = rand() % 1000;
        if (fwrite(&num, sizeof(int), 1, f) != 1)
            return IO_ERROR;
    }

    fseek(f, SEEK_SET, 0);

    return OK;
}

int print_file(FILE *f)
{
    size_t size;

    if (file_size(f, &size) != OK)
        return IO_ERROR;

    size_t number_count = size / sizeof(int);
    if (number_count == 0)
        return EMPTY_FILE;

    int num;
    size_t bytes_read = 0;
    for (size_t i = 0; i < number_count; i++)
    {
        if (fread(&num, sizeof(int), 1, f) != 1)
            return IO_ERROR;
        printf("%d ", num);
        bytes_read += sizeof(int);
    }
    printf("\n");

    if (bytes_read != size)
        return IO_ERROR;

    return OK;
}


int get_number_by_pos(FILE *f, size_t pos, int *num)
{
    if (pos == 0)
        pos++;

    fseek(f, (long) ((pos - 1) * sizeof(int)), SEEK_SET);
    if (fread(num, sizeof(int), 1, f) != 1)
        return -1;

    return OK;
}


int put_number_by_pos(FILE *f, size_t pos, int num)
{
    if (pos == 0)
        pos++;

    fseek(f, (long) ((pos - 1) * sizeof(int)), SEEK_SET);
    if (fwrite(&num, sizeof(int), 1, f) != 1)
        return -1;

    return OK;
}

int swap_numbers(size_t i, size_t min_ind, FILE *f)
{
    int num, min_num;
    if (get_number_by_pos(f, i, &num) != OK)
        return IO_ERROR;

    if (get_number_by_pos(f, min_ind, &min_num) != OK)
        return IO_ERROR;

    if (put_number_by_pos(f, i, min_num) != OK)
        return IO_ERROR;

    if (put_number_by_pos(f, min_ind, num) != OK)
        return IO_ERROR;

    return OK;
}

int sort_file(FILE *f)
{
    size_t size;
    if (file_size(f, &size) != OK)
        return IO_ERROR;

    size_t number_count = size / sizeof(int) + 1;
    if (number_count == 1)
        return EMPTY_FILE;

    size_t bytes_read = 0;
    for (size_t i = 0; i < (number_count - 1); i++)
    {
        size_t min_ind = i;
        int min_num;

        if (get_number_by_pos(f, i, &min_num) != OK)
            return IO_ERROR;

        bytes_read += sizeof(int);

        for (size_t j = i + 1; j < number_count; j++)
        {
            int num;
            if (get_number_by_pos(f, j, &num) != OK)
                return IO_ERROR;

            if (num < min_num)
            {
                min_ind = j;
                min_num = num;
            }
        }
        if (swap_numbers(i, min_ind, f) != OK)
            return IO_ERROR;
    }

    if (bytes_read != size)
        return IO_ERROR;

    return OK;
}

int import(FILE *f_txt, FILE *f_bin)
{
    int num;
    while (fscanf(f_txt, "%d", &num) == 1)
        fwrite(&num, sizeof(int), 1, f_bin);

    if (!feof(f_txt))
        return IO_ERROR;

    return OK;
}

int export(FILE *f_bin, FILE *f_txt)
{
    size_t size;
    if (file_size(f_bin, &size) != OK)
        return IO_ERROR;

    int num;
    size_t bytes_read = 0;
    while (fread(&num, sizeof(int), 1, f_bin) == 1)
    {
        bytes_read += sizeof(int);
        fprintf(f_txt, "%d ", num);
    }

    if (bytes_read != size)
        return IO_ERROR;

    return OK;
}
