#include <check.h>
#include <limits.h>

#include "associative_array.h"
#include "check_insert.h"

START_TEST(test_insert_one_item)
{
    assoc_array_t arr = assoc_array_create();
    int res = assoc_array_insert(arr, "abc", 8);

    ck_assert_int_eq(res, ASSOC_ARRAY_OK);
    assoc_array_destroy(&arr);
}
END_TEST

START_TEST(test_insert_multiple_items)
{
    assoc_array_t arr = assoc_array_create();

    ck_assert_int_eq(assoc_array_insert(arr, "key1", 1), ASSOC_ARRAY_OK);
    ck_assert_int_eq(assoc_array_insert(arr, "key2", 2), ASSOC_ARRAY_OK);
    ck_assert_int_eq(assoc_array_insert(arr, "key3", 3), ASSOC_ARRAY_OK);

    assoc_array_destroy(&arr);
}
END_TEST

START_TEST(test_insert_large_value)
{
    assoc_array_t arr = assoc_array_create();
    int res = assoc_array_insert(arr, "large_key", INT_MAX);

    ck_assert_int_eq(res, ASSOC_ARRAY_OK);
    assoc_array_destroy(&arr);
}
END_TEST

START_TEST(test_insert_null_array)
{
    int res = assoc_array_insert(NULL, "abc", 8);
    ck_assert_int_eq(res, ASSOC_ARRAY_INVALID_PARAM);
}
END_TEST

START_TEST(test_insert_empty_key)
{
    assoc_array_t arr = assoc_array_create();
    int res = assoc_array_insert(arr, "", 8);

    ck_assert_int_eq(res, ASSOC_ARRAY_INVALID_PARAM);
    assoc_array_destroy(&arr);
}
END_TEST

START_TEST(test_insert_duplicate_key)
{
    assoc_array_t arr = assoc_array_create();
    ck_assert_int_eq(assoc_array_insert(arr, "key1", 1), ASSOC_ARRAY_OK);

    int res = assoc_array_insert(arr, "key1", 2);
    ck_assert_int_eq(res, ASSOC_ARRAY_KEY_EXISTS);

    assoc_array_destroy(&arr);
}
END_TEST

START_TEST(test_insert_null_key)
{
    assoc_array_t arr = assoc_array_create();
    int res = assoc_array_insert(arr, NULL, 8);

    ck_assert_int_eq(res, ASSOC_ARRAY_INVALID_PARAM);
    assoc_array_destroy(&arr);
}
END_TEST

Suite *assoc_array_insert_suite(void)
{
    Suite *s;
    TCase *tc_positive, *tc_negative;

    s = suite_create("Assoc array insert");

    tc_positive = tcase_create("Positive");
    tcase_add_test(tc_positive, test_insert_one_item);
    tcase_add_test(tc_positive, test_insert_large_value);
    tcase_add_test(tc_positive, test_insert_multiple_items);
    suite_add_tcase(s, tc_positive);

    tc_negative = tcase_create("Negative");
    tcase_add_test(tc_negative, test_insert_null_array);
    tcase_add_test(tc_negative, test_insert_empty_key);
    tcase_add_test(tc_negative, test_insert_duplicate_key);
    tcase_add_test(tc_negative, test_insert_null_key);
    suite_add_tcase(s, tc_negative);

    return s;
}
