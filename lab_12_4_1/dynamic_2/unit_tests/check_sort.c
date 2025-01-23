#include <check.h>
#include <stdlib.h>
#include <stdint.h>
#include <dlfcn.h>

#include "check_main.h"
#include "errors.h"

typedef void (*mysort_t)(void *first, size_t number, size_t size, int (*comparator)(const void *, const void *));
typedef int (*int_comparator_t)(const void *a, const void *b);
typedef int (*double_comparator_t)(const void *a, const void *b);

static mysort_t mysort;
static int_comparator_t int_comparator;
static double_comparator_t double_comparator;

static void load_library(const char *libname)
{
    void *lib = dlopen(libname, RTLD_LAZY);

    mysort = (mysort_t) (uintptr_t) dlsym(lib, "mysort");
    int_comparator = (int_comparator_t) (uintptr_t) dlsym(lib, "int_comparator");
    double_comparator = (double_comparator_t) (uintptr_t) dlsym(lib, "double_comparator");
}

START_TEST(test_sort_one_element_array)
{
    int arr[] = {1};
    int *p = arr;
    int number = 1;
    int size = sizeof(int);
    int res_arr[] = {1};

    mysort(p, number, size, int_comparator);
    for (int i = 0; i < number; i++)
        ck_assert_int_eq(arr[i], res_arr[i]);
}
END_TEST

START_TEST(test_sort_two_acs_element_array)
{
    int arr[] = {1, 2};
    int *p = arr;
    int number = 2;
    int size = sizeof(int);
    int res_arr[] = {1, 2};

    mysort(p, number, size, int_comparator);
    for (int i = 0; i < number; i++)
        ck_assert_int_eq(arr[i], res_arr[i]);
}
END_TEST

START_TEST(test_sort_two_desc_element_array)
{
    int arr[] = {2, 1};
    int *p = arr;
    int number = 2;
    int size = sizeof(int);
    int res_arr[] = {1, 2};

    mysort(p, number, size, int_comparator);
    for (int i = 0; i < number; i++)
        ck_assert_int_eq(arr[i], res_arr[i]);
}
END_TEST

START_TEST(test_sort_sorted_array)
{
    int arr[] = {1, 2, 3, 4, 5, 6, 7};
    int *p = arr;
    int number = 7;
    int size = sizeof(int);
    int res_arr[] = {1, 2, 3, 4, 5, 6, 7};

    mysort(p, number, size, int_comparator);
    for (int i = 0; i < number; i++)
        ck_assert_int_eq(arr[i], res_arr[i]);
}
END_TEST

START_TEST(test_sort_reversed_array)
{
    int arr[] = {7, 6, 5, 4, 3, 2, 1};
    int *p = arr;
    int number = 7;
    int size = sizeof(int);
    int res_arr[] = {1, 2, 3, 4, 5, 6, 7};

    mysort(p, number, size, int_comparator);
    for (int i = 0; i < number; i++)
        ck_assert_int_eq(arr[i], res_arr[i]);
}
END_TEST

START_TEST(test_sort_equal_elements_array)
{
    int arr[] = {1, 1, 1, 1, 1, 1, 1};
    int *p = arr;
    int number = 7;
    int size = sizeof(int);
    int res_arr[] = {1, 1, 1, 1, 1, 1, 1};

    mysort(p, number, size, int_comparator);
    for (int i = 0; i < number; i++)
        ck_assert_int_eq(arr[i], res_arr[i]);
}
END_TEST

START_TEST(test_sort_random_array)
{
    int arr[] = {4, 3, 6, 4, 1, 4, 3, 7, 8};
    int *p = arr;
    int number = 9;
    int size = sizeof(int);
    int res_arr[] = {1, 3, 3, 4, 4, 4, 6, 7, 8};

    mysort(p, number, size, int_comparator);
    for (int i = 0; i < number; i++)
        ck_assert_int_eq(arr[i], res_arr[i]);
}
END_TEST

START_TEST(test_negative_vals_array)
{
    int arr[] = {-1, 0, 5, 3, -2, -5, -10};
    int *p = arr;
    int number = 7;
    int size = sizeof(int);
    int res_arr[] = {-10, -5, -2, -1, 0, 3, 5};

    mysort(p, number, size, int_comparator);
    for (int i = 0; i < number; i++)
        ck_assert_int_eq(arr[i], res_arr[i]);
}
END_TEST

START_TEST(test_sort_double_array)
{
    double arr[] = {0.1, -1.45, 5.32, 0.11, -0.32};
    double *p = arr;
    int number = 5;
    int size = sizeof(double);
    double res_arr[] = {-1.45, -0.32, 0.1, 0.11, 5.32};

    mysort(p, number, size, double_comparator);
    for (int i = 0; i < number; i++)
        ck_assert_double_eq(arr[i], res_arr[i]);
}
END_TEST

Suite *sort_suite(void)
{
    Suite *s;
    TCase *tc_pos;

    s = suite_create("sort");

    load_library("./out/libarr.so");

    tc_pos = tcase_create("positives");
    tcase_add_test(tc_pos, test_sort_one_element_array);
    tcase_add_test(tc_pos, test_sort_two_acs_element_array);
    tcase_add_test(tc_pos, test_sort_two_desc_element_array);
    tcase_add_test(tc_pos, test_sort_sorted_array);
    tcase_add_test(tc_pos, test_sort_reversed_array);
    tcase_add_test(tc_pos, test_sort_equal_elements_array);
    tcase_add_test(tc_pos, test_sort_random_array);
    tcase_add_test(tc_pos, test_negative_vals_array);
    tcase_add_test(tc_pos, test_sort_double_array);
    suite_add_tcase(s, tc_pos);

    return s;
}
