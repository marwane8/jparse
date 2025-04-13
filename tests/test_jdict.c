#include <stdio.h>
#include <string.h>
#include "minunit.h"

#include "jdict.h"

static char *test_json_init()
{
    json json;
    char *out;
    int res;

    json_init(&json);
    out = json_srlz(json);
    res = strcmp(out, "{}");
    mu_assert("X failed null json", 0 == res);

    jput_int(&json, "age", 23);
    jput_float(&json, "balance", 120.125);
    out = json_srlz(json);
    res = strcmp(out, "{ \"age\" : 23, \"balance\" : 120.125000 }\n");
    mu_assert("X failed number inserts", 0 == res);

    jput_string(&json, "name", "retarded");
    out = json_srlz(json);

    pass_msg("test_json_init");
    return 0;
}

static char *test_json_string()
{
    json json;
    char *out;
    int res;

    json_init(&json);
    jput_string(&json, "name", "buddy");
    jput_string(&json, NULL, "buddy");
    out = json_srlz(json);
    res = strcmp(out, "{ \"name\" : \"buddy\" }\n");

    printf("%s", out);

    mu_assert("X failed string inserts", 0 == res);

    pass_msg("test_json_string");
    return 0;
}

// INIT TESTS
static char *jdict_tests()
{
    printf("\n--- JDICT TESTS ---\n");
    mu_run_test(test_json_init);
    mu_run_test(test_json_string);
    return 0;
}
