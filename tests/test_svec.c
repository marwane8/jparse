#include <stdio.h>
#include <string.h>
#include "minunit.h"
#include "svec.h"

static char *test_svec_add()
{
    svec vec;
    strv_init(&vec);
    char *string = strv_get(vec);
    mu_assert("X vector not initalized", *string == 0);

    strv_add(&vec, "Hello world");
    string = strv_get(vec);
    int res1 = strcmp(string, "Hello world");
    mu_assert("X failed init append", res1 == 0);

    strv_add(&vec, " I'm Working!");
    string = strv_get(vec);
    int res2 = strcmp(string, "Hello world I'm Working!");
    mu_assert("X failed second append", res2 == 0);

    strv_init(&vec);
    string = strv_get(vec);
    mu_assert("X failed vector cleared", *string == 0);

    pass_msg("test_svec_add");
    return 0;
}

// INIT TESTS
static char *svec_tests()
{
    printf("\n--- SVEC TESTS ---\n");
    mu_run_test(test_svec_add);
    return 0;
}
