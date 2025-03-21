#include <stdio.h>
#include <string.h>

#include "minunit.h"
#include "test_svec.c"
#include "test_jdict.c"

int tests_run = 0;

// INIT TESTS
static char *all_tests()
{
    mu_run_test(svec_tests);
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