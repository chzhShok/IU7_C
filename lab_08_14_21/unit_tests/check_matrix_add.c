#include <check.h>
#include <stdlib.h>

#include "check_main.h"
#include "errors.h"
#include "matrix.h"

START_TEST(matrix_non_negatives)
{
    matrix_t matrix1 = {0}, matrix2 = {0}, expected_matrix = {0}, result_matrix = {0};

    matrix1.n = matrix2.n = expected_matrix.n = result_matrix.n = N3;
    matrix1.m = matrix2.m = expected_matrix.m = result_matrix.m = N3;

    allocate_matrix(&matrix1);
    allocate_matrix(&matrix2);
    allocate_matrix(&expected_matrix);
    allocate_matrix(&result_matrix);

    double mtr1[N3][N3] = {{10.5, 4.0, 6.2}, {1.0, 2.5, 7.1}, {3.3, 5.7, 9.0}};
    for (int i = 0; i < N3; i++)
        for (int j = 0; j < N3; j++)
            matrix1.data[i][j] = mtr1[i][j];

    double mtr2[N3][N3] = {{2.5, 1.0, 8.0}, {3.0, 3.5, 2.1}, {4.7, 2.3, 6.0}};
    for (int i = 0; i < N3; i++)
        for (int j = 0; j < N3; j++)
            matrix2.data[i][j] = mtr2[i][j];

    double mtr3[N3][N3] = {{13.0, 5.0, 14.2}, {4.0, 6.0, 9.2}, {8.0, 8.0, 15.0}};
    for (int i = 0; i < N3; i++)
        for (int j = 0; j < N3; j++)
            expected_matrix.data[i][j] = mtr3[i][j];

    matrix_addition(&result_matrix, &matrix1, &matrix2);

    ck_assert_int_eq(cmp_matrix(expected_matrix.data, result_matrix.data, N3, N3), 1);

    free_matrix(matrix1.data);
    free_matrix(matrix2.data);
    free_matrix(expected_matrix.data);
    free_matrix(result_matrix.data);
}
END_TEST

START_TEST(matrix_has_negatives)
{
    matrix_t matrix1 = {0}, matrix2 = {0}, expected_matrix = {0}, result_matrix = {0};

    matrix1.n = matrix2.n = expected_matrix.n = result_matrix.n = N3;
    matrix1.m = matrix2.m = expected_matrix.m = result_matrix.m = N3;

    allocate_matrix(&matrix1);
    allocate_matrix(&matrix2);
    allocate_matrix(&expected_matrix);
    allocate_matrix(&result_matrix);

    double mtr1[N3][N3] = {{-5.0, 2.5, -8.0}, {4.0, -1.0, -2.5}, {-3.3, -7.5, 6.0}};
    for (int i = 0; i < N3; i++)
        for (int j = 0; j < N3; j++)
            matrix1.data[i][j] = mtr1[i][j];

    double mtr2[N3][N3] = {{1.0, -3.5, -2.0}, {-4.0, 2.0, -1.5}, {3.0, -2.5, -6.0}};
    for (int i = 0; i < N3; i++)
        for (int j = 0; j < N3; j++)
            matrix2.data[i][j] = mtr2[i][j];

    double mtr3[N3][N3] = {{-4.0, -1.0, -10.0}, {0.0, 1.0, -4.0}, {-0.3, -10.0, 0.0}};
    for (int i = 0; i < N3; i++)
        for (int j = 0; j < N3; j++)
            expected_matrix.data[i][j] = mtr3[i][j];

    matrix_addition(&result_matrix, &matrix1, &matrix2);

    ck_assert_int_eq(cmp_matrix(expected_matrix.data, result_matrix.data, N3, N3), 1);

    free_matrix(matrix1.data);
    free_matrix(matrix2.data);
    free_matrix(expected_matrix.data);
    free_matrix(result_matrix.data);
}
END_TEST

START_TEST(matrix_size_eq_1)
{
    matrix_t matrix1 = {0}, matrix2 = {0}, expected_matrix = {0}, result_matrix = {0};

    matrix1.n = matrix2.n = expected_matrix.n = result_matrix.n = N1;
    matrix1.m = matrix2.m = expected_matrix.m = result_matrix.m = N1;

    allocate_matrix(&matrix1);
    allocate_matrix(&matrix2);
    allocate_matrix(&expected_matrix);
    allocate_matrix(&result_matrix);

    double mtr1[N1][N1] = {{-5.75}};
    for (int i = 0; i < N1; i++)
        for (int j = 0; j < N1; j++)
            matrix1.data[i][j] = mtr1[i][j];

    double mtr2[N1][N1] = {{3.25}};
    for (int i = 0; i < N1; i++)
        for (int j = 0; j < N1; j++)
            matrix2.data[i][j] = mtr2[i][j];

    double mtr3[N1][N1] = {{-2.5}};
    for (int i = 0; i < N1; i++)
        for (int j = 0; j < N1; j++)
            expected_matrix.data[i][j] = mtr3[i][j];

    matrix_addition(&result_matrix, &matrix1, &matrix2);

    ck_assert_int_eq(cmp_matrix(expected_matrix.data, result_matrix.data, N1, N1), 1);

    free_matrix(matrix1.data);
    free_matrix(matrix2.data);
    free_matrix(expected_matrix.data);
    free_matrix(result_matrix.data);
}
END_TEST

START_TEST(matrix_rectangle)
{
    matrix_t matrix1 = {0}, matrix2 = {0}, expected_matrix = {0}, result_matrix = {0};

    matrix1.n = matrix2.n = expected_matrix.n = result_matrix.n = N3;
    matrix1.m = matrix2.m = expected_matrix.m = result_matrix.m = N4;

    allocate_matrix(&matrix1);
    allocate_matrix(&matrix2);
    allocate_matrix(&expected_matrix);
    allocate_matrix(&result_matrix);

    double mtr1[N3][N4] = {
            {-4.0, 2.5, -8.0, 3.0},
            {1.5, -2.0, 0.0, -1.2},
            {2.3, 4.0, 5.5, -3.1}};
    for (int i = 0; i < N3; i++)
        for (int j = 0; j < N4; j++)
            matrix1.data[i][j] = mtr1[i][j];

    double mtr2[N3][N4] = {
            {1.0, -3.5, 2.0, -0.5},
            {-1.5, 3.0, -0.5, 2.0},
            {3.7, -1.5, 4.5, 1.1}};
    for (int i = 0; i < N3; i++)
        for (int j = 0; j < N4; j++)
            matrix2.data[i][j] = mtr2[i][j];

    double mtr3[N3][N4] = {
            {-3.0, -1.0, -6.0, 2.5},
            {0.0, 1.0, -0.5, 0.8},
            {6.0, 2.5, 10.0, -2.0}};
    for (int i = 0; i < N3; i++)
        for (int j = 0; j < N4; j++)
            expected_matrix.data[i][j] = mtr3[i][j];

    matrix_addition(&result_matrix, &matrix1, &matrix2);

    ck_assert_int_eq(cmp_matrix(expected_matrix.data, result_matrix.data, N3, N4), 1);

    free_matrix(matrix1.data);
    free_matrix(matrix2.data);
    free_matrix(expected_matrix.data);
    free_matrix(result_matrix.data);
}
END_TEST

Suite *add_suite(void)
{
    Suite *s;
    TCase *tc_matrix_add_positive;

    s = suite_create("matrix_add_tests");

    tc_matrix_add_positive = tcase_create("add_positives");
    tcase_add_test(tc_matrix_add_positive, matrix_non_negatives);
    tcase_add_test(tc_matrix_add_positive, matrix_has_negatives);
    tcase_add_test(tc_matrix_add_positive, matrix_size_eq_1);
    tcase_add_test(tc_matrix_add_positive, matrix_rectangle);

    suite_add_tcase(s, tc_matrix_add_positive);

    return s;
}
