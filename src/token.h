#ifndef TOKEN_H
#define TOKEN_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

static const unsigned int MAX_TOKENS;

typedef enum TokenType {
    TOK_EOF,
    TOK_ILLEGAL,

    TOK_IDENT,
    TOK_INT,

    TOK_ADD,
    TOK_SUB,
    TOK_MUL,
    TOK_QUO,
    TOK_MOD,

    TOK_LPAREN,
    TOK_RPAREN,

    TOK_LET
} TokenType;

static const char* TOKEN_TYPE_STR[] = {
        [TOK_EOF] = "<EOF>",
        [TOK_ILLEGAL] = "<ILLEGAL>",
        [TOK_IDENT] = "<IDENT>",
        [TOK_INT] = "<INT>",
        [TOK_ADD] = "+",
        [TOK_SUB] = "-",
        [TOK_MUL] = "*",
        [TOK_QUO] = "/",
        [TOK_MOD] = "%",
        [TOK_LPAREN] = "(",
        [TOK_RPAREN] = ")",
        [TOK_LET] = "let"
};

typedef struct {
    TokenType type;
    char *lit;
} Token;

Token * new_token(TokenType type, char *lit);
char * token_to_str(Token *self);

typedef struct {
    int pos;
    Token ** tokens;
} TokenStream;

TokenStream *new_token_stream(Token ** tokens);
Token * tok_next(TokenStream *self);
Token * tok_current(TokenStream *self);

bool token_equal(Token * left, Token * right);
void token_copy(Token * dest, Token * src);

#endif
