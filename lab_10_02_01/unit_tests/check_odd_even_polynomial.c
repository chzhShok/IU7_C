#include <check.h>

#include "check_main.h"
#include "list.h"

START_TEST(test_odd_even_polynomial_simple)
{
    node_t *head = create_node(3, 4);
    head->next = create_node(2, 3);
    head->next->next = create_node(1, 2);
    head->next->next->next = create_node(0, 5);

    node_t *even = NULL;
    node_t *odd = NULL;

    odd_even_polynomial(&head, &even, &odd);

    ck_assert_int_eq(even->degree, 2);
    ck_assert_int_eq(even->coeff, 3);
    ck_assert_int_eq(odd->degree, 3);
    ck_assert_int_eq(odd->coeff, 4);
    ck_assert_int_eq(odd->next->degree, 1);
    ck_assert_int_eq(odd->next->coeff, 2);

    free_list(head);
    free_list(even);
    free_list(odd);
}
END_TEST

START_TEST(test_odd_even_polynomial_empty)
{
    node_t *head = NULL;
    node_t *even = NULL;
    node_t *odd = NULL;

    odd_even_polynomial(&head, &even, &odd);

    ck_assert_ptr_eq(even, NULL);
    ck_assert_ptr_eq(odd, NULL);
}
END_TEST

START_TEST(test_odd_even_polynomial_single_even)
{
    node_t *head = create_node(2, 3);
    node_t *even = NULL;
    node_t *odd = NULL;

    odd_even_polynomial(&head, &even, &odd);

    ck_assert_int_eq(even->degree, 2);
    ck_assert_int_eq(even->coeff, 3);
    ck_assert_ptr_eq(odd, NULL);

    free_list(head);
    free_list(even);
}
END_TEST

START_TEST(test_odd_even_polynomial_single_odd)
{
    node_t *head = create_node(3, 5);
    node_t *even = NULL;
    node_t *odd = NULL;

    odd_even_polynomial(&head, &even, &odd);

    ck_assert_int_eq(odd->degree, 3);
    ck_assert_int_eq(odd->coeff, 5);
    ck_assert_ptr_eq(even, NULL);

    free_list(head);
    free_list(odd);
}
END_TEST

START_TEST(test_odd_even_polynomial_all_even)
{
    node_t *head = create_node(4, 3);
    head->next = create_node(2, 5);
    head->next->next = create_node(0, 7);

    node_t *even = NULL;
    node_t *odd = NULL;

    odd_even_polynomial(&head, &even, &odd);

    ck_assert_int_eq(even->degree, 4);
    ck_assert_int_eq(even->coeff, 3);
    ck_assert_int_eq(even->next->degree, 2);
    ck_assert_int_eq(even->next->coeff, 5);
    ck_assert_int_eq(even->next->next->degree, 0);
    ck_assert_int_eq(even->next->next->coeff, 7);
    ck_assert_ptr_eq(odd, NULL);

    free_list(head);
    free_list(even);
}
END_TEST

START_TEST(test_odd_even_polynomial_all_odd)
{
    node_t *head = create_node(3, 5);
    head->next = create_node(1, 2);

    node_t *even = NULL;
    node_t *odd = NULL;

    odd_even_polynomial(&head, &even, &odd);

    ck_assert_int_eq(odd->degree, 3);
    ck_assert_int_eq(odd->coeff, 5);
    ck_assert_int_eq(odd->next->degree, 1);
    ck_assert_int_eq(odd->next->coeff, 2);
    ck_assert_ptr_eq(even, NULL);

    free_list(head);
    free_list(odd);
}
END_TEST

START_TEST(test_odd_even_polynomial_mixed)
{
    node_t *head = create_node(3, 4);
    head->next = create_node(2, 3);
    head->next->next = create_node(1, 2);
    head->next->next->next = create_node(0, 5);

    node_t *even = NULL;
    node_t *odd = NULL;

    odd_even_polynomial(&head, &even, &odd);

    ck_assert_int_eq(even->degree, 2);
    ck_assert_int_eq(even->coeff, 3);
    ck_assert_int_eq(odd->degree, 3);
    ck_assert_int_eq(odd->coeff, 4);
    ck_assert_int_eq(odd->next->degree, 1);
    ck_assert_int_eq(odd->next->coeff, 2);

    free_list(head);
    free_list(even);
    free_list(odd);
}
END_TEST

Suite *odd_even_polynomial_suite(void)
{
    Suite *s = suite_create("Odd even polynomial");
    TCase *tc = tcase_create("Test");

    tcase_add_test(tc, test_odd_even_polynomial_simple);
    tcase_add_test(tc, test_odd_even_polynomial_empty);
    tcase_add_test(tc, test_odd_even_polynomial_single_even);
    tcase_add_test(tc, test_odd_even_polynomial_single_odd);
    tcase_add_test(tc, test_odd_even_polynomial_all_even);
    tcase_add_test(tc, test_odd_even_polynomial_all_odd);
    tcase_add_test(tc, test_odd_even_polynomial_mixed);

    suite_add_tcase(s, tc);
    return s;
}
