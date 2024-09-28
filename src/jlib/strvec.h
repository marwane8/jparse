#ifndef _STRVEC_H_
#define _STRVEC_H_

typedef struct
{
    int length;
    int capacity;
    char **list;
} strvec;

int svpush(strvec *vector, char *string);
char *svpop(strvec *vector);
char *svat(strvec *vector, size_t i);
int svrm(strvec *vector, size_t i);
void svprint(strvec vector);

#endif // _STRVEC_H_