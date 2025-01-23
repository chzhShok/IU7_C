#include <check.h>

#include "check_main.h"
#include "list.h"

START_TEST(test_pop_back_single_element)
{
    int data = 42;
    node_t *head = create_node(&data);

    int *result = pop_back(&head);
    ck_assert_ptr_nonnull(result);
    ck_assert_int_eq(*result, 42);
    ck_assert_ptr_null(head);
}
END_TEST

START_TEST(test_pop_back_multiple_elements)
{
    int data1 = 10, data2 = 20, data3 = 30;
    node_t *head = create_node(&data1);
    head->next = create_node(&data2);
    head->next->next = create_node(&data3);

    int *result = pop_back(&head);
    ck_assert_ptr_nonnull(result);
    ck_assert_int_eq(*result, 30);

    result = pop_back(&head);
    ck_assert_ptr_nonnull(result);
    ck_assert_int_eq(*result, 20);

    result = pop_back(&head);
    ck_assert_ptr_nonnull(result);
    ck_assert_int_eq(*result, 10);

    ck_assert_ptr_null(head);
}
END_TEST

START_TEST(test_pop_back_empty_list)
{
    node_t *head = NULL;
    void *result = pop_back(&head);
    ck_assert_ptr_null(result);
    ck_assert_ptr_null(head);
}
END_TEST

START_TEST(test_pop_back_null_pointer)
{
    node_t *head = NULL;
    void *result = pop_back(&head);
    ck_assert_ptr_null(result);
}
END_TEST

START_TEST(test_pop_back_with_null_data)
{
    node_t *head = create_node(NULL);
    void *result = pop_back(&head);
    ck_assert_ptr_null(result);
    ck_assert_ptr_null(head);
}
END_TEST

Suite *pop_back_suite(void)
{
    Suite *s;
    TCase *tc_pos, *tc_neg;

    s = suite_create("Pop Back Tests");

    tc_pos = tcase_create("Positive Tests");
    tcase_add_test(tc_pos, test_pop_back_single_element);
    tcase_add_test(tc_pos, test_pop_back_multiple_elements);
    suite_add_tcase(s, tc_pos);

    tc_neg = tcase_create("Negative Tests");
    tcase_add_test(tc_neg, test_pop_back_empty_list);
    tcase_add_test(tc_neg, test_pop_back_null_pointer);
    tcase_add_test(tc_neg, test_pop_back_with_null_data);
    suite_add_tcase(s, tc_neg);

    return s;
}
