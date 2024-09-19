#define MAXLINE 1000;

typedef struct {
    int length;
    char **vec;
} strvec;

int sv_push(strvec *vector, char *string);
char *sv_pop(strvec *vector);
char *sv_at(strvec *vector, int i);
int sv_rm(strvec *vector, int i);

