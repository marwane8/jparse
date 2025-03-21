#include <stdio.h>
#include <string.h>

#define KEY_MAX 100
#define TABLE_SIZE 10

typedef struct
{
    char key[KEY_MAX];
    int value;
} s2i_map;

s2i_map *table[TABLE_SIZE];

unsigned int hash(char *key);

s2i_map *init_hash_map();
int s2i_insert(s2i_map *node);
void s2i_print();

int main()
{
    s2i_map *table = init_hash_map();
    s2i_map pair = {.key = "bob", .value = 123};
    s2i_map pair1 = {.key = "mohammed", .value = 43};
    s2i_map pair2 = {.key = "adrian", .value = 10};
    s2i_map pair3 = {.key = "hommer", .value = 2121};

    s2i_print();

    s2i_insert(&pair);
    s2i_insert(&pair1);
    s2i_insert(&pair2);
    s2i_insert(&pair3);

    s2i_print();
}

s2i_map *init_hash_map()
{

    for (size_t i = 0; i < TABLE_SIZE; i++)
    {
        table[i] = NULL;
    }
    return table;
}

unsigned int hash(char *key)
{

    int hash_value = 0;
    for (int i = 0; i < strlen(key); i++)
    {
        hash_value += key[i];
        hash_value *= key[i];
    }

    return hash_value * 7 % TABLE_SIZE;
}

int s2i_insert(s2i_map *node)
{
    if (node == NULL)
        return 1;

    int i = hash(node->key);
    printf("key %s : %i\n", node->key, i);
    if (table[i] != NULL)
    {
        return 1;
    }

    table[i] = &node;
    return 0;
}

void s2i_print()
{

    printf("== START ==\n");
    for (int i = 0; i < TABLE_SIZE; i++)
    {
        if (table[i] != NULL)
        {
            printf(" %i\t%s\n", i, table[i]->key);
        }
        else
        {
            printf(" %i\t---\n", i);
        }
    }
    printf("== END ==\n");
}