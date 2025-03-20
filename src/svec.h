#ifndef _SVEC_H_
#define _SVEC_H_

#include "macros.h"

typedef struct
{
    char *string;
    int size;
} svec;

void svinit(svec *vec);
char *svadd(svec *vec, char *string);
char *svget(svec vec);
int svfree(svec *vec);
void svlog(svec vec);

#endif // _STRVEC_H_