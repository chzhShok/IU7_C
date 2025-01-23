#include <check.h>
#include <stdlib.h>

#include "array.h"
#include "check_main.h"

START_TEST(test_key_null_src_pointers)
{
    int *pb = NULL;
    int *pe = NULL;
    int *pb_dst = NULL, *pe_dst = NULL;

    int rc = key(pb, pe, &pb_dst, &pe_dst);
    ck_assert_int_eq(rc, INCORRECT_PARAMETERS);
}
END_TEST

START_TEST(test_key_swapped_pointers)
{
    int arr[] = {1, 2, 3, 4, 5};
    int *pb = arr;
    int *pe = arr + 5;
    int *pb_dst = NULL, *pe_dst = NULL;

    int rc = key(pe, pb, &pb_dst, &pe_dst);
    ck_assert_int_eq(rc, INCORRECT_PARAMETERS);
}
END_TEST

START_TEST(test_key_one_element_array)
{
    int arr[1] = {1};
    int *pb = arr, *pe = arr + 1;
    int *pb_dst = NULL, *pe_dst = NULL;

    int rc = key(pb, pe, &pb_dst, &pe_dst);
    ck_assert_int_eq(rc, EMPTY_FILTERED_ARRAY);
}
END_TEST

START_TEST(test_key_null_dst_pointers)
{
    int arr[] = {1, 2, 3, 4, 5};
    int *pb = arr, *pe = arr + 5;

    int rc = key(pb, pe, NULL, NULL);
    ck_assert_int_eq(rc, INCORRECT_PARAMETERS);
}
END_TEST

START_TEST(test_key_all_elements_equal)
{
    int arr[] = {1, 1, 1, 1, 1};
    int *pb = arr, *pe = arr + 5;
    int *pb_dst = NULL, *pe_dst = NULL;

    int rc = key(pb, pe, &pb_dst, &pe_dst);
    ck_assert_int_eq(rc, EMPTY_FILTERED_ARRAY);
}
END_TEST

START_TEST(test_key_two_elements_array)
{
    int arr[] = {1, 2};
    int *pb = arr, *pe = arr + 2;
    int *pb_dst = NULL, *pe_dst = NULL;

    int rc = key(pb, pe, &pb_dst, &pe_dst);
    ck_assert_int_eq(rc, OK);
    ck_assert_int_eq(*pb_dst, 2);

    free(pb_dst);
}
END_TEST

START_TEST(test_key_reversed_array)
{
    int arr[] = {5, 4, 3, 2, 1};
    int *pb = arr, *pe = arr + 5;
    int *pb_dst = NULL, *pe_dst = NULL;

    int rc = key(pb, pe, &pb_dst, &pe_dst);
    ck_assert_int_eq(rc, OK);
    ck_assert_int_eq(*pb_dst, 5);
    pb_dst++;
    ck_assert_int_eq(*pb_dst, 4);

    pb_dst--;
    free(pb_dst);
}
END_TEST

START_TEST(test_key_sorted_array)
{
    int arr[] = {1, 2, 3, 4, 5};
    int *pb = arr, *pe = arr + 5;
    int *pb_dst = NULL, *pe_dst = NULL;

    int rc = key(pb, pe, &pb_dst, &pe_dst);
    ck_assert_int_eq(rc, OK);
    ck_assert_int_eq(*pb_dst, 4);
    pb_dst++;
    ck_assert_int_eq(*pb_dst, 5);

    pb_dst--;
    free(pb_dst);
}
END_TEST

START_TEST(test_key_random_array)
{
    int arr[] = {3, 2, 5, 4, 1};
    int *pb = arr, *pe = arr + 5;
    int *pb_dst = NULL, *pe_dst = NULL;

    int rc = key(pb, pe, &pb_dst, &pe_dst);
    ck_assert_int_eq(rc, OK);
    ck_assert_int_eq(*pb_dst, 5);
    pb_dst++;
    ck_assert_int_eq(*pb_dst, 4);

    pb_dst--;
    free(pb_dst);
}
END_TEST

START_TEST(test_one_element_bigger_than_others)
{
    int arr[] = {1, 1, 1, 1, 5};
    int *pb = arr, *pe = arr + 5;
    int *pb_dst = NULL, *pe_dst = NULL;

    int rc = key(pb, pe, &pb_dst, &pe_dst);
    ck_assert_int_eq(rc, OK);
    ck_assert_int_eq(*pb_dst, 5);

    free(pb_dst);
}
END_TEST

Suite *key_suite(void)
{
    Suite *s;
    TCase *tc_neg;
    TCase *tc_pos;

    s = suite_create("key");

    tc_neg = tcase_create("negatives");
    tcase_add_test(tc_neg, test_key_null_src_pointers);
    tcase_add_test(tc_neg, test_key_swapped_pointers);
    tcase_add_test(tc_neg, test_key_one_element_array);
    tcase_add_test(tc_neg, test_key_null_dst_pointers);
    tcase_add_test(tc_neg, test_key_all_elements_equal);
    suite_add_tcase(s, tc_neg);

    tc_pos = tcase_create("positives");
    tcase_add_test(tc_pos, test_key_two_elements_array);
    tcase_add_test(tc_pos, test_key_reversed_array);
    tcase_add_test(tc_pos, test_key_sorted_array);
    tcase_add_test(tc_pos, test_key_random_array);
    tcase_add_test(tc_pos, test_one_element_bigger_than_others);
    suite_add_tcase(s, tc_pos);

    return s;
}
