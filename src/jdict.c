#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "jdict.h"

#include "svec.h"

int json_init(json *jj)
{
    jj->arr = calloc(JBUFFER, sizeof(jnode));
    jj->size = JBUFFER;
    jj->len = 0;
    return 0;
}
int json_add(json *jj, jnode node)
{
    jnode *arr = jj->arr;
    if (jj->arr == NULL)
    {
        LOGERROR("json is not initialized.");
        return -1;
    }

    if (jj->len == jj->size)
    {

        int block_size = jj->size * jj->size;
        jj->arr = realloc(jj->arr, sizeof(jnode) * block_size);
        if (jj->arr == NULL)
        {
            LOGERROR("unable to realloc json");
            return -1;
        }

        jj->size = block_size;
    }
    arr[jj->len] = node;
    jj->len++;
    return 0;
}

char *json_srlz(json jsn)
{
    int L = jsn.len;

    svec jvec;
    svinit(&jvec);
    svadd(&jvec, "{ ");

    if (L == 0)
        return "{}";

    for (int i = 0; i < L; i++)
    {

        jnode n = jsn.arr[i];
        jtype typ = n.type;
        char item[JSON_NODE_BUF];

        switch (typ)
        {
        case INTEGER:
            snprintf(item, JSON_NODE_BUF, "\"%s\" : %i", n.key, n.value.int_val);
            svadd(&jvec, item);
            break;
        case FLOAT:
            snprintf(item, JSON_NODE_BUF, "\"%s\" : %f", n.key, n.value.float_val);
            svadd(&jvec, item);
            break;

        default:
            printf(" no node");
            break;
        }

        if (i != L - 1)
            svadd(&jvec, ", ");
    }
    svadd(&jvec, " }\n");
    printf("size: %d\n", jvec.size);
    char *srlzd = svget(jvec);
    return srlzd;
}

int jput_int(json *jj, char *key, int number)
{

    if (jj->arr == NULL)
    {
        LOGERROR("null obj\n");
        return 1;
    }

    if (strlen(key) >= JSON_KEY_MAX)
    {
        LOGERROR("exceeded key length limit\n");
        return 1;
    }

    jnode node;
    strcpy(node.key, key);
    node.type = INTEGER;
    node.value.int_val = number;
    int res = json_add(jj, node);
    if (0 != res)
    {
        LOGERROR("unable to add int ");
        return -1;
    }

    return 0;
}

int jput_float(json *jj, char *key, float number)
{

    if (jj->arr == NULL)
    {
        LOGERROR("null obj\n");
        return 1;
    }

    if (strlen(key) >= JSON_KEY_MAX)
    {

        LOGERROR("exceeded key length limit\n");
        return 1;
    }

    jnode node;
    strcpy(node.key, key);
    node.type = FLOAT;
    node.value.float_val = number;
    int res = json_add(jj, node);
    if (0 != res)
    {
        LOGERROR("unable to add float");
        return -1;
    }

    return 0;
}