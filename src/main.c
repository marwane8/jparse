#include <stdio.h>
#include <stdlib.h>
#include "tokenizer.h"

int main(int argc, char *argv[])
{
    FILE *file;

    if (argc < 1)
    {
        printf("No input file provided");
    }

    file = fopen(argv[1], "r");
    if (file == NULL)
    {
        perror("main.c file error");
        exit(EXIT_FAILURE);
        return 1;
    }
    int c;
    tokenizer tkzr = {0};

    printf("It worked");
}