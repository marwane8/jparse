#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "str_vector.h"
#include "json_parse.h"

void init_json_token(json_token *token)
{
    token->type = tkn_error;
    int rc = strv_init(&token->value);
    if (rc < 0)
    {
        exit(1);
    }
}

u8 is_space(char c)
{
    return ((c == ' ') || (c == '\t') || (c == '\n') || (c == '\r'));
}

u8 is_delimeter(char c)
{
    return strchr("{}[],;:", c) > 0;
}

char parse_next(json_parser *parser)
{
    if (parser->error_code != 0)
    {

        char msg[32];
        sprintf(msg, "parse error: index (%llu)", parser->index);
        LOGERROR(msg);
        exit(1);
    }
    if (parser->index < parser->size)
    {
        u64 i = parser->index;
        char c = parser->buffer.string[i];
        parser->index++;
        return c;
    }

    parser->error_code = -1;
    LOGERROR("parse error: end of buffer");
    return -1;
}

json_token get_next_token(json_parser *parser)
{
    json_token tkn;
    init_json_token(&tkn);
    char c;

    if (parser->index >= parser->size)
    {
        tkn.type = tkn_eof;
        return tkn;
    }

    while ((c = parse_next(parser)) > 0)
    {

        if (is_space(c))
            continue;
        else if (strchr("{}[],;:", c) > 0)
        {
            tkn.type = c;
            strv_addc(&tkn.value, c);
            return tkn;
        }
        else if (c == '"')
        {
            tkn.type = tkn_string;
            while ((c = parse_next(parser)) >= 0 && c != '"')
            {
                strv_addc(&tkn.value, c);
            }
            return tkn;
        }
        else if (strchr("-0123456789", c) > 0)
        {
            tkn.type = tkn_number;
            strv_addc(&tkn.value, c);
            while ((c = parse_next(parser)) >= 0 && strchr("-01233456789.eE", c))
            {
                strv_addc(&tkn.value, c);
            }
            if (!is_space(c) || c != ',')
            {
                tkn.type = tkn_error;
                parser->error_code = -1;
                return tkn;
            }
            parser->index--;
            return tkn;
        }
        // TODO Parse key words
    }

    return tkn;
}

// check which structure is being parsed
typedef enum _json_structure_
{
    none,
    json_object,
    json_list
} json_struct;

void parse_json_object(json_parser *parser, json_node *node);
json_node *parse_json_node(json_parser *parser, json_node *node, json_token token, json_struct curr_struct)
{
    if (parser->error_code != 0)
    {
        return NULL;
    }

    if (curr_struct == json_object && token.type == tkn_close_brace)
        return node;

    if (curr_struct == json_list && token.type == tkn_close_bracket)
        return node;

    if (token.type == tkn_open_brace)
    {

        json_node *obj_node = calloc(1, sizeof(json_node));
        parse_json_object(parser, obj_node);
        if (node == NULL) // this is the root node
        {
            return obj_node;
        }
        node->json_child = obj_node;
    }
    else if (token.type == tkn_open_bracket)
    {
        json_node *list_node = calloc(1, sizeof(json_node));
        if (node == NULL) // this is the root node
        {
            return list_node;
        }
        node->json_child = list_node;
    }
    else if (
        token.type == tkn_string ||
        token.type == tkn_number ||
        token.type == tkn_true ||
        token.type == tkn_false ||
        token.type == tkn_null)
    {
        node->value = token.value;
        json_token next_tkn = get_next_token(parser);
        parse_json_node(parser, node, next_tkn, curr_struct);
    }
    else if (token.type == tkn_comma)
    {
        json_token next_tkn = get_next_token(parser);
        json_node *next_node = calloc(1, sizeof(json_node));
        parse_json_node(parser, next_node, next_tkn, curr_struct);
        node->json_child = next_node;
    }

    return node;
}

void parse_json_object(json_parser *parser, json_node *node)
{
    json_token tkn_start, tkn_mid, tkn_next;

    tkn_start = get_next_token(parser);
    tkn_mid = get_next_token(parser);

    if (
        tkn_start.type != tkn_string ||
        tkn_mid.type != tkn_colon)
    {
        LOGERROR("invalid object token sequence");
        node = NULL;
        parser->error_code = -1;
        return;
    }

    node->key = tkn_start.value;
    tkn_next = get_next_token(parser);
    parse_json_node(parser, node, tkn_next, json_object);
}

json_node *parse_json(svec buffer)
{
    json_parser parser = {
        .buffer = buffer,
        .size = buffer.size,
        .index = 0,
        .error_code = 0};

    json_token init_tkn = get_next_token(&parser);
    json_node *node = parse_json_node(&parser, NULL, init_tkn, none);
    return node;
}

void log_json_node(json_node *n, u16 depth)
{
    char tabs[depth];
    for (int i = 0; i < depth; i++)
    {
        tabs[i] = ' ';
    }
    if (n == NULL)
    {
        printf("%s--\n", tabs);
        return;
    }

    printf("%skey: %s, val: %s\n", tabs, n->key.string, n->value.string);
    if (n->json_child != NULL)
    {
        printf("%s{", tabs);
        log_json_node(n->json_child, ++depth);
        printf("%s}", tabs);
    }
    if (n->json_next != NULL)
    {
        printf("%s[", tabs);
        log_json_node(n->json_next, depth);
        printf("%s]", tabs);
    }
}

json_node try_parse(json_parser *prs)
{
    json_node nd;
    json_token tkn = get_next_token(prs);
    nd.key = tkn.value;
    nd.value = tkn.value;
    return nd;
}