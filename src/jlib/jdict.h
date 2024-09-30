#ifndef _JDICT_H_
#define _JDICT_H_

#include "strvec.h"

#define DICTSIZE 5

typedef enum
{
    INT,
    FLOAT,
    STRING,
    LIST,
    JDICT,
    NONE
} jtype;

typedef struct
{
    jtype type;
    void *value;
} jval;

typedef struct jnode
{
    char *key;
    jval node;
    struct jnode *next;
} jnode;

typedef struct
{
    jnode *jmap[DICTSIZE];
    strvec keys;
} jdict;

int jdput(jdict *dict, char *key, jval);
jval jdget(jdict *dict, char *key);
int jdrm(jdict *dict, char *key);
int jdprint(jdict *dict);

#endif // _JDICT_H_