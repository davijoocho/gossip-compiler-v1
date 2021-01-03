#ifndef TOKEN_H
#define TOKEN_H

#include <stdlib.h>

enum token_type
{
    LEFT_PAREN, RIGHT_PAREN, LEFT_BRACE, RIGHT_BRACE,
    MINUS, PLUS, SEMICOLON, SLASH, ASTERISK,


    BANG, BANG_EQUAL, EQUAL, EQUAL_EQUAL, GREATER, GREATER_EQUAL,
    LESS, LESS_EQUAL,

    ARROW,

    INT, IDENTIFIER,

    AND, ELSE, INSTRUCTN, FOR, IF, OR, OUTPUT, RETURN, WHILE, 

    EOF_F
};

struct token
{
    enum token_type tag;
    union
    {
        char* string_v;
        int int_v;
    };
};

struct token_vector
{
    int pos;
    int n_items;
    int max_length;
    struct token* vec;
};

struct token_vector* construct_vector (); // malloc and ret pointer - free token_vector and vec
void add_token (struct token_vector* tkn_vec, enum token_type type, void* value); // realloc when n_items = max_length

#endif
