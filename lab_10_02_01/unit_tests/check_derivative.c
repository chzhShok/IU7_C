#include <check.h>

#include "check_main.h"
#include "list.h"

START_TEST(test_derivative_simple)
{
    node_t *head = create_node(3, 4);
    head->next = create_node(2, 3);
    head->next->next = create_node(1, 2);
    head->next->next->next = create_node(0, 5);

    node_t *d_head = NULL;
    derivative(&head, &d_head);

    ck_assert_int_eq(d_head->degree, 2);
    ck_assert_int_eq(d_head->coeff, 12);
    ck_assert_int_eq(d_head->next->degree, 1);
    ck_assert_int_eq(d_head->next->coeff, 6);
    ck_assert_int_eq(d_head->next->next->degree, 0);
    ck_assert_int_eq(d_head->next->next->coeff, 2);

    free_list(head);
    free_list(d_head);
}
END_TEST

START_TEST(test_derivative_single_term)
{
    node_t *head = create_node(5, 3);

    node_t *d_head = NULL;
    derivative(&head, &d_head);

    ck_assert_int_eq(d_head->degree, 4);
    ck_assert_int_eq(d_head->coeff, 15);

    free_list(head);
    free_list(d_head);
}
END_TEST

START_TEST(test_derivative_empty)
{
    node_t *head = NULL;

    node_t *d_head = NULL;
    int result = derivative(&head, &d_head);

    ck_assert_int_eq(result, 0);
    ck_assert_ptr_eq(d_head, NULL);

    free_list(d_head);
}
END_TEST

START_TEST(test_derivative_all_zero)
{
    node_t *head = create_node(3, 0);
    head->next = create_node(2, 0);
    head->next->next = create_node(1, 0);

    node_t *d_head = NULL;
    derivative(&head, &d_head);

    ck_assert_ptr_eq(d_head, NULL);

    free_list(head);
}
END_TEST

Suite *derivative_suite(void)
{
    Suite *s = suite_create("Derivative");
    TCase *tc = tcase_create("Test");

    tcase_add_test(tc, test_derivative_simple);
    tcase_add_test(tc, test_derivative_single_term);
    tcase_add_test(tc, test_derivative_empty);
    tcase_add_test(tc, test_derivative_all_zero);

    suite_add_tcase(s, tc);
    return s;
}
