#ifndef _STR_VEC_H_
#define _STR_VEC_H_

typedef struct
{
    char *string;
    int size;
} str_vec;

int strv_init(str_vec *vec);
char *strv_add(str_vec *vec, char *string);
char *strv_addc(str_vec *vec, char ch);
char *strv_get(str_vec vec);
char strvi(str_vec vec, int i); // character at index ;
int strv_free(str_vec *vec);
void strv_log(str_vec vec);

#endif // _STR_VEC_H_