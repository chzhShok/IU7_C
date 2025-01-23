#include <stdio.h>
#include <string.h>

#include "errors.h"
#include "matrix.h"

#define MIN_ARGS 4
#define MAX_ARGS 5

int main(int argc, char *argv[])
{
    if (argc < MIN_ARGS || argc > MAX_ARGS)
    {
        fprintf(stderr, "Incorrect number of arguments\n");
        return INCORRECT_ARGS;
    }

    char *operation_type = argv[1];
    if (strcmp(operation_type, "a") == 0 || strcmp(operation_type, "m") == 0)
    {
        if (argc != 5)
        {
            fprintf(stderr, "Incorrect arguments\n");
            return INCORRECT_ARGS;
        }

        matrix_t matrix1 = { 0 };
        int rc = init_matrix(argv[2], &matrix1);
        if (rc)
            return rc;

        matrix_t matrix2 = { 0 };
        rc = init_matrix(argv[3], &matrix2);
        if (rc)
        {
            free_matrix(matrix1.data);
            return rc;
        }

        matrix_t result_matrix = { 0 };
        if (strcmp(operation_type, "a") == 0)
        {
            if (matrix1.n != matrix2.n || matrix1.m != matrix2.m)
            {
                fprintf(stderr, "Incorrect data for addition\n");
                free_matrix(matrix1.data);
                free_matrix(matrix2.data);
                return IO_ERROR;
            }

            result_matrix.n = matrix1.n;
            result_matrix.m = matrix1.m;
            rc = allocate_matrix(&result_matrix);
            if (rc)
            {
                free_matrix(matrix1.data);
                free_matrix(matrix2.data);
                return rc;
            }

            matrix_addition(&result_matrix, &matrix1, &matrix2);
        }
        else if (strcmp(operation_type, "m") == 0)
        {
            if (matrix1.m != matrix2.n)
            {
                fprintf(stderr, "Incorrect data for multiplication\n");
                free_matrix(matrix1.data);
                free_matrix(matrix2.data);
                return IO_ERROR;
            }

            result_matrix.n = matrix1.n;
            result_matrix.m = matrix2.m;
            rc = allocate_matrix(&result_matrix);
            if (rc)
            {
                free_matrix(matrix1.data);
                free_matrix(matrix2.data);
                return rc;
            }

            matrix_multiplication(&result_matrix, &matrix1, &matrix2);
        }

        free_matrix(matrix1.data);
        free_matrix(matrix2.data);

        FILE *f = fopen(argv[4], "w");
        if (!f)
        {
            free_matrix(result_matrix.data);
            fprintf(stderr, "Error while opening file\n");
            return FILE_ERROR;
        }

        write_matrix(f, &result_matrix);

        fclose(f);
        free_matrix(result_matrix.data);
    }
    else if (strcmp(operation_type, "o") == 0)
    {
        if (argc != 4)
        {
            fprintf(stderr, "Incorrect arguments\n");
            return INCORRECT_ARGS;
        }

        matrix_t matrix = { 0 };
        int rc = init_matrix(argv[2], &matrix);
        if (rc)
            return rc;

        if (matrix.n != matrix.m)
        {
            fprintf(stderr, "Incorrect matrix parameters\n");
            free_matrix(matrix.data);
            return INCORRECT_DATA;
        }

        matrix_t inv_matrix = { 0 };
        inv_matrix.n = matrix.n;
        inv_matrix.m = matrix.m;
        rc = allocate_matrix(&inv_matrix);
        if (rc)
        {
            free_matrix(matrix.data);
            return rc;
        }

        rc = inverse_matrix(&inv_matrix, &matrix);
        if (rc == INVERSE_MATRIX_ERROR)
        {
            free_matrix(matrix.data);
            free_matrix(inv_matrix.data);
            return INVERSE_MATRIX_ERROR;
        }

        free_matrix(matrix.data);

        FILE *f = fopen(argv[3], "w");
        if (!f)
        {
            free_matrix(inv_matrix.data);
            fprintf(stderr, "Error while opening file\n");
            return FILE_ERROR;
        }

        write_matrix(f, &inv_matrix);

        fclose(f);
        free_matrix(inv_matrix.data);
    }
    else
    {
        fprintf(stderr, "Incorrect arguments\n");
        return INCORRECT_ARGS;
    }

    return OK;
}
