/* file minunit_example.c */

#include <stdio.h>
#include "minunit.h"
#include "jdict.h"

int tests_run = 0;

int foo = 7;
int bar = 4;

static char *test_foo()
{
    mu_assert("error, foo != 7", foo == 7);
    printf("> test_foo pass\n");
    return 0;
}

static char *test_jdict_numbers()
{
    jdict *json = jinit();
    int int_val = 34;
    float float_val = 1024.32;

    jput_int(json, "age", int_val);
    jput_float(json, "balance", float_val);

    mu_assert("node length != 2", json->len == 2);
    mu_assert("X node 1 is not INT", json->nodes[0].type == INTEGER);
    mu_assert("X node 1 is not int value incorrect", json->nodes[0].value.int_val == 34);

    mu_assert("X node 1 is not FLOAT", json->nodes[1].type == FLOAT);
    mu_assert("X node 1 is not float value incorrect", json->nodes[1].value.float_val == float_val);

    printf("> test_jdict_numbers\n");
    return 0;
}

static char *all_tests()
{
    mu_run_test(test_foo);
    mu_run_test(test_jdict_numbers);
    return 0;
}

int main(int argc, char **argv)
{
    char *result = all_tests();
    if (result != 0)
    {
        printf("%s\n", result);
    }
    else
    {
        printf("ALL TESTS PASSED\n");
    }
    printf("Tests run: %d\n", tests_run);

    return result != 0;
}
