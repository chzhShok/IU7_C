#include <check.h>
#include <stdlib.h>

#include "check_main.h"

int main(void)
{
    int no_failed = 0;
    Suite *s;
    SRunner *runner;

    s = snprintf_suite();
    runner = srunner_create(s);
    srunner_run_all(runner, CK_VERBOSE);
    no_failed += srunner_ntests_failed(runner);
    srunner_free(runner);

    return (no_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
