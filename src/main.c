#include <stdio.h>
#include "tokenizer.h"

int main()
{

    int c;
    tokenizer tkzr = {0};

    while ((c = getchar()) != EOF)
    {
        tokenize(&tkzr, c);
    }
}