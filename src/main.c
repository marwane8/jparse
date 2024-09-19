#include <stdio.h>

#include "strvec.h"


int main() {

    strvec vec1;

    int val1 = sv_push(&vec1, "yoo");
    char *val2 = sv_pop(&vec1);
    char *val3 = sv_at(&vec1, 2);
    int val4 = sv_rm(&vec1, 1);

    printf("The value val1 is: %d\n",val1);
    printf("The value val2 is: %s\n",val2);
    printf("The value val3 is: %s\n",val3);
    printf("The value val4 is: %d\n",val4);
}