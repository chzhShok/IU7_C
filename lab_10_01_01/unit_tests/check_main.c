#include <check.h>

#include "check_main.h"

int main(void)
{
    int errs = 0;

    Suite *s_pop_front, *s_pop_back, *s_copy, *s_sort;
    SRunner *runner;

    s_pop_front = pop_front_suite();
    runner = srunner_create(s_pop_front);
    srunner_run_all(runner, CK_VERBOSE);
    errs += srunner_ntests_failed(runner);
    srunner_free(runner);

    s_pop_back = pop_back_suite();
    runner = srunner_create(s_pop_back);
    srunner_run_all(runner, CK_VERBOSE);
    errs += srunner_ntests_failed(runner);
    srunner_free(runner);

    s_copy = copy_suite();
    runner = srunner_create(s_copy);
    srunner_run_all(runner, CK_VERBOSE);
    errs += srunner_ntests_failed(runner);
    srunner_free(runner);

    s_sort = sort_suite();
    runner = srunner_create(s_sort);
    srunner_run_all(runner, CK_VERBOSE);
    errs += srunner_ntests_failed(runner);
    srunner_free(runner);

    return errs;
}
