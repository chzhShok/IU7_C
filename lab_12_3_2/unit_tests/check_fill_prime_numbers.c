#include <check.h>

#include "mylib.h"

START_TEST(test_fill_prime_numbers)
{
    int n = 5;
    int arr[5];

    int rc = fill_prime_numbers(arr, n);

    ck_assert_int_eq(rc, SUCCESS);

    int expected[] = {2, 3, 5, 7, 11};

    for (int i = 0; i < n; i++)
        ck_assert_int_eq(arr[i], expected[i]);
}
END_TEST

START_TEST(test_fill_prime_numbers_zero_elements)
{
    int n = 0;
    int arr[1];

    int rc = fill_prime_numbers(arr, n);

    ck_assert_int_eq(rc, FAIL);
}
END_TEST

START_TEST(test_fill_prime_numbers_large_n)
{
    int n = 10;
    int arr[10];

    int rc = fill_prime_numbers(arr, n);

    ck_assert_int_eq(rc, SUCCESS);

    int expected[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29};

    for (int i = 0; i < n; i++)
        ck_assert_int_eq(arr[i], expected[i]);
}
END_TEST

START_TEST(test_fill_prime_numbers_negative_n)
{
    int n = -1;
    int arr[1];

    int rc = fill_prime_numbers(arr, n);

    ck_assert_int_eq(rc, FAIL);
}
END_TEST

Suite* prime_suite(void)
{
    Suite *s = suite_create("Prime Numbers Suite");
    TCase *tc = tcase_create("Test");

    tcase_add_test(tc, test_fill_prime_numbers);
    tcase_add_test(tc, test_fill_prime_numbers_zero_elements);
    tcase_add_test(tc, test_fill_prime_numbers_large_n);
    tcase_add_test(tc, test_fill_prime_numbers_negative_n);

    suite_add_tcase(s, tc);

    return s;
}
