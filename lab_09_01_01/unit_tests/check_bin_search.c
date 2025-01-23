#include <check.h>

#include "array_funcs.h"
#include "errors.h"

START_TEST(test_bin_search_title_found)
{
    movie_t movies[] = {
            {"A Movie", "Director A", 2000},
            {"B Movie", "Director B", 2005},
            {"C Movie", "Director C", 2010}};

    int index = bin_search_title(movies, 3, "B Movie");
    ck_assert_int_eq(index, 1);
}
END_TEST

START_TEST(test_bin_search_title_not_found)
{
    movie_t movies[] = {
            {"A Movie", "Director A", 2000},
            {"B Movie", "Director B", 2005},
            {"C Movie", "Director C", 2010}};

    int index = bin_search_title(movies, 3, "D Movie");
    ck_assert_int_eq(index, -1);
}
END_TEST

START_TEST(test_bin_search_name_found)
{
    movie_t movies[] = {
            {"A Movie", "Director A", 2000},
            {"B Movie", "Director B", 2005},
            {"C Movie", "Director C", 2010}};

    int index = bin_search_name(movies, 3, "Director C");
    ck_assert_int_eq(index, 2);
}
END_TEST

START_TEST(test_bin_search_year_found)
{
    movie_t movies[] = {
            {"A Movie", "Director A", 2000},
            {"B Movie", "Director B", 2005},
            {"C Movie", "Director C", 2010}};

    int index = bin_search_year(movies, 3, 2005);
    ck_assert_int_eq(index, 1);
}
END_TEST

START_TEST(test_bin_search_year_not_found)
{
    movie_t movies[] = {
            {"A Movie", "Director A", 2000},
            {"B Movie", "Director B", 2005},
            {"C Movie", "Director C", 2010}};

    int index = bin_search_year(movies, 3, 2020);
    ck_assert_int_eq(index, -1);
}
END_TEST

START_TEST(test_bin_search_by_key_title)
{
    movie_t movies[] = {
            {"A Movie", "Director A", 2000},
            {"B Movie", "Director B", 2005},
            {"C Movie", "Director C", 2010}};

    int index;
    int rc = bin_search_by_key(movies, 3, "B Movie", "title", &index);
    ck_assert_int_eq(rc, OK);
    ck_assert_int_eq(index, 1);
}
END_TEST

START_TEST(test_bin_search_by_key_year_invalid)
{
    movie_t movies[] = {
            {"A Movie", "Director A", 2000},
            {"B Movie", "Director B", 2005},
            {"C Movie", "Director C", 2010}};

    int index;
    int rc = bin_search_by_key(movies, 3, "invalid", "year", &index);
    ck_assert_int_eq(rc, IO_ERROR);
}
END_TEST

Suite *binary_search_suite(void)
{
    Suite *s;
    TCase *tc_bin_search;

    s = suite_create("binary_search");

    tc_bin_search = tcase_create("bin_search_positives");
    tcase_add_test(tc_bin_search, test_bin_search_title_found);
    tcase_add_test(tc_bin_search, test_bin_search_title_not_found);
    tcase_add_test(tc_bin_search, test_bin_search_name_found);
    tcase_add_test(tc_bin_search, test_bin_search_year_found);
    tcase_add_test(tc_bin_search, test_bin_search_year_not_found);
    tcase_add_test(tc_bin_search, test_bin_search_by_key_title);
    tcase_add_test(tc_bin_search, test_bin_search_by_key_year_invalid);

    suite_add_tcase(s, tc_bin_search);

    return s;
}
