#ifndef _TOKENIZER_H_
#define _TOKENIZER_H_

#include "svec.h"


typedef struct {
    int quotes;
    int curly; 
    int colons;
    char *tkn;
    svec tokens;
} tokenizer;


int tokenize(tokenizer *tkzr, FILE *file);


#endif // _TOKENIZER_H_