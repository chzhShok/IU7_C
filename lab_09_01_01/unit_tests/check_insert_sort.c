#include <check.h>
#include <stdlib.h>
#include <string.h>
#include "text_file_funcs.h"

movie_t create_movie(const char *title, const char *name, int year)
{
    movie_t movie;
    movie.title = malloc((strlen(title) + 1) * sizeof(char));
    movie.name = malloc((strlen(name) + 1) * sizeof(char));
    strcpy(movie.title, title);
    strcpy(movie.name, name);
    movie.year = year;
    return movie;
}

START_TEST(test_insert_sort_title)
{
    movie_t *movies = malloc(3 * sizeof(movie_t));
    size_t len = 2;

    movies[0] = create_movie("A Movie", "Director A", 2000);
    movies[1] = create_movie("C Movie", "Director C", 2010);

    movie_t new_movie = create_movie("B Movie", "Director B", 2005);

    insert_sort_title(movies, len, &new_movie);

    free(new_movie.title);
    free(new_movie.name);

    ck_assert_str_eq(movies[0].title, "A Movie");
    ck_assert_str_eq(movies[1].title, "B Movie");
    ck_assert_str_eq(movies[2].title, "C Movie");

    free_movies(movies, 3);
}
END_TEST

START_TEST(test_insert_sort_name)
{
    movie_t *movies = malloc(3 * sizeof(movie_t));
    size_t len = 2;

    movies[0] = create_movie("Movie A", "Director A", 2000);
    movies[1] = create_movie("Movie C", "Director C", 2010);

    movie_t new_movie = create_movie("Movie B", "Director B", 2005);

    insert_sort_name(movies, len, &new_movie);

    free(new_movie.title);
    free(new_movie.name);

    ck_assert_str_eq(movies[0].name, "Director A");
    ck_assert_str_eq(movies[1].name, "Director B");
    ck_assert_str_eq(movies[2].name, "Director C");

    free_movies(movies, 3);
}
END_TEST

START_TEST(test_insert_sort_year)
{
    movie_t *movies = malloc(3 * sizeof(movie_t));
    size_t len = 2;

    movies[0] = create_movie("Movie A", "Director A", 2000);
    movies[1] = create_movie("Movie C", "Director C", 2010);

    movie_t new_movie = create_movie("Movie B", "Director B", 2005);

    insert_sort_year(movies, len, &new_movie);

    free(new_movie.title);
    free(new_movie.name);

    ck_assert_int_eq(movies[0].year, 2000);
    ck_assert_int_eq(movies[1].year, 2005);
    ck_assert_int_eq(movies[2].year, 2010);

    free_movies(movies, 3);
}
END_TEST

START_TEST(test_insert_sort_by_field_title)
{
    movie_t *movies = malloc(3 * sizeof(movie_t));
    size_t len = 2;

    movies[0] = create_movie("A Movie", "Director A", 2000);
    movies[1] = create_movie("C Movie", "Director C", 2010);

    movie_t new_movie = create_movie("B Movie", "Director B", 2005);

    insert_sort_by_field(movies, len, &new_movie, "title");

    free(new_movie.title);
    free(new_movie.name);

    ck_assert_str_eq(movies[0].title, "A Movie");
    ck_assert_str_eq(movies[1].title, "B Movie");
    ck_assert_str_eq(movies[2].title, "C Movie");

    free_movies(movies, 3);
}
END_TEST

START_TEST(test_insert_sort_by_field_name)
{
    movie_t *movies = malloc(3 * sizeof(movie_t));
    size_t len = 2;

    movies[0] = create_movie("Movie A", "Director A", 2000);
    movies[1] = create_movie("Movie C", "Director C", 2010);

    movie_t new_movie = create_movie("Movie B", "Director B", 2005);

    insert_sort_by_field(movies, len, &new_movie, "name");

    free(new_movie.title);
    free(new_movie.name);

    ck_assert_str_eq(movies[0].name, "Director A");
    ck_assert_str_eq(movies[1].name, "Director B");
    ck_assert_str_eq(movies[2].name, "Director C");

    free_movies(movies, 3);
}
END_TEST

START_TEST(test_insert_sort_by_field_year)
{
    movie_t *movies = malloc(3 * sizeof(movie_t));
    size_t len = 2;

    movies[0] = create_movie("Movie A", "Director A", 2000);
    movies[1] = create_movie("Movie C", "Director C", 2010);

    movie_t new_movie = create_movie("Movie B", "Director B", 2005);

    insert_sort_by_field(movies, len, &new_movie, "year");

    free(new_movie.title);
    free(new_movie.name);

    ck_assert_int_eq(movies[0].year, 2000);
    ck_assert_int_eq(movies[1].year, 2005);
    ck_assert_int_eq(movies[2].year, 2010);

    free_movies(movies, 3);
}
END_TEST

Suite *insert_sort_suite(void)
{
    Suite *s;
    TCase *tc_insert_sort;

    s = suite_create("insert_sort");

    tc_insert_sort = tcase_create("insert_sort_positives");
    tcase_add_test(tc_insert_sort, test_insert_sort_title);
    tcase_add_test(tc_insert_sort, test_insert_sort_name);
    tcase_add_test(tc_insert_sort, test_insert_sort_year);
    tcase_add_test(tc_insert_sort, test_insert_sort_by_field_title);
    tcase_add_test(tc_insert_sort, test_insert_sort_by_field_name);
    tcase_add_test(tc_insert_sort, test_insert_sort_by_field_year);

    suite_add_tcase(s, tc_insert_sort);

    return s;
}
