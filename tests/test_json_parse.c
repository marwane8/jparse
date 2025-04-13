#include <stdio.h>
#include <string.h>
#include "minunit.h"

#include "json_parse.h"

static char *test_json_init()
{

    int x = 1;
    mu_assert("X cant do math", x + x == 2);
    pass_msg("test_json_init");
    return 0;
}

// INIT TESTS
static char *jdict_tests()
{
    printf("\n--- JDICT TESTS ---\n");
    mu_run_test(test_json_init);
    return 0;
}
