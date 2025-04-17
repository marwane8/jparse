#ifndef _JSON_PARSE_
#define _JSON_PARSE_

#include "util.h"
#include "str_vector.h"

typedef enum _json_token_type_
{
    tkn_error = -1,
    tkn_eof = 0,
    tkn_string,
    tkn_number,
    tkn_true,
    tkn_false,
    tkn_null,
    tkn_colon = ':',
    tkn_comma = ',',
    tkn_open_bracket = '[',
    tkn_close_bracket = ']',
    tkn_open_brace = '{',
    tkn_close_brace = '}'
} json_token_type;

// check which structure is being parsed
typedef enum _json_structure_
{
    none,
    json_object,
    json_list,
    json_value,
    json_string,
} json_struct;

typedef struct _json_token_
{
    json_token_type type;
    str_vec value;
} json_token;

typedef struct _json_node_
{
    json_struct struct_type;
    str_vec key;
    str_vec value;
    struct _json_node_ *json_child; // nested json
    struct _json_node_ *json_next;  // next json
} json_node;

typedef struct _json_parser_
{
    str_vec buffer;
    u64 index;
    u64 size;
    u8 error_code;
} json_parser;

json_node *lookup_node(json_node *n, char *key);
json_node *parse_json(str_vec buffer);
void print_node(json_node *n);
void log_json(json_node *n, u16 depth);

// test functions
void tokenize_full_json(str_vec buffer);

#endif // _JSON_PARSE_