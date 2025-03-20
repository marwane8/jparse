#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "jdict.h"

int jput_int(jobj *obj, char *key, int number)
{

    if (obj == NULL)
    {
        printf("Error: null obj\n");
        return 1;
    }
    if (strlen(key) >= JSON_KEY_MAX)
    {

        printf("Error: key length\n");
        return 1;
    }

    strcpy(obj->key, key);
    obj->type = INTEGER;
    obj->value.int_val = number;
    return 0;
}

int jput_float(jobj *obj, char *key, float number)
{

    if (obj == NULL)
    {
        printf("Error: null obj\n");
        return 1;
    }
    if (strlen(key) >= JSON_KEY_MAX)
    {

        printf("Error: key length\n");
        return 1;
    }

    strcpy(obj->key, key);
    obj->type = FLOAT;
    obj->value.float_val = number;
    return 0;
}