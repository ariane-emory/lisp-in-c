#ifndef TOKEN_H
#define TOKEN_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

const unsigned int MAX_TOKENS = 10000;

typedef enum TokenType {
    TOK_EOF,
    ILLEGAL,

    IDENT,
    INT,

    ADD,
    SUB,
    MUL,
    QUO,
    MOD,

    LPAREN,
    RPAREN,

    LET
} TokenType;

static const char* TOKEN_TYPE_STR[] = {
        [TOK_EOF] = "<EOF>",
        [ILLEGAL] = "<ILLEGAL>",
        [IDENT] = "<IDENT>",
        [INT] = "<INT>",
        [ADD] = "+",
        [SUB] = "-",
        [MUL] = "*",
        [QUO] = "/",
        [MOD] = "%",
        [LPAREN] = "(",
        [RPAREN] = ")",
        [LET] = "let"
};

typedef struct {
    TokenType type;
    char *lit;
} Token;

Token new_token(TokenType type, char *lit);
char *token_to_str(Token *self);

typedef struct {
    int pos;
    Token *tokens;
} TokenStream;

TokenStream *new_token_stream(Token *tokens);
Token *tok_next(TokenStream *self);
Token *tok_peek(TokenStream *self);

#endif
