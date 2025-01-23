#include <check.h>

#include "mylib.h"

START_TEST(test_insert_after_even_basic)
{
    int src[] = {1, 2, 3, 4, 5};
    int src_len = 5;
    int dst[10];

    int k = 99;

    int result_len = insert_after_even(src, src_len, dst, k);

    ck_assert_int_eq(result_len, 7);

    int expected[] = {1, 2, 99, 3, 4, 99, 5};

    for (int i = 0; i < result_len; i++)
        ck_assert_int_eq(dst[i], expected[i]);
}
END_TEST

START_TEST(test_insert_after_even_empty_array)
{
    int src[1] = {0};
    int src_len = 0;
    int dst[10];
    int k = 99;

    int result_len = insert_after_even(src, src_len, dst, k);

    ck_assert_int_eq(result_len, FAIL);
}
END_TEST

START_TEST(test_insert_after_even_no_even_numbers)
{
    int src[] = {1, 3, 5, 7};
    int src_len = 4;
    int dst[10];
    int k = 99;

    int result_len = insert_after_even(src, src_len, dst, k);

    ck_assert_int_eq(result_len, 4);

    for (int i = 0; i < result_len; i++)
        ck_assert_int_eq(dst[i], src[i]);
}
END_TEST

START_TEST(test_insert_after_even_negative_k)
{
    int src[] = {2, 4, 6};
    int src_len = 3;
    int dst[10];
    int k = -99;

    int result_len = insert_after_even(src, src_len, dst, k);

    ck_assert_int_eq(result_len, 6);

    int expected[] = {2, -99, 4, -99, 6, -99};

    for (int i = 0; i < result_len; i++)
        ck_assert_int_eq(dst[i], expected[i]);
}
END_TEST

START_TEST(test_insert_after_even_large_k)
{
    int src[] = {2, 3, 4};
    int src_len = 3;
    int dst[10];
    int k = 1000000;

    int result_len = insert_after_even(src, src_len, dst, k);

    ck_assert_int_eq(result_len, 5);

    int expected[] = {2, 1000000, 3, 4, 1000000};

    for (int i = 0; i < result_len; i++)
        ck_assert_int_eq(dst[i], expected[i]);
}
END_TEST

Suite* insert_after_even_suite(void)
{
    Suite *s = suite_create("Insert After Even Suite");
    TCase *tc = tcase_create("Test");

    tcase_add_test(tc, test_insert_after_even_basic);
    tcase_add_test(tc, test_insert_after_even_empty_array);
    tcase_add_test(tc, test_insert_after_even_no_even_numbers);
    tcase_add_test(tc, test_insert_after_even_negative_k);
    tcase_add_test(tc, test_insert_after_even_large_k);

    suite_add_tcase(s, tc);

    return s;
}
