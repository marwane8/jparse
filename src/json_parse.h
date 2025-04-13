#ifndef _JSON_PARSE_
#define _JSON_PARSE_

#include "str_vector.h"
#include "macros.h"

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

typedef struct _json_token_
{
    json_token_type type;
    svec value;
} json_token;

typedef struct _json_node_
{
    svec key;
    svec value;
    struct _json_node_ *json_child; // nested json
    struct _json_node_ *json_next;  // next json
} json_node;

typedef struct _json_parser_
{
    svec buffer;
    u64 index;
    u64 size;
    u8 error_code;
} json_parser;

#endif // _JSON_PARSE_