#ifndef _JDICT_H_
#define _JDICT_H_

#define JBUFFER 5
#define MAX_KEY_LENGTH 100

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
    char key[100];
    jtype type;
    jval value;
} jnode;

typedef struct
{
    jnode *nodes;
    size_t len;
    size_t size;
} jdict;

jdict *jinit();
jdict *jput_int(jdict *dict, char *key, int number);
jdict *jput_float(jdict *dict, char *key, float number);

void jprint(jdict *dict);

// TODO
// jval jget(jdict *dict, char *key);
// int jdel(jdict *dict, char *key);
// jdict *jput_string(jdict *dict, char *word);

#endif // _JDICT_H_