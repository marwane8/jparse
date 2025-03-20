#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "svec.h"
#include "macros.h"

#define VECSIZ 64

void svinit(svec *vec)
{
    vec->string = calloc(VECSIZ, sizeof(char));
    vec->size = VECSIZ;
}

char *svadd(svec *vec, char *string)
{

    if (vec->string == NULL)
    {
        LOGERROR("vec is not initialized.");
        return NULL;
    }

    int src_len = strlen(vec->string);
    int cat_len = strlen(string);
    int new_length = src_len + cat_len;

    if (vec->size <= new_length)
    {

        int block_size = (new_length / VECSIZ) + 1;
        LOGINFO("strvec.c:svadd - reallocating...");
        vec->string = realloc(vec->string, sizeof(char) * block_size);
        if (vec->string == NULL)
        {
            LOGERROR("strvec.c:svadd - unable to realloc");
            return "";
        }

        vec->size = block_size;
    }

    strncat(vec->string, string, cat_len);
    return vec->string;
}

char *svget(svec vec)
{
    if (vec.string == NULL)
    {
        LOGERROR("vec is not initialized.");
        return NULL;
    }

    return vec.string;
}
int svfree(svec *vec)
{
    if (vec->size == 0)
    {
        LOGERROR("vector is empty aborting free...");
        return -1;
    }
    vec->size = 0;
    free(vec->string);
    return 0;
}

void svlog(svec vec)
{
    printf("innnher");

    if (vec.string == NULL)
    {
        LOGERROR("vec is not initialized.");
        return;
    }

    printf("-- vector --\n");
    printf("\tbuffer: %d\n", vec.size);
    printf("\tlength: %lu\n", strlen(vec.string));
    printf("\tstring: %s\n", vec.string);
    printf("--- end ---\n");
}
