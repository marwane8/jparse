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

    return strchr(" \t\n\r", c) > 0;
}

u8 is_delimeter(char c)
{
    return strchr("{}[],;:", c) > 0;
}

char parse_next(json_parser *parser)
{
    if (parser->error_code != 0)
    {
        LOGERROR("parse error: index (%llu)", parser->index);
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
        parser->error_code = -1;
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

            parser->index--;
            return tkn;
        }
        // TODO Parse key words
    }

    return tkn;
}

json_node *parse_json_list(json_parser *parser, json_token start_tkn, json_token_type end_type, u8 add_label);
json_node *parse_json_node(json_parser *parser, str_vec key_value, json_token token)
{

    u8 valid = true;

    json_node *child_node = NULL;

    if (token.type == tkn_open_bracket)
    {
        child_node = parse_json_list(parser, token, tkn_close_bracket, false);
    }
    else if (token.type == tkn_open_brace)
    {
        child_node = parse_json_list(parser, token, tkn_close_brace, true);
    }

    else if (
        token.type == tkn_string ||
        token.type == tkn_number ||
        token.type == tkn_true ||
        token.type == tkn_false ||
        token.type == tkn_null)
    {
        // set data at end;
    }
    else
    {
        valid = false;
    }
    json_node *node = NULL;
    if (valid)
    {
        node = (json_node *)malloc(sizeof(json_node));
        node->key = key_value;
        node->value = token.value;
        node->json_child = child_node;
        node->json_next = NULL;
    }
    return node;
}

json_node *parse_json_list(json_parser *parser, json_token start_tkn, json_token_type end_type, u8 has_key)
{

    json_node *first_node = NULL;
    json_node *last_node = NULL;

    while (parser->error_code == 0)
    {
        str_vec key_value = {};
        json_token value = get_next_token(parser);
        if (has_key)
        {
            if (value.type == tkn_string)
            {
                strv_init(&key_value);
                key_value = value.value;
                json_token colon = get_next_token(parser);

                if (colon.type == tkn_colon)
                {
                    value = get_next_token(parser);
                }
                else
                {
                    LOGERROR("parsing error: expected colon token - '%s'", strv_get(colon.value));
                    parser->error_code = -1;
                }
            }
            else if (value.type != end_type)
            {
                LOGERROR("parsing error: unexpected toke in json - '%s'", strv_get(value.value));
                parser->error_code = -1;
            }
        }

        json_node *node = parse_json_node(parser, key_value, value);
        if (node)
        {
            if (first_node == NULL)
            {
                first_node = last_node = node;
            }
            else
            {
                last_node->json_next = node;
                last_node = node;
            }
        }
        else if (value.type == end_type)
        {
            break;
        }
        else
        {
            LOGERROR("parsing error: unexpected toke in json - '%s'", strv_get(value.value));
            parser->error_code = -1;
        }

        json_token comma = get_next_token(parser);
        if (comma.type == end_type)
        {
            break;
        }

        else if (comma.type != tkn_comma)
        {
            LOGERROR("parsing error: unexpected toke in json - '%s'", strv_get(value.value));
            parser->error_code = -1;
        }
    }
    return first_node;
}

json_node *parse_json(str_vec buffer)
{
    json_parser parser = {
        .buffer = buffer,
        .size = buffer.size,
        .index = 0,
        .error_code = 0};

    str_vec init_key = {};
    json_node *root = parse_json_node(&parser, init_key, get_next_token(&parser));
    return root;
}

void log_json(json_node *n, u16 depth)
{
    char tabs[depth];
    for (int i = 0; i < depth; i++)
    {
        tabs[i] = ' ';
    }
    printf("%s(%s : %s)\n", tabs, n->key.string, n->value.string);
    if (n->json_child != NULL)
    {
        log_json(n->json_child, ++depth);
    }

    json_node *next = n;
    while ((next = next->json_next) != NULL)
    {
        printf("%s(%s : %s)\n", tabs, next->key.string, next->value.string);
        if (next->json_child != NULL)
        {
            log_json(next->json_child, ++depth);
        }
    }
}

void tokenize_full_json(str_vec buffer)
{

    json_parser parser = {
        .buffer = buffer,
        .size = buffer.size,
        .index = 0,
        .error_code = 0};

    json_token token;
    while ((token = get_next_token(&parser)).type > 0)
    {
        char *value = strv_get(token.value);
        printf("(%s) ", value);
    }
}