#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "jdict.h"

jdict *jput(jdict *dict, jnode jnode);
int jcpy(jnode *dest, jnode *src);

jdict *jinit()
{
    jnode *n = calloc(JBUFFER, sizeof(jnode));
    jdict *dict = (jdict *)calloc(1, sizeof(jdict)); // Allocates and zeroes memory
    if (dict)
    {
        dict->nodes = n; // Assuming `n` is already allocated or initialized
        dict->len = 0;
        dict->size = JBUFFER;
    }
    return dict;
}

jdict *jput_int(jdict *dict, char *key, int number)
{
    char keyValue[MAX_KEY_LENGTH];

    strncpy(keyValue, key, MAX_KEY_LENGTH - 1);

    jnode node = {
        .type = INTEGER,
        .value = {.int_val = number}};
    strcpy(node.key, key);
    dict = jput(dict, node);
    return dict;
}

jdict *jput_float(jdict *dict, char *key, float number)
{
    jnode node = {
        .type = FLOAT,
        .value = {.float_val = number}};
    strcpy(node.key, key);

    dict = jput(dict, node);
    return dict;
}

void jprint(jdict *dict)
{

    int len = dict->len;
    printf("{\n");
    for (size_t i = 0; i < len; i++)
    {
        jnode n = dict->nodes[i];
        printf("  %s : ", n.key);
        switch (n.type)
        {
        case INTEGER:
            printf("%d,\n", n.value.int_val);
            break;
        case FLOAT:
            printf("%.2f,\n", n.value.float_val);
            break;

        default:
            printf("-- , \n");
            break;
        }
    }
    printf("}\n");
}

// INTERNAL FUNCTIONS
jdict *jput(jdict *dict, jnode jnode)
{
    if (strlen(jnode.key) >= MAX_KEY_LENGTH)
    {
        printf("failed to insert: key >= 100 characters");
        return dict;
    }

    int length = dict->len;
    int max = dict->size;

    if (length == max)
    {
        dict = realloc(dict, (sizeof(jnode) * max * 2));
    }

    jcpy(&dict->nodes[length], &jnode);
    dict->len = length + 1;
    return dict;
}

int jcpy(jnode *dest, jnode *src)
{
    if (strlen(src->key) >= MAX_KEY_LENGTH)
    {
        printf("Key Error: %s", src->key);
        return 1;
    }

    strcpy(dest->key, src->key);
    dest->type = src->type;
    dest->value = src->value;
    return 0;
}