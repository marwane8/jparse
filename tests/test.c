#include <stdio.h>
#include <string.h>

#include "minunit.h"
#include "test_str_vector.c"
#include "test_json_parse.c"

int tests_run = 0;

// INIT TESTS
static char *all_tests()
{
    mu_run_test(str_vec_tests);
    mu_run_test(jdict_tests);
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
        printf("\n\nALL TESTS PASSED\n");
    }
    printf("Tests run: %d\n", tests_run);

    return result != 0;
}