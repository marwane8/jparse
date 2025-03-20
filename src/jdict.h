#ifndef _JDICT_H_
#define _JDICT_H_

#define JBUFFER 5
#define JSON_KEY_MAX 100

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

typedef struct jobj
{
    char key[JSON_KEY_MAX];
    jtype type;
    jval value;
} jobj;

int jput_int(jobj *obj, char *key, int number);
int jput_float(jobj *obj, char *key, float number);
char *jsrlz(jobj *obj);

// TODO
// jval jget(jdict *dict, char *key);
// int jdel(jdict *dict, char *key);
// jdict *jput_string(jdict *dict, char *word);

#endif // _JDICT_H_