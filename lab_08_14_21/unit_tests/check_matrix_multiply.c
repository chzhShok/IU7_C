#include <check.h>
#include <stdio.h>
#include <stdlib.h>

#include "check_main.h"
#include "errors.h"
#include "matrix.h"

START_TEST(matrix_result_square)
{
    matrix_t matrix1 = {.n = 3, .m = 4};
    matrix_t matrix2 = {.n = 4, .m = 3};
    matrix_t result_matrix = {.n = 3, .m = 3};
    matrix_t expected_matrix = {.n = 3, .m = 3};

    ck_assert_int_eq(allocate_matrix(&matrix1), OK);
    ck_assert_int_eq(allocate_matrix(&matrix2), OK);
    ck_assert_int_eq(allocate_matrix(&result_matrix), OK);
    ck_assert_int_eq(allocate_matrix(&expected_matrix), OK);

    double mtr1[N3][N4] = {
            {1.0, -2.0, 3.0, 0.0},
            {4.0, 0.0, 1.0, -1.0},
            {2.0, 1.0, -1.0, 3.0}};
    for (int i = 0; i < N3; i++)
        for (int j = 0; j < N4; j++)
            matrix1.data[i][j] = mtr1[i][j];

    double mtr2[N4][N3] = {
            {1.0, 2.0, 0.0},
            {0.0, -1.0, 3.0},
            {2.0, 1.0, 4.0},
            {1.0, 0.0, -2.0}};
    for (int i = 0; i < N4; i++)
        for (int j = 0; j < N3; j++)
            matrix2.data[i][j] = mtr2[i][j];

    double mtr3[N3][N3] = {
            {7.0, 7.0, 6.0},
            {5.0, 9.0, 6.0},
            {3.0, 2.0, -7.0}};
    for (int i = 0; i < N3; i++)
        for (int j = 0; j < N3; j++)
            expected_matrix.data[i][j] = mtr3[i][j];

    matrix_multiplication(&result_matrix, &matrix1, &matrix2);

    ck_assert_int_eq(cmp_matrix(expected_matrix.data, result_matrix.data, N3, N3), 1);

    free_matrix(matrix1.data);
    free_matrix(matrix2.data);
    free_matrix(result_matrix.data);
    free_matrix(expected_matrix.data);
}
END_TEST

START_TEST(matrix_result_rectangle)
{
    matrix_t matrix1 = {.n = 3, .m = 4};
    matrix_t matrix2 = {.n = 4, .m = 1};
    matrix_t result_matrix = {.n = 3, .m = 1};
    matrix_t expected_matrix = {.n = 3, .m = 1};

    ck_assert_int_eq(allocate_matrix(&matrix1), OK);
    ck_assert_int_eq(allocate_matrix(&matrix2), OK);
    ck_assert_int_eq(allocate_matrix(&result_matrix), OK);
    ck_assert_int_eq(allocate_matrix(&expected_matrix), OK);

    double mtr1[N3][N4] = {
            {2.0, -1.0, 3.0, 1.0},
            {4.0, 0.0, 1.0, -2.0},
            {1.0, 2.0, -1.0, 4.0}};
    for (int i = 0; i < N3; i++)
        for (int j = 0; j < N4; j++)
            matrix1.data[i][j] = mtr1[i][j];

    double mtr2[N4][N1] = {{1.0}, {0.0}, {2.0}, {3.0}};
    for (int i = 0; i < N4; i++)
        for (int j = 0; j < N1; j++)
            matrix2.data[i][j] = mtr2[i][j];

    double mtr3[N3][N1] = {{11.0}, {0.0}, {11.0}};
    for (int i = 0; i < N3; i++)
        for (int j = 0; j < N1; j++)
            expected_matrix.data[i][j] = mtr3[i][j];

    matrix_multiplication(&result_matrix, &matrix1, &matrix2);

    ck_assert_int_eq(cmp_matrix(expected_matrix.data, result_matrix.data, N3, N1), 1);

    free_matrix(matrix1.data);
    free_matrix(matrix2.data);
    free_matrix(result_matrix.data);
    free_matrix(expected_matrix.data);
}
END_TEST

START_TEST(matrix_squares)
{
    matrix_t matrix1 = {.n = 2, .m = 2};
    matrix_t matrix2 = {.n = 2, .m = 2};
    matrix_t result_matrix = {.n = 2, .m = 2};
    matrix_t expected_matrix = {.n = 2, .m = 2};

    ck_assert_int_eq(allocate_matrix(&matrix1), OK);
    ck_assert_int_eq(allocate_matrix(&matrix2), OK);
    ck_assert_int_eq(allocate_matrix(&result_matrix), OK);
    ck_assert_int_eq(allocate_matrix(&expected_matrix), OK);

    double mtr1[N2][N2] = {{1.0, -2.0}, {3.0, 4.0}};
    for (int i = 0; i < N2; i++)
        for (int j = 0; j < N2; j++)
            matrix1.data[i][j] = mtr1[i][j];

    double mtr2[N2][N2] = {{2.0, 1.0}, {-1.0, 3.0}};
    for (int i = 0; i < N2; i++)
        for (int j = 0; j < N2; j++)
            matrix2.data[i][j] = mtr2[i][j];

    double mtr3[N2][N2] = {{4.0, -5.0}, {2.0, 15.0}};
    for (int i = 0; i < N2; i++)
        for (int j = 0; j < N2; j++)
            expected_matrix.data[i][j] = mtr3[i][j];

    matrix_multiplication(&result_matrix, &matrix1, &matrix2);

    ck_assert_int_eq(cmp_matrix(expected_matrix.data, result_matrix.data, N2, N2), 1);

    free_matrix(matrix1.data);
    free_matrix(matrix2.data);
    free_matrix(result_matrix.data);
    free_matrix(expected_matrix.data);
}
END_TEST

START_TEST(matrix_result_size_one)
{
    matrix_t matrix1 = {.n = 1, .m = 3};
    matrix_t matrix2 = {.n = 3, .m = 1};
    matrix_t result_matrix = {.n = 1, .m = 1};
    matrix_t expected_matrix = {.n = 1, .m = 1};

    ck_assert_int_eq(allocate_matrix(&matrix1), OK);
    ck_assert_int_eq(allocate_matrix(&matrix2), OK);
    ck_assert_int_eq(allocate_matrix(&result_matrix), OK);
    ck_assert_int_eq(allocate_matrix(&expected_matrix), OK);

    double mtr1[N1][N3] = {{1.0, -2.0, 3.0}};
    for (int i = 0; i < N1; i++)
        for (int j = 0; j < N3; j++)
            matrix1.data[i][j] = mtr1[i][j];

    double mtr2[N3][N1] = {{2.0}, {-1.0}, {1.0}};
    for (int i = 0; i < N3; i++)
        for (int j = 0; j < N1; j++)
            matrix2.data[i][j] = mtr2[i][j];

    double mtr3[N1][N1] = {{7.0}};
    for (int i = 0; i < N1; i++)
        for (int j = 0; j < N1; j++)
            expected_matrix.data[i][j] = mtr3[i][j];

    matrix_multiplication(&result_matrix, &matrix1, &matrix2);

    ck_assert_int_eq(cmp_matrix(expected_matrix.data, result_matrix.data, N1, N1), 1);

    free_matrix(matrix1.data);
    free_matrix(matrix2.data);
    free_matrix(result_matrix.data);
    free_matrix(expected_matrix.data);
}
END_TEST

Suite *multiplication_suite(void)
{
    Suite *s;
    TCase *tc_matrix_multiplication_positive;

    s = suite_create("matrix_multiplication_tests");

    tc_matrix_multiplication_positive = tcase_create("multiply_positives");
    tcase_add_test(tc_matrix_multiplication_positive, matrix_result_square);
    tcase_add_test(tc_matrix_multiplication_positive, matrix_result_rectangle);
    tcase_add_test(tc_matrix_multiplication_positive, matrix_squares);
    tcase_add_test(tc_matrix_multiplication_positive, matrix_result_size_one);

    suite_add_tcase(s, tc_matrix_multiplication_positive);

    return s;
}
