#include <check.h>

#include "associative_array.h"
#include "check_create.h"

START_TEST(test_create_assoc_array)
{
    assoc_array_t arr = assoc_array_create();

    ck_assert_ptr_nonnull(arr);

    assoc_array_destroy(&arr);
}
END_TEST

Suite *assoc_array_create_suite(void)
{
    Suite *s;
    TCase *tc;

    s = suite_create("assoc array each");

    tc = tcase_create("tests");
    tcase_add_test(tc, test_create_assoc_array);
    suite_add_tcase(s, tc);

    return s;
}
