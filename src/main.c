#include <stdio.h>
#include "strvec.h"


int main()
{

    int c;

    while ((c = getchar()) != EOF)
    {
        // putchar(c);
        if (c == '\n')
        {

            printf("NEWLINE\n");
        }
        else
        {

            printf("char: %c \n", c);
        }
    }
}