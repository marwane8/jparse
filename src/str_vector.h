#ifndef _SVEC_H_
#define _SVEC_H_

typedef struct
{
    char *string;
    int size;
} svec;

int strv_init(svec *vec);
char *strv_add(svec *vec, char *string);
char *strv_addc(svec *vec, char ch);
char *strv_get(svec vec);
char strvi(svec vec, int i); // character at index ;
int strv_free(svec *vec);
void strv_log(svec vec);

#endif // _SVEC_H_