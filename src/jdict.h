#ifndef _JDICT_H_
#define _JDICT_H_

#include "macros.h"

#define JBUFFER 16
#define JSON_KEY_MAX 128
#define JSON_NODE_BUF 256 

typedef enum jtype
{
    INTEGER,
    FLOAT,
    STRING,
    JDICT,
    NONE
} jtype;

typedef union
{
    int int_val;
    float float_val;
    void *ptr_val;
} jval;

typedef struct jnode
{
    char key[JSON_KEY_MAX];
    jtype type;
    jval value;
} jnode;

typedef struct json
{
    size_t size;
    size_t len;
    jnode *arr;
} json;

int json_init(json *jj);
int json_add(json *jj, jnode node);
int json_del(json *jj, char *key);
char *json_srlz(json jsn);

int jput_int(json *jj, char *key, int number);
int jput_float(json *jj, char *key, float number);

#endif // _JDICT_H_