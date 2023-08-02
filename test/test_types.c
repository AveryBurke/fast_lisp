#include <stdio.h>
#include "test.h"
#include "../repl.h"

#define increment_tests_run { tests_run++; }

int tests_run = 0;

int test_int(void)
{
    begin_test
    double i = new_int(-9);
    assert_eq_type(get_type(i), TYPE_INT, "int");
    begin_test
    double j = new_int(9);
    assert_eq_type(get_type(j), TYPE_INT, "int");
    return 1;
}

int test_symbol(void)
{
    begin_test
    char *str = "symbol";
    double s = new_symbol(str);
    assert_eq_type(get_type(s), TYPE_SYM, "symbol");
    return 1;
}

int test_float(void)
{
    begin_test
    double f = 2.2;
    assert_eq_type(get_type(f), TYPE_FLOAT, "float");
    begin_test
    double not_f = -2.2;
    assert_eq_type(get_type(not_f), TYPE_FLOAT, "float");
    return 1;
}

int all_tests(void)
{
    run_test(test_int);
    run_test(test_symbol); 
    run_test(test_float);
    return 1;
}

int main(int argc, char **argv)
{
    int result = all_tests();
    if (result == 1)
    {
        printf("\nall tests passed!!\n");
    }
    printf("\ntests run: %i\n", tests_run);
    return !result;
}