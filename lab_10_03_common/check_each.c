#include <check.h>

#include "associative_array.h"
#include "check_each.h"

void increment_values(const char *key, int *num, void *param)
{
    (void) key;
    (void) param;

    if (num)
        (*num) += 1;
}

void increment_with_param(const char *key, int *num, void *param)
{
    (void) key;

    if (num && param)
        (*num) += *(int *) param;
}

START_TEST(test_each_increment_values)
{
    assoc_array_t arr = assoc_array_create();
    assoc_array_insert(arr, "key1", 1);
    assoc_array_insert(arr, "key2", 2);
    assoc_array_insert(arr, "key3", 3);

    int res = assoc_array_each(arr, increment_values, NULL);
    ck_assert_int_eq(res, ASSOC_ARRAY_OK);

    int *value = NULL;
    ck_assert_int_eq(assoc_array_find(arr, "key1", &value), ASSOC_ARRAY_OK);
    ck_assert_int_eq(*value, 2);
    ck_assert_int_eq(assoc_array_find(arr, "key2", &value), ASSOC_ARRAY_OK);
    ck_assert_int_eq(*value, 3);
    ck_assert_int_eq(assoc_array_find(arr, "key3", &value), ASSOC_ARRAY_OK);
    ck_assert_int_eq(*value, 4);

    assoc_array_destroy(&arr);
}
END_TEST

START_TEST(test_each_with_param)
{
    assoc_array_t arr = assoc_array_create();
    assoc_array_insert(arr, "key1", 1);
    assoc_array_insert(arr, "key2", 2);

    int increment_by = 5;

    int res = assoc_array_each(arr, increment_with_param, &increment_by);
    ck_assert_int_eq(res, ASSOC_ARRAY_OK);

    int *value = NULL;
    ck_assert_int_eq(assoc_array_find(arr, "key1", &value), ASSOC_ARRAY_OK);
    ck_assert_int_eq(*value, 6);
    ck_assert_int_eq(assoc_array_find(arr, "key2", &value), ASSOC_ARRAY_OK);
    ck_assert_int_eq(*value, 7);

    assoc_array_destroy(&arr);
}
END_TEST

START_TEST(test_each_null_array)
{
    int res = assoc_array_each(NULL, increment_values, NULL);
    ck_assert_int_eq(res, ASSOC_ARRAY_INVALID_PARAM);
}
END_TEST

START_TEST(test_each_null_action)
{
    assoc_array_t arr = assoc_array_create();
    assoc_array_insert(arr, "key1", 1);

    int res = assoc_array_each(arr, NULL, NULL);
    ck_assert_int_eq(res, ASSOC_ARRAY_INVALID_PARAM);

    assoc_array_destroy(&arr);
}
END_TEST

START_TEST(test_each_empty_array)
{
    assoc_array_t arr = assoc_array_create();

    int res = assoc_array_each(arr, increment_values, NULL);
    ck_assert_int_eq(res, ASSOC_ARRAY_OK);

    assoc_array_destroy(&arr);
}
END_TEST

Suite *assoc_array_each_suite(void)
{
    Suite *s;
    TCase *tc_positive, *tc_negative;

    s = suite_create("Assoc array each");

    tc_positive = tcase_create("Positive");
    tcase_add_test(tc_positive, test_each_increment_values);
    tcase_add_test(tc_positive, test_each_with_param);
    suite_add_tcase(s, tc_positive);

    tc_negative = tcase_create("Negative");
    tcase_add_test(tc_negative, test_each_null_array);
    tcase_add_test(tc_negative, test_each_null_action);
    tcase_add_test(tc_negative, test_each_empty_array);
    suite_add_tcase(s, tc_negative);

    return s;
}
