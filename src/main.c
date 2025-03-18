#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tokenizer.h"
#include "jdict.h"

// test entry
int main()
{

    jdict *json = jinit();
    jput_int(json, "age", 34);
    jput_float(json, "balance", 1024.32);
    jprint(json);
}

// int main(int argc, char *argv[])
// {

//     FILE *file;

//     if (argc < 1)
//     {
//         printf("No input file provided");
//     }

//     file = fopen(argv[1], "r");
//     if (file == NULL)
//     {
//         perror("main.c file error");
//         exit(EXIT_FAILURE);
//         return 1;
//     }

//     // application starting point
//     tokenizer tkzr = {0};
//     tokenize(&tkzr, file);
//     fclose(file);

//     int num = 20;
//     void *ptr = num;

//     jval jvl1 = {.type = INT, .value = };
//     char *word = "Timmy, Im very old!";
//     char *w1 = (char *)calloc(strlen(word) + 1, sizeof(char));
//     strcpy(w1, word);

//     jval jvl2 = {
//         .type = STRING,
//         .value = w1};

//     jdput(&JDICT, "age", jvl1);
//     jdput(&JDICT, "name", jvl2);
//     jdprint(&JDICT);
// }
