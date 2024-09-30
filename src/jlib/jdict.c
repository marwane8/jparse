#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "jdict.h"

int jdhashf(char *string);
int jdput(jdict *dict, char *key, jval value)
{
    int idx = jdhashf(key);

    jnode *nnode = (jnode *)calloc(1, sizeof(jnode));
    nnode->key = key;
    nnode->node.type = value.type;
    nnode->node.value = value.value;
    nnode->next = NULL;

    jnode *cnode = dict->jmap[idx];
    if (!cnode)
    {
        dict->jmap[idx] = nnode;
        return 0;
    }

    if (0 == strcmp(cnode->key, key))
    {
        cnode->node.type = value.type;
        cnode->node.value = value.value;
        return 0;
    }

    while (cnode->next)
    {
        if (0 == strcmp(cnode->key, key))
        {
            cnode->node.type = value.type;
            cnode->node.value = value.value;
            return 0;
        }
    }
    cnode->next = nnode;
    return 0;
}

jval jdget(jdict *dict, char *key)
{
    int idx = jdhashf(key);
    jnode *node = dict->jmap[idx];

    while (node)
    {
        if (0 == strcmp(node->key, key))
        {
            return node->node;
        }
        node = node->next;
    }
    jval nulnode = {.type = NONE, .value = NULL};
    return nulnode;
}

int jdrm(jdict *dict, char *key)
{
    int idx = jdhashf(key);
    jnode *node = dict->jmap[idx];

    if (0 == strcmp(node->key, key))
    {
        dict->jmap[idx] = NULL;
        return 0;
    }

    while (node)
    {
        jnode *nxtnode = node->next;
        if (0 == strcmp(nxtnode->key, key))
        {
            node->next = NULL;
        }
        node = node->next;
    }
    return 1;
}

int jdprint(jdict *dict)
{

    printf("{\n");
    for (int i = 0; i < DICTSIZE; ++i)
    {
        jnode *node = dict->jmap[i];

        while (node)
        {
            if (INT == node->node.type)
            {
                printf("  '%s' : '%d',\n", node->key, (int)node->node.value);
            }
            else if (STRING == node->node.type)
            {
                printf("  '%s' : '%s',\n", node->key, (char *)node->node.value);
            }
            node = node->next;
        }
    }
    printf("}\n");
    return 0;
}

// internal functions
int jdhashf(char *string)
{
    int hashval = 0;
    int len = strlen(string);

    for (int i = 0; i < len; ++i)
    {
        hashval = hashval + string[i];
    }

    int multp = strlen(string) % 7;
    hashval = hashval * multp;
    return hashval % DICTSIZE;
}
