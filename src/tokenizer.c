#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "tokenizer.h"
#include "svec.h"

char *addchar(char *dest, char ch)
{
    int len = (dest == NULL) ? 2 : strlen(dest) + 2;
    dest = realloc(dest, len);
    if (!dest)
    {
        perror("addchar allocation error: ");
        exit(1);
    }
    dest[len - 2] = ch;
    dest[len - 1] = '\0';
    return dest;
}

int tokenize(tokenizer *tkzr, FILE *file)
{
    int c = 0;
    while ((c = fgetc(file)) != EOF)
    {
        char *token = NULL;
        if (c == '{')
        {
            if (0 != tkzr->curly)
            {
                fprintf(stderr, "Out of bound character: { ");
                return -1;
            }
            ++tkzr->curly;
            token = addchar(token, (char)c);
        }
        else if (c == '"')
        {
            int wch = fgetc(file); // start counting word characters
            while (wch != '"' && wch != EOF)
            {
                token = addchar(token, (char)wch);
                wch = fgetc(file);
            }
        }
        else if (c == ':')
        {
            ++tkzr->colons;
            token = addchar(token, (char)c);
        }

        else if (c == '}')
        {
            if (1 != tkzr->curly)
            {
                fprintf(stderr, "Out of bound character: } ");
                return -1;
            }
            --tkzr->curly;
            token = addchar(token, (char)c);
        }
        else if (c == ',' || c == '[' || c == ']')
        {
            token = addchar(token, (char)c);
        }

        if (token)
            svadd(&tkzr->tokens, token);
    }
    svlog(tkzr->tokens);
    return 0;
}
