#include <check.h>
#include <stdlib.h>

#include "check_main.h"

int main(void)
{
    int no_failed = 0;
    Suite *s_key;
    Suite *s_sort;
    SRunner *runner;

    s_key = key_suite();
    runner = srunner_create(s_key);
    srunner_run_all(runner, CK_VERBOSE);
    no_failed += srunner_ntests_failed(runner);
    srunner_free(runner);

    s_sort = sort_suite();
    runner = srunner_create(s_sort);
    srunner_run_all(runner, CK_VERBOSE);
    no_failed += srunner_ntests_failed(runner);
    srunner_free(runner);

    return (no_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
