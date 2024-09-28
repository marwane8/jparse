#ifndef _TOKENIZER_H_
#define _TOKENIZER_H_

#include "strvec.h"


typedef struct {
    int quotes;
    int curly; 
    int colons;
    char *tkn;
    strvec tokens;
} tokenizer;


int tokenize(tokenizer *tkzr, int ch);


#endif // _TOKENIZER_H_