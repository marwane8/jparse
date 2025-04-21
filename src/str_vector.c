#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>

#include "str_vector.h"
#include "util.h"

#define VECSIZ 64

int strv_init(str_vec *vec)
{
    vec->string = calloc(VECSIZ, sizeof(char));
    vec->size = VECSIZ;
    return 0;
}

char *strv_add(str_vec *vec, char *string)
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

        int block_size = vec->size * vec->size;
        vec->string = realloc(vec->string, sizeof(char) * block_size);
        if (vec->string == NULL)
        {
            LOGERROR("strvec.c:strv_add - unable to realloc");
            return "";
        }

        vec->size = block_size;
    }

    strncat(vec->string, string, cat_len);
    return vec->string;
}

int strv_fmap(char *fpath, str_vec *vec)
{

    int fd = open(fpath, O_RDONLY);
    if (fd < 0)
    {
        LOGERROR("file not found: %s", fpath);
        return -1;
    }

    struct stat st;

    if (fstat(fd, &st) == -1)
    {
        LOGERROR("unable to retrieve file size");
        return -1;
    }

    char *mem_array = mmap(NULL, st.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
    vec->string = mem_array;
    vec->size = st.st_size;
    return 0;
}

char *strv_addc(str_vec *vec, char ch)
{

    if (vec->string == NULL)
    {
        LOGERROR("vec is not initialized.");
        return NULL;
    }

    int len = strlen(vec->string);
    if (vec->size <= len + 1)
    {

        int block_size = vec->size * vec->size;
        vec->string = realloc(vec->string, sizeof(char) * block_size);
        if (vec->string == NULL)
        {
            LOGERROR("strvec.c:strv_add - unable to realloc");
            return "";
        }

        vec->size = block_size;
    }

    vec->string[len] = ch;
    vec->string[len + 1] = '\0';

    return vec->string;
}

char *strv_get(str_vec vec)
{
    if (vec.string == NULL)
    {
        return NULL;
    }

    return vec.string;
}

int strv_free(str_vec *vec)
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

void strv_log(str_vec vec)
{
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
