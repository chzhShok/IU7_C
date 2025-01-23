#include <check.h>
#include <stdlib.h>

#include "check_main.h"
#include "list.h"

START_TEST(test_sort_non_empty_list)
{
    film_t *film1 = malloc(sizeof(film_t));
    film1->name = strdup("Film A");
    film1->year = 2005;
    film1->rating = 7.5;

    film_t *film2 = malloc(sizeof(film_t));
    film2->name = strdup("Film B");
    film2->year = 1998;
    film2->rating = 8.0;

    film_t *film3 = malloc(sizeof(film_t));
    film3->name = strdup("Film C");
    film3->year = 2015;
    film3->rating = 6.5;

    node_t *head = malloc(sizeof(node_t));
    head->data = film1;
    head->next = malloc(sizeof(node_t));
    head->next->data = film2;
    head->next->next = malloc(sizeof(node_t));
    head->next->next->data = film3;
    head->next->next->next = NULL;

    head = sort(head, comparator);

    ck_assert_ptr_nonnull(head);
    ck_assert_ptr_nonnull(head->next);
    ck_assert_ptr_nonnull(head->next->next);

    ck_assert_int_eq(((film_t *) (head->data))->year, 1998);
    ck_assert_int_eq(((film_t *) (head->next->data))->year, 2005);
    ck_assert_int_eq(((film_t *) (head->next->next->data))->year, 2015);

    free(film1->name);
    free(film2->name);
    free(film3->name);
    free(film1);
    free(film2);
    free(film3);
    free_list(head);
}
END_TEST

START_TEST(test_sort_empty_list)
{
    node_t *head = NULL;

    head = sort(head, comparator);

    ck_assert_ptr_null(head);
}
END_TEST

START_TEST(test_sort_single_element)
{
    film_t *film = malloc(sizeof(film_t));
    film->name = strdup("Film A");
    film->year = 2005;
    film->rating = 7.5;

    node_t *head = malloc(sizeof(node_t));
    head->data = film;
    head->next = NULL;

    head = sort(head, comparator);

    ck_assert_ptr_nonnull(head);
    ck_assert_ptr_null(head->next);
    ck_assert_int_eq(((film_t *) (head->data))->year, 2005);

    free(film->name);
    free(film);
    free_list(head);
}
END_TEST

START_TEST(test_sort_duplicates)
{
    film_t *film1 = malloc(sizeof(film_t));
    film1->name = strdup("Film A");
    film1->year = 2005;
    film1->rating = 7.5;

    film_t *film2 = malloc(sizeof(film_t));
    film2->name = strdup("Film B");
    film2->year = 2005;
    film2->rating = 8.0;

    film_t *film3 = malloc(sizeof(film_t));
    film3->name = strdup("Film C");
    film3->year = 2005;
    film3->rating = 6.5;

    node_t *head = malloc(sizeof(node_t));
    head->data = film1;
    head->next = malloc(sizeof(node_t));
    head->next->data = film2;
    head->next->next = malloc(sizeof(node_t));
    head->next->next->data = film3;
    head->next->next->next = NULL;

    head = sort(head, comparator);

    ck_assert_ptr_nonnull(head);
    ck_assert_ptr_nonnull(head->next);
    ck_assert_ptr_nonnull(head->next->next);

    ck_assert_int_eq(((film_t *) (head->data))->year, 2005);
    ck_assert_int_eq(((film_t *) (head->next->data))->year, 2005);
    ck_assert_int_eq(((film_t *) (head->next->next->data))->year, 2005);

    free(film1->name);
    free(film2->name);
    free(film3->name);
    free(film1);
    free(film2);
    free(film3);
    free_list(head);
}
END_TEST

Suite *sort_suite(void)
{
    Suite *s;
    TCase *tc_pos;

    s = suite_create("Sort Tests");

    tc_pos = tcase_create("Positive Tests");
    tcase_add_test(tc_pos, test_sort_non_empty_list);
    tcase_add_test(tc_pos, test_sort_empty_list);
    tcase_add_test(tc_pos, test_sort_single_element);
    tcase_add_test(tc_pos, test_sort_duplicates);
    suite_add_tcase(s, tc_pos);

    return s;
}
