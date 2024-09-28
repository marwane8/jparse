#include <stdio.h>
#include "tokenizer.h"
#include "strvec.h"

int tokenize(tokenizer *tkzr, int ch)
{
    if (ch == '{')
    {
        if (0 != tkzr->curly)
        {
            fprintf(stderr, "Out of bound character: { ");
            return -1;
        }

        ++tkzr->curly;
        // convert curly to string;
        char str[2];
        str[0] = ch;
        svpush(&tkzr->tokens, str);
        return 0;
    }

    if (ch == '}')
    {

        if (1 != tkzr->curly)
        {
            fprintf(stderr, "Out of bound character: } ");
            return -1;
        }

        --tkzr->curly;
        // convert curly to string;
        char str[2];
        str[0] = ch;
        svpush(&tkzr->tokens, str);
        return 0;
    }

    printf("Current tokens: ");
    svprint(tkzr->tokens);
    return 0;

}