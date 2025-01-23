#include <check.h>

#include "check_main.h"
#include "list.h"

START_TEST(test_calculate_val_simple)
{
    node_t *head = create_node(2, 1);
    head->next = create_node(1, 2);
    head->next->next = create_node(0, 3);

    int result = calculate_val(&head, 2);
    ck_assert_int_eq(result, 1 * pow(2, 2) + 2 * pow(2, 1) + 3 * pow(2, 0));

    free_list(head);
}
END_TEST

START_TEST(test_calculate_val_zero_coefficients)
{
    node_t *head = create_node(2, 0);
    head->next = create_node(1, 0);
    head->next->next = create_node(0, 0);

    int result = calculate_val(&head, 5);
    ck_assert_int_eq(result, 0);

    free_list(head);
}
END_TEST

START_TEST(test_calculate_val_zero_degree)
{
    node_t *head = create_node(0, 4);

    int result = calculate_val(&head, 10);
    ck_assert_int_eq(result, 4);

    free_list(head);
}
END_TEST

START_TEST(test_calculate_val_negative_x)
{
    node_t *head = create_node(2, 1);
    head->next = create_node(1, -2);
    head->next->next = create_node(0, 3);

    int result = calculate_val(&head, -3);
    ck_assert_int_eq(result, 1 * pow(-3, 2) + (-2) * pow(-3, 1) + 3 * pow(-3, 0));

    free_list(head);
}
END_TEST

START_TEST(test_calculate_val_empty)
{
    node_t *head = NULL;

    int result = calculate_val(&head, 10);
    ck_assert_int_eq(result, 0);

    free_list(head);
}
END_TEST

Suite *calculate_val_suite(void)
{
    Suite *s = suite_create("Calculate val");
    TCase *tc = tcase_create("Test");

    tcase_add_test(tc, test_calculate_val_simple);
    tcase_add_test(tc, test_calculate_val_zero_coefficients);
    tcase_add_test(tc, test_calculate_val_zero_degree);
    tcase_add_test(tc, test_calculate_val_negative_x);
    tcase_add_test(tc, test_calculate_val_empty);

    suite_add_tcase(s, tc);
    return s;
}
