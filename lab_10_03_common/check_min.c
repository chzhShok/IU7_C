#include <check.h>

#include "associative_array.h"
#include "check_min.h"

START_TEST(test_min_one_item)
{
    assoc_array_t arr = assoc_array_create();
    int res = assoc_array_insert(arr, "apple", 12);
    ck_assert_int_eq(res, ASSOC_ARRAY_OK);

    int *num;
    res = assoc_array_min(arr, &num);
    ck_assert_int_eq(res, ASSOC_ARRAY_OK);
    ck_assert_int_eq(*num, 12);

    assoc_array_destroy(&arr);
}
END_TEST

START_TEST(test_min_three_items)
{
    assoc_array_t arr = assoc_array_create();
    int res = assoc_array_insert(arr, "orange", 3);
    ck_assert_int_eq(res, ASSOC_ARRAY_OK);

    res = assoc_array_insert(arr, "banana", -5);
    ck_assert_int_eq(res, ASSOC_ARRAY_OK);

    res = assoc_array_insert(arr, "grape", 10);
    ck_assert_int_eq(res, ASSOC_ARRAY_OK);

    int *num;
    res = assoc_array_min(arr, &num);
    ck_assert_int_eq(res, ASSOC_ARRAY_OK);
    ck_assert_int_eq(*num, -5);

    assoc_array_destroy(&arr);
}
END_TEST

START_TEST(test_min_equal_items)
{
    assoc_array_t arr = assoc_array_create();
    int res = assoc_array_insert(arr, "mango", 15);
    ck_assert_int_eq(res, ASSOC_ARRAY_OK);

    res = assoc_array_insert(arr, "pear", 15);
    ck_assert_int_eq(res, ASSOC_ARRAY_OK);

    res = assoc_array_insert(arr, "peach", 15);
    ck_assert_int_eq(res, ASSOC_ARRAY_OK);

    int *num;
    res = assoc_array_min(arr, &num);
    ck_assert_int_eq(res, ASSOC_ARRAY_OK);
    ck_assert_int_eq(*num, 15);

    assoc_array_destroy(&arr);
}
END_TEST


START_TEST(test_min_null_arr)
{
    assoc_array_t arr = NULL;
    int *num;
    int res = assoc_array_min(arr, &num);
    ck_assert_int_eq(res, ASSOC_ARRAY_INVALID_PARAM);
}
END_TEST

START_TEST(test_min_empty_arr)
{
    assoc_array_t arr = assoc_array_create();
    int *num;
    int res = assoc_array_min(arr, &num);
    ck_assert_int_eq(res, ASSOC_ARRAY_NOT_FOUND);

    assoc_array_destroy(&arr);
}
END_TEST

START_TEST(test_min_null_num)
{
    assoc_array_t arr = assoc_array_create();
    int res = assoc_array_insert(arr, "kiwi", 7);
    ck_assert_int_eq(res, ASSOC_ARRAY_OK);

    res = assoc_array_insert(arr, "lemon", 4);
    ck_assert_int_eq(res, ASSOC_ARRAY_OK);

    res = assoc_array_insert(arr, "lime", 2);
    ck_assert_int_eq(res, ASSOC_ARRAY_OK);

    res = assoc_array_min(arr, NULL);
    ck_assert_int_eq(res, ASSOC_ARRAY_INVALID_PARAM);

    assoc_array_destroy(&arr);
}
END_TEST

Suite *assoc_array_min_suite(void)
{
    Suite *s;
    TCase *tc_positive, *tc_negative;

    s = suite_create("Assoc array min");

    tc_positive = tcase_create("Positive");
    tcase_add_test(tc_positive, test_min_one_item);
    tcase_add_test(tc_positive, test_min_three_items);
    tcase_add_test(tc_positive, test_min_equal_items);
    suite_add_tcase(s, tc_positive);

    tc_negative = tcase_create("Negative");
    tcase_add_test(tc_negative, test_min_null_arr);
    tcase_add_test(tc_negative, test_min_empty_arr);
    tcase_add_test(tc_negative, test_min_null_num);
    suite_add_tcase(s, tc_negative);

    return s;
}
