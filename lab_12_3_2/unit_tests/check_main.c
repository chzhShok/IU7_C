#include <check.h>
#include <stdlib.h>

#include "check_main.h"

int main(void)
{
    int no_failed = 0;
    Suite *s_prime, *s_insert;
    SRunner *runner;

    s_prime = prime_suite();
    runner = srunner_create(s_prime);
    srunner_run_all(runner, CK_VERBOSE);
    no_failed += srunner_ntests_failed(runner);
    srunner_free(runner);

    s_insert = insert_after_even_suite();
    runner = srunner_create(s_insert);
    srunner_run_all(runner, CK_VERBOSE);
    no_failed += srunner_ntests_failed(runner);
    srunner_free(runner);

    return (no_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
