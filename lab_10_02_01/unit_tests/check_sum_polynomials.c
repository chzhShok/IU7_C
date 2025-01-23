#include <check.h>

#include "check_main.h"
#include "list.h"

START_TEST(test_sum_polynomials_simple) {
    node_t *head1 = create_node(3, 4);
    head1->next = create_node(2, 3);
    head1->next->next = create_node(1, 2);

    node_t *head2 = create_node(3, 1);
    head2->next = create_node(2, 2);
    head2->next->next = create_node(0, 5);

    node_t *result = sum_polynomials(&head1, &head2);

    ck_assert_int_eq(result->degree, 3);
    ck_assert_int_eq(result->coeff, 5);
    ck_assert_int_eq(result->next->degree, 2);
    ck_assert_int_eq(result->next->coeff, 5);
    ck_assert_int_eq(result->next->next->degree, 1);
    ck_assert_int_eq(result->next->next->coeff, 2);
    ck_assert_int_eq(result->next->next->next->degree, 0);
    ck_assert_int_eq(result->next->next->next->coeff, 5);

    free_list(head1);
    free_list(head2);
    free_list(result);
}
END_TEST

START_TEST(test_sum_polynomials_different_degrees) {
    node_t *head1 = create_node(4, 3);
    head1->next = create_node(2, 5);

    node_t *head2 = create_node(3, 7);
    head2->next = create_node(1, 2);
    head2->next->next = create_node(0, 4);

    node_t *result = sum_polynomials(&head1, &head2);

    ck_assert_int_eq(result->degree, 4);
    ck_assert_int_eq(result->coeff, 3);
    ck_assert_int_eq(result->next->degree, 3);
    ck_assert_int_eq(result->next->coeff, 7);
    ck_assert_int_eq(result->next->next->degree, 2);
    ck_assert_int_eq(result->next->next->coeff, 5);
    ck_assert_int_eq(result->next->next->next->degree, 1);
    ck_assert_int_eq(result->next->next->next->coeff, 2);
    ck_assert_int_eq(result->next->next->next->next->degree, 0);
    ck_assert_int_eq(result->next->next->next->next->coeff, 4);

    free_list(head1);
    free_list(head2);
    free_list(result);
}
END_TEST

START_TEST(test_sum_polynomials_empty_lists) {
    node_t *head1 = NULL;
    node_t *head2 = NULL;

    node_t *result = sum_polynomials(&head1, &head2);

    ck_assert_ptr_eq(result, NULL);
}
END_TEST

START_TEST(test_sum_polynomials_one_empty_list) {
    node_t *head1 = create_node(3, 4);
    head1->next = create_node(2, 3);

    node_t *head2 = NULL;

    node_t *result = sum_polynomials(&head1, &head2);

    ck_assert_int_eq(result->degree, 3);
    ck_assert_int_eq(result->coeff, 4);
    ck_assert_int_eq(result->next->degree, 2);
    ck_assert_int_eq(result->next->coeff, 3);

    free_list(head1);
    free_list(result);
}
END_TEST

START_TEST(test_sum_polynomials_mixed_degrees) {
    node_t *head1 = create_node(4, 3);
    head1->next = create_node(2, 5);
    head1->next->next = create_node(0, 1);

    node_t *head2 = create_node(3, 7);
    head2->next = create_node(2, 2);
    head2->next->next = create_node(0, 5);

    node_t *result = sum_polynomials(&head1, &head2);

    ck_assert_int_eq(result->degree, 4);
    ck_assert_int_eq(result->coeff, 3);
    ck_assert_int_eq(result->next->degree, 3);
    ck_assert_int_eq(result->next->coeff, 7);
    ck_assert_int_eq(result->next->next->degree, 2);
    ck_assert_int_eq(result->next->next->coeff, 7);
    ck_assert_int_eq(result->next->next->next->degree, 0);
    ck_assert_int_eq(result->next->next->next->coeff, 6);

    free_list(head1);
    free_list(head2);
    free_list(result);
}
END_TEST

START_TEST(test_sum_polynomials_identical_lists) {
    node_t *head1 = create_node(3, 4);
    head1->next = create_node(2, 3);
    head1->next->next = create_node(1, 2);

    node_t *head2 = create_node(3, 4);
    head2->next = create_node(2, 3);
    head2->next->next = create_node(1, 2);

    node_t *result = sum_polynomials(&head1, &head2);

    ck_assert_int_eq(result->degree, 3);
    ck_assert_int_eq(result->coeff, 8);
    ck_assert_int_eq(result->next->degree, 2);
    ck_assert_int_eq(result->next->coeff, 6);
    ck_assert_int_eq(result->next->next->degree, 1);
    ck_assert_int_eq(result->next->next->coeff, 4);

    free_list(head1);
    free_list(head2);
    free_list(result);
}
END_TEST

Suite *sum_polynomials_suite(void)
{
    Suite *s = suite_create("Sum polynomials");
    TCase *tc = tcase_create("Test");

    tcase_add_test(tc, test_sum_polynomials_simple);
    tcase_add_test(tc, test_sum_polynomials_different_degrees);
    tcase_add_test(tc, test_sum_polynomials_empty_lists);
    tcase_add_test(tc, test_sum_polynomials_one_empty_list);
    tcase_add_test(tc, test_sum_polynomials_mixed_degrees);
    tcase_add_test(tc, test_sum_polynomials_identical_lists);

    suite_add_tcase(s, tc);
    return s;
}
