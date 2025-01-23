#include <check.h>

#include "associative_array.h"
#include "check_find.h"

START_TEST(test_find_existing_key)
{
    assoc_array_t arr = assoc_array_create();
    assoc_array_insert(arr, "key1", 10);

    int *value = NULL;
    int res = assoc_array_find(arr, "key1", &value);

    ck_assert_int_eq(res, ASSOC_ARRAY_OK);
    ck_assert_ptr_nonnull(value);
    ck_assert_int_eq(*value, 10);

    assoc_array_destroy(&arr);
}
END_TEST

START_TEST(test_find_multiple_keys)
{
    assoc_array_t arr = assoc_array_create();
    assoc_array_insert(arr, "key1", 10);
    assoc_array_insert(arr, "key2", 20);
    assoc_array_insert(arr, "key3", 30);

    int *value = NULL;

    ck_assert_int_eq(assoc_array_find(arr, "key1", &value), ASSOC_ARRAY_OK);
    ck_assert_int_eq(*value, 10);

    ck_assert_int_eq(assoc_array_find(arr, "key2", &value), ASSOC_ARRAY_OK);
    ck_assert_int_eq(*value, 20);

    ck_assert_int_eq(assoc_array_find(arr, "key3", &value), ASSOC_ARRAY_OK);
    ck_assert_int_eq(*value, 30);

    assoc_array_destroy(&arr);
}
END_TEST

START_TEST(test_find_null_array)
{
    int *value = NULL;
    int res = assoc_array_find(NULL, "key1", &value);

    ck_assert_int_eq(res, ASSOC_ARRAY_INVALID_PARAM);
    ck_assert_ptr_null(value);
}
END_TEST

START_TEST(test_find_empty_key)
{
    assoc_array_t arr = assoc_array_create();
    int *value = NULL;
    int res = assoc_array_find(arr, "", &value);

    ck_assert_int_eq(res, ASSOC_ARRAY_INVALID_PARAM);
    ck_assert_ptr_null(value);

    assoc_array_destroy(&arr);
}
END_TEST

START_TEST(test_find_null_key)
{
    assoc_array_t arr = assoc_array_create();
    int *value = NULL;
    int res = assoc_array_find(arr, NULL, &value);

    ck_assert_int_eq(res, ASSOC_ARRAY_INVALID_PARAM);
    ck_assert_ptr_null(value);

    assoc_array_destroy(&arr);
}
END_TEST

START_TEST(test_find_key_not_found)
{
    assoc_array_t arr = assoc_array_create();
    assoc_array_insert(arr, "key1", 10);

    int *value = NULL;
    int res = assoc_array_find(arr, "key2", &value);

    ck_assert_int_eq(res, ASSOC_ARRAY_NOT_FOUND);
    ck_assert_ptr_null(value);

    assoc_array_destroy(&arr);
}
END_TEST

START_TEST(test_find_null_output_pointer)
{
    assoc_array_t arr = assoc_array_create();
    assoc_array_insert(arr, "key1", 10);

    int res = assoc_array_find(arr, "key1", NULL);

    ck_assert_int_eq(res, ASSOC_ARRAY_INVALID_PARAM);

    assoc_array_destroy(&arr);
}
END_TEST

Suite *assoc_array_find_suite(void)
{
    Suite *s;
    TCase *tc_positive, *tc_negative;

    s = suite_create("Assoc array find");

    tc_positive = tcase_create("Positive");
    tcase_add_test(tc_positive, test_find_existing_key);
    tcase_add_test(tc_positive, test_find_multiple_keys);
    suite_add_tcase(s, tc_positive);

    tc_negative = tcase_create("Negative");
    tcase_add_test(tc_negative, test_find_null_array);
    tcase_add_test(tc_negative, test_find_empty_key);
    tcase_add_test(tc_negative, test_find_null_key);
    tcase_add_test(tc_negative, test_find_key_not_found);
    tcase_add_test(tc_negative, test_find_null_output_pointer);
    suite_add_tcase(s, tc_negative);

    return s;
}
