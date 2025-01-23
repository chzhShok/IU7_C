#include <check.h>

#include "check_main.h"

int main(void)
{
    int errs = 0;

    Suite *s_val, *s_ddx, *s_dvd, *s_sum;
    SRunner *runner;

    s_val = calculate_val_suite();
    runner = srunner_create(s_val);
    srunner_run_all(runner, CK_VERBOSE);
    errs += srunner_ntests_failed(runner);
    srunner_free(runner);

    s_ddx = derivative_suite();
    runner = srunner_create(s_ddx);
    srunner_run_all(runner, CK_VERBOSE);
    errs += srunner_ntests_failed(runner);
    srunner_free(runner);

    s_dvd = odd_even_polynomial_suite();
    runner = srunner_create(s_dvd);
    srunner_run_all(runner, CK_VERBOSE);
    errs += srunner_ntests_failed(runner);
    srunner_free(runner);

    s_sum = sum_polynomials_suite();
    runner = srunner_create(s_sum);
    srunner_run_all(runner, CK_VERBOSE);
    errs += srunner_ntests_failed(runner);
    srunner_free(runner);

    return errs;
}
