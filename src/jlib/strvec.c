#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "strvec.h"

void svprint(strvec vector)
{
    printf("|| cap: %d | len: %d | start: %p ||\n[ ", vector.capacity, vector.length, vector.list);
    for (size_t i = 0; i < vector.length; ++i)
    {
        printf("\"%s\" - ", vector.list[i]);
    }
    printf(" ]\n");
}

int svpush(strvec *vector, char *string)
{
    size_t cap = vector->capacity;
    size_t len = vector->length;

    if (cap == 0)
    {
        vector->list = (char **)calloc(1, sizeof(char *));
        if (!vector->list) {
            return -1;
        }
        ++cap;
    }
    else if (cap == len)
    {
        cap = cap * 2;
        vector->list = realloc(vector->list, cap);
    }

    vector->list[len] = string;
    ++len;
    vector->capacity = cap;
    vector->length = len;
    return 0;
}

char *svpop(strvec *vector)
{
    if (vector->length == 0)
    {
        return NULL;
    }
    char *pop = vector->list[vector->length - 1];
    --vector->length;
    return pop;
}

char *svat(strvec *vector, size_t i)
{
    if (vector->length == 0 || i >= vector->length)
    {
        return NULL;
    }
    return vector->list[i];
}

int svrm(strvec *vector, size_t i)
{
    if (vector->length == 0 || i >= vector->length)
    {
        return -1;
    }

    for (size_t n = i + 1; n < vector->length; ++n)
    {
        vector->list[n - 1] = vector->list[n];
    }
    --vector->length;
    return 0;
}
