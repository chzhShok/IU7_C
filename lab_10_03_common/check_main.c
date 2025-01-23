#include <check.h>

#include "check_create.h"
#include "check_each.h"
#include "check_find.h"
#include "check_insert.h"
#include "check_max.h"
#include "check_min.h"
#include "check_remove.h"

int main(void)
{
    int errs = 0;

    Suite *s_arr_max, *s_arr_min, *s_arr_each, *s_arr_remove, *s_arr_find, *s_arr_insert, *s_arr_create;
    SRunner *runner;

    s_arr_create = assoc_array_create_suite();
    runner = srunner_create(s_arr_create);
    srunner_run_all(runner, CK_VERBOSE);
    errs += srunner_ntests_failed(runner);
    srunner_free(runner);

    s_arr_insert = assoc_array_insert_suite();
    runner = srunner_create(s_arr_insert);
    srunner_run_all(runner, CK_VERBOSE);
    errs += srunner_ntests_failed(runner);
    srunner_free(runner);

    s_arr_find = assoc_array_find_suite();
    runner = srunner_create(s_arr_find);
    srunner_run_all(runner, CK_VERBOSE);
    errs += srunner_ntests_failed(runner);
    srunner_free(runner);

    s_arr_remove = assoc_array_remove_suite();
    runner = srunner_create(s_arr_remove);
    srunner_run_all(runner, CK_VERBOSE);
    errs += srunner_ntests_failed(runner);
    srunner_free(runner);

    s_arr_each = assoc_array_each_suite();
    runner = srunner_create(s_arr_each);
    srunner_run_all(runner, CK_VERBOSE);
    errs += srunner_ntests_failed(runner);
    srunner_free(runner);

    s_arr_min = assoc_array_min_suite();
    runner = srunner_create(s_arr_min);
    srunner_run_all(runner, CK_VERBOSE);
    errs += srunner_ntests_failed(runner);
    srunner_free(runner);

    s_arr_max = assoc_array_max_suite();
    runner = srunner_create(s_arr_max);
    srunner_run_all(runner, CK_VERBOSE);
    errs += srunner_ntests_failed(runner);
    srunner_free(runner);

    return errs;
}
