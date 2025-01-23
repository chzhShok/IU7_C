#include <check.h>

#include "associative_array.h"
#include "check_remove.h"

START_TEST(test_remove_existing_key)
{
    assoc_array_t arr = assoc_array_create();
    assoc_array_insert(arr, "key1", 10);

    int res = assoc_array_remove(arr, "key1");

    ck_assert_int_eq(res, ASSOC_ARRAY_OK);

    int *value = NULL;
    res = assoc_array_find(arr, "key1", &value);
    ck_assert_int_eq(res, ASSOC_ARRAY_NOT_FOUND);

    assoc_array_destroy(&arr);
}
END_TEST

START_TEST(test_remove_multiple_keys)
{
    assoc_array_t arr = assoc_array_create();
    assoc_array_insert(arr, "key1", 10);
    assoc_array_insert(arr, "key2", 20);
    assoc_array_insert(arr, "key3", 30);

    ck_assert_int_eq(assoc_array_remove(arr, "key2"), ASSOC_ARRAY_OK);

    int *value = NULL;
    ck_assert_int_eq(assoc_array_find(arr, "key2", &value), ASSOC_ARRAY_NOT_FOUND);

    ck_assert_int_eq(assoc_array_remove(arr, "key1"), ASSOC_ARRAY_OK);
    ck_assert_int_eq(assoc_array_find(arr, "key1", &value), ASSOC_ARRAY_NOT_FOUND);

    ck_assert_int_eq(assoc_array_remove(arr, "key3"), ASSOC_ARRAY_OK);
    ck_assert_int_eq(assoc_array_find(arr, "key3", &value), ASSOC_ARRAY_NOT_FOUND);

    assoc_array_destroy(&arr);
}
END_TEST

START_TEST(test_remove_null_array)
{
    int res = assoc_array_remove(NULL, "key1");
    ck_assert_int_eq(res, ASSOC_ARRAY_INVALID_PARAM);
}
END_TEST

START_TEST(test_remove_empty_key)
{
    assoc_array_t arr = assoc_array_create();
    int res = assoc_array_remove(arr, "");

    ck_assert_int_eq(res, ASSOC_ARRAY_INVALID_PARAM);

    assoc_array_destroy(&arr);
}
END_TEST

START_TEST(test_remove_null_key)
{
    assoc_array_t arr = assoc_array_create();
    int res = assoc_array_remove(arr, NULL);

    ck_assert_int_eq(res, ASSOC_ARRAY_INVALID_PARAM);

    assoc_array_destroy(&arr);
}
END_TEST

START_TEST(test_remove_key_not_found)
{
    assoc_array_t arr = assoc_array_create();
    assoc_array_insert(arr, "key1", 10);

    int res = assoc_array_remove(arr, "key2");

    ck_assert_int_eq(res, ASSOC_ARRAY_NOT_FOUND);

    assoc_array_destroy(&arr);
}
END_TEST

Suite *assoc_array_remove_suite(void)
{
    Suite *s;
    TCase *tc_positive, *tc_negative;

    s = suite_create("Assoc array remove");

    tc_positive = tcase_create("Positive");
    tcase_add_test(tc_positive, test_remove_existing_key);
    tcase_add_test(tc_positive, test_remove_multiple_keys);
    suite_add_tcase(s, tc_positive);

    tc_negative = tcase_create("Negative");
    tcase_add_test(tc_negative, test_remove_null_array);
    tcase_add_test(tc_negative, test_remove_empty_key);
    tcase_add_test(tc_negative, test_remove_null_key);
    tcase_add_test(tc_negative, test_remove_key_not_found);
    suite_add_tcase(s, tc_negative);

    return s;
}
