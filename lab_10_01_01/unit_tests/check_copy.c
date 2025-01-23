#include <check.h>
#include <stdlib.h>
#include <errno.h>

#include "check_main.h"
#include "list.h"

START_TEST(test_copy_empty_list)
{
    node_t *head = NULL;
    node_t *new_head = NULL;

    int result = copy(head, &new_head);

    ck_assert_int_eq(result, EINVAL);
    ck_assert_ptr_null(new_head);

    free_list(new_head);
}
END_TEST

START_TEST(test_copy_single_element)
{
    node_t *head = NULL;
    film_t film1 = {"Film1", 2000, 8.5};
    push_back(&head, &film1);

    node_t *new_head = NULL;
    int result = copy(head, &new_head);

    ck_assert_int_eq(result, 0);
    ck_assert_ptr_nonnull(new_head);


    ck_assert_ptr_eq(head->data, new_head->data);
    ck_assert_ptr_null(new_head->next);

    free_list(head);
    free_list(new_head);
}
END_TEST

START_TEST(test_copy_multiple_elements)
{
    node_t *head = NULL;
    film_t film1 = {"Film1", 2000, 8.5};
    film_t film2 = {"Film2", 2005, 7.2};
    film_t film3 = {"Film3", 2010, 9.0};

    push_back(&head, &film1);
    push_back(&head, &film2);
    push_back(&head, &film3);

    node_t *new_head = NULL;
    int result = copy(head, &new_head);

    ck_assert_int_eq(result, 0);
    ck_assert_ptr_nonnull(new_head);


    node_t *orig_node = head;
    node_t *copy_node = new_head;
    while (orig_node != NULL)
    {
        ck_assert_ptr_eq(orig_node->data, copy_node->data);
        orig_node = orig_node->next;
        copy_node = copy_node->next;
    }
    ck_assert_ptr_null(copy_node);

    free_list(head);
    free_list(new_head);
}
END_TEST

Suite *copy_suite(void)
{
    Suite *s;
    TCase *tc_pos;

    s = suite_create("Copy Tests");

    tc_pos = tcase_create("Positive Tests");
    tcase_add_test(tc_pos, test_copy_empty_list);
    tcase_add_test(tc_pos, test_copy_single_element);
    tcase_add_test(tc_pos, test_copy_multiple_elements);
    suite_add_tcase(s, tc_pos);

    return s;
}
