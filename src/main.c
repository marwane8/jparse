#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "util.h"
#include "str_vector.h"
#include "json_parse.h"

int read_to_buffer(FILE *fp, str_vec *buffer)
{
    char c;
    while ((c = getc(fp)) != EOF)
    {
        strv_addc(buffer, c);
    }
    return 0;
}

int main(int argc, char *argv[])
{

    FILE *file;
    str_vec buffer;
    strv_init(&buffer);

    if (argc <= 1)
    {
        printf("\tUsage: jparse <file.json>\n");
        return 0;
    }

    char *filename = argv[1];
    file = fopen(filename, "r");
    if (file == NULL)
    {
        LOGERROR("file not found: %s", filename);
        exit(EXIT_FAILURE);
        return 1;
    }

    read_to_buffer(file, &buffer);
    tokenize_full_json(buffer); 

    json_node *JSON = parse_json(buffer);
    log_json(JSON,0);


}
