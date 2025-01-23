#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "errors.h"
#include "matrix.h"

int allocate_matrix(matrix_t *matrix)
{
    double **ptrs = malloc(matrix->n * sizeof(double *));
    if (!ptrs)
    {
        fprintf(stderr, "Memory error\n");
        return MEMORY_ERROR;
    }

    double *data = calloc(matrix->n * matrix->m, sizeof(double));
    if (!data)
    {
        free(ptrs);
        fprintf(stderr, "Memory error\n");
        return MEMORY_ERROR;
    }

    for (int i = 0; i < matrix->n; i++)
        ptrs[i] = data + i * matrix->m;

    matrix->data = ptrs;

    return OK;
}

void free_matrix(double **ptrs)
{
    free(ptrs[0]);
    free(ptrs);
}

int read_matrix(FILE *f, matrix_t *matrix)
{
    int row, col;
    double value;

    for (int i = 0; i < matrix->not_zero; i++)
    {
        if (fscanf(f, "%d%d%lf", &row, &col, &value) != 3)
        {
            fprintf(stderr, "I/O error\n");
            return IO_ERROR;
        }

        if (row <= 0 || col <= 0 || row > matrix->n || col > matrix->m)
        {
            fprintf(stderr, "Incorrect matrix data\n");
            return INCORRECT_DATA;
        }

        matrix->data[row - 1][col - 1] = value;
    }

    return OK;
}

int init_matrix(char *filepath, matrix_t *matrix)
{
    FILE *f = fopen(filepath, "r");
    if (!f)
    {
        fprintf(stderr, "I/O error\n");
        return IO_ERROR;
    }

    if (fscanf(f, "%d%d%d", &(matrix->n), &(matrix->m), &(matrix->not_zero)) != 3)
    {
        fclose(f);
        fprintf(stderr, "I/O error\n");
        return IO_ERROR;
    }
    if (matrix->n == 0 || matrix->m == 0 || matrix->not_zero == 0 || matrix->not_zero > matrix->n * matrix->m)
    {
        fclose(f);
        fprintf(stderr, "Incorrect matrix data\n");
        return INCORRECT_DATA;
    }

    int rc = allocate_matrix(matrix);
    if (rc != OK)
    {
        fclose(f);
        return rc;
    }

    rc = read_matrix(f, matrix);
    if (rc != OK)
    {
        fclose(f);
        free_matrix(matrix->data);
        return rc;
    }

    fclose(f);

    return OK;
}

void print_matrix(double **matrix, size_t n, size_t m)
{
    for (size_t i = 0; i < n; i++)
    {
        for (size_t j = 0; j < m; j++)
            printf("%lf ", matrix[i][j]);
        printf("\n");
    }
}

void write_matrix(FILE *f, matrix_t *matrix)
{
    fprintf(f, "%d %d\n", matrix->n, matrix->m);

    for (int i = 0; i < matrix->n; i++)
    {
        for (int j = 0; j < matrix->m; j++)
            fprintf(f, "%.6lf ", matrix->data[i][j]);
        fprintf(f, "\n");
    }
}

// Предполагаю, что на вход поступают корректные данные
void matrix_addition(matrix_t *result_matrix, matrix_t *matrix1, matrix_t *matrix2)
{
    size_t n = matrix1->n;
    size_t m = matrix1->m;

    for (size_t i = 0; i < n; i++)
        for (size_t j = 0; j < m; j++)
            result_matrix->data[i][j] = matrix1->data[i][j] + matrix2->data[i][j];
}

// Предполагаю, что на вход поступают корректные данные
void matrix_multiplication(matrix_t *result_matrix, matrix_t *matrix1, matrix_t *matrix2)
{
    for (int i1 = 0; i1 < matrix1->n; i1++)
        for (int j2 = 0; j2 < matrix2->m; j2++)
        {
            double sum = 0.0;
            for (int j1 = 0; j1 < matrix1->m; j1++)
                sum += matrix1->data[i1][j1] * matrix2->data[j1][j2];
            result_matrix->data[i1][j2] = sum;
        }
}

void swap_rows(double *row1, double *row2, int n)
{
    for (int i = 0; i < n; i++)
    {
        double tmp = row1[i];
        row1[i] = row2[i];
        row2[i] = tmp;
    }
}

void normalize_row(double *row, double first_coef, int n)
{
    for (int i = 0; i < n; i++)
        row[i] = row[i] / first_coef;
}

int gauss(matrix_t coeffs)
{
    for (int i = 0; i < coeffs.m - 1; i++)
    {
        double max_coeff = coeffs.data[i][i];
        int ind_max = i;
        for (int j = i; j < coeffs.n; j++)
            if (fabs(coeffs.data[j][i]) > fabs(max_coeff))
            {
                max_coeff = coeffs.data[j][i];
                ind_max = j;
            }

        if (fabs(max_coeff) < EPS)
            return 0;

        swap_rows(coeffs.data[i], coeffs.data[ind_max], coeffs.m);

        for (int j = i; j < coeffs.n; j++)
            if (fabs(coeffs.data[j][i]) >= EPS)
                normalize_row(coeffs.data[j], coeffs.data[j][i], coeffs.m);

        for (int p = i + 1; p < coeffs.n; p++)
            if (fabs(coeffs.data[p][i]) >= EPS)
                for (int q = i; q < coeffs.m; q++)
                    coeffs.data[p][q] -= coeffs.data[i][q];
    }

    for (int i = coeffs.n - 1; i >= 0; i--)
    {
        for (int p = i - 1; p >= 0; p--)
        {
            double factor = coeffs.data[p][i];
            for (int q = i; q < coeffs.m; q++)
                coeffs.data[p][q] -= factor * coeffs.data[i][q];
        }
    }

    return 1;
}

int inverse_matrix(matrix_t *inv_matrix, matrix_t *matrix)
{
    matrix_t matrix_tmp;
    matrix_tmp.n = matrix->n;
    matrix_tmp.m = matrix->m + 1;
    int rc = allocate_matrix(&matrix_tmp);
    if (rc)
        return rc;

    for (int i = 0; i < matrix->n; i++)
    {
        for (int p = 0; p < matrix->n; p++)
            for (int q = 0; q < matrix->m; q++)
                matrix_tmp.data[p][q] = matrix->data[p][q];

        for (int j = 0; j < matrix->n; j++)
            matrix_tmp.data[j][matrix->m] = j == i;

        if (!gauss(matrix_tmp))
        {
            free_matrix(matrix_tmp.data);
            fprintf(stderr, "Inverse matrix doesn't exist\n");
            return INVERSE_MATRIX_ERROR;
        }

        for (int j = 0; j < matrix->n; j++)
            inv_matrix->data[j][i] = matrix_tmp.data[j][matrix->m];
    }

    free_matrix(matrix_tmp.data);

    return OK;
}
