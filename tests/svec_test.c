/* file minunit_example.c */

#include <stdio.h>
#include <string.h>
#include "minunit.h"
#include "svec.h"

int tests_run = 0;

static char *test_svec_add()
{
    svec vec;
    svinit(&vec);
    char *string = svget(vec);
    mu_assert("X vector not initalized", *string == 0);

    svadd(&vec, "Hello world");
    string = svget(vec);
    int res1 = strcmp(string, "Hello world");
    mu_assert("X failed init append", res1 == 0);

    svadd(&vec, " I'm Working!");
    string = svget(vec);
    int res2 = strcmp(string, "Hello world I'm Working!");
    mu_assert("X failed second append", res2 == 0);

    svinit(&vec);
    string = svget(vec);
    mu_assert("X vector not cleared", *string == 0);

    pass_msg("test_svec_add");
    return 0;
}

// INIT TESTS
static char *all_tests()
{
    mu_run_test(test_svec_add);
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
