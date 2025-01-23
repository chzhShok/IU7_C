#include <check.h>
#include <limits.h>
#include <stdio.h>

#include "check_main.h"
#include "my_snprintf.h"

#define BUFFER 100

START_TEST(test_snprintf_basic)
{
    char buf1[BUFFER];
    char buf2[BUFFER];
    int res1, res2;

    res1 = my_snprintf(buf1, sizeof(buf1), "%c", 'a');
    res2 = snprintf(buf2, sizeof(buf2), "%c", 'a');
    ck_assert_int_eq(res1, res2);
    ck_assert_str_eq(buf1, buf2);

    res1 = my_snprintf(buf1, sizeof(buf1), "%s", "hello");
    res2 = snprintf(buf2, sizeof(buf2), "%s", "hello");
    ck_assert_int_eq(res1, res2);
    ck_assert_str_eq(buf1, buf2);

    res1 = my_snprintf(buf1, sizeof(buf1), "%d", 123);
    res2 = snprintf(buf2, sizeof(buf2), "%d", 123);
    ck_assert_int_eq(res1, res2);
    ck_assert_str_eq(buf1, buf2);

    res1 = my_snprintf(buf1, sizeof(buf1), "%ld", 123456789L);
    res2 = snprintf(buf2, sizeof(buf2), "%ld", 123456789L);
    ck_assert_int_eq(res1, res2);
    ck_assert_str_eq(buf1, buf2);

    res1 = my_snprintf(buf1, sizeof(buf1), "%hd", (short) 42);
    res2 = snprintf(buf2, sizeof(buf2), "%hd", (short) 42);
    ck_assert_int_eq(res1, res2);
    ck_assert_str_eq(buf1, buf2);
}
END_TEST

START_TEST(test_snprintf_edge_cases)
{
    char buf1[BUFFER] = "";
    char buf2[BUFFER] = "";
    int res1, res2;

    char s[11] = "hello world";
    res1 = my_snprintf(buf1, 5, "%s", s);
    res2 = snprintf(buf2, 5, "%s", s);
    ck_assert_int_eq(res1, res2);
    ck_assert_str_eq(buf1, buf2);

    res1 = my_snprintf(NULL, 0, "%d", 123);
    res2 = snprintf(NULL, 0, "%d", 123);
    ck_assert_int_eq(res1, res2);

    res1 = my_snprintf(buf1, 100, "%ld", LONG_MAX);
    res2 = snprintf(buf2, 100, "%ld", LONG_MAX);
    ck_assert_int_eq(res1, res2);
    ck_assert_str_eq(buf1, buf2);

    res1 = my_snprintf(buf1, 100, "%ld", LONG_MIN);
    res2 = snprintf(buf2, 100, "%ld", LONG_MIN);
    ck_assert_int_eq(res1, res2);
    ck_assert_str_eq(buf1, buf2);
}
END_TEST

START_TEST(test_snprintf_complex)
{
    char buf1[BUFFER];
    char buf2[BUFFER];
    int res1, res2;

    res1 = my_snprintf(buf1, sizeof(buf1), "%c %s %d %ld %hd", 'x', "check", 456, 987654321L, (short) -123);
    res2 = snprintf(buf2, sizeof(buf2), "%c %s %d %ld %hd", 'x', "check", 456, 987654321L, (short) -123);
    ck_assert_int_eq(res1, res2);
    ck_assert_str_eq(buf1, buf2);

    res1 = my_snprintf(buf1, sizeof(buf1), "%d %ld %hd", -123, -987654321L, (short) -42);
    res2 = snprintf(buf2, sizeof(buf2), "%d %ld %hd", -123, -987654321L, (short) -42);
    ck_assert_int_eq(res1, res2);
    ck_assert_str_eq(buf1, buf2);

    char s[9] = "truncate";
    res1 = my_snprintf(buf1, 1, "%s", s);
    res2 = snprintf(buf2, 1, "%s", s);
    ck_assert_int_eq(res1, res2);
    ck_assert_str_eq(buf1, buf2);

    res1 = my_snprintf(buf1, sizeof(buf1), "Hello, world!");
    res2 = snprintf(buf2, sizeof(buf2), "Hello, world!");
    ck_assert_int_eq(res1, res2);
    ck_assert_str_eq(buf1, buf2);
}
END_TEST

START_TEST(test_snprintf_large_inputs)
{
    char buf1[1000];
    char buf2[1000];
    int res1, res2;

    const char *long_str = "This is a very long string used to test the snprintf implementation for correctness.";
    res1 = my_snprintf(buf1, sizeof(buf1), "%s", long_str);
    res2 = snprintf(buf2, sizeof(buf2), "%s", long_str);
    ck_assert_int_eq(res1, res2);
    ck_assert_str_eq(buf1, buf2);

    res1 = my_snprintf(buf1, sizeof(buf1), "%ld", LONG_MAX);
    res2 = snprintf(buf2, sizeof(buf2), "%ld", LONG_MAX);
    ck_assert_int_eq(res1, res2);
    ck_assert_str_eq(buf1, buf2);
}
END_TEST

Suite *snprintf_suite(void)
{
    Suite *s;
    TCase *tc;

    s = suite_create("my_snprintf");

    tc = tcase_create("Tests");
    tcase_add_test(tc, test_snprintf_basic);
    tcase_add_test(tc, test_snprintf_edge_cases);
    tcase_add_test(tc, test_snprintf_complex);
    tcase_add_test(tc, test_snprintf_large_inputs);
    suite_add_tcase(s, tc);

    return s;
}
