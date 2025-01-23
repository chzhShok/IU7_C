#include <check.h>
#include <stdlib.h>

#include "check_main.h"
#include "matrix.h"

int cmp_matrix(double **matrix1, double **matrix2, size_t n, size_t m)
{
    for (size_t i = 0; i < n; i++)
        for (size_t j = 0; j < m; j++)
            if (fabs((matrix1[i][j] - matrix2[i][j])) > EPS)
                return 0;
    return 1;
}

int main(void)
{
    int no_failed = 0;
    Suite *s_add, *s_mult;
    SRunner *runner;

    s_add = add_suite();
    runner = srunner_create(s_add);
    srunner_run_all(runner, CK_VERBOSE);
    no_failed += srunner_ntests_failed(runner);
    srunner_free(runner);

    s_mult = multiplication_suite();
    runner = srunner_create(s_mult);
    srunner_run_all(runner, CK_VERBOSE);
    no_failed += srunner_ntests_failed(runner);
    srunner_free(runner);

    return (no_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
