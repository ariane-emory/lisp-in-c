#include "token.h"

static const unsigned int MAX_TOKENS = 10000;

Token new_token(TokenType type, char *lit) {
    Token tok;
    tok.type = type;
    tok.lit = lit;
    return tok;
}

char *token_to_str(Token *self) {
    static char str_tmp[500] = "";
    snprintf(
            str_tmp,
            500,
            "Token { Type: %s, Lit: %s }",
            TOKEN_TYPE_STR[self->type],
            self->lit);

    char *tok_str = calloc(strlen(str_tmp) + 1, sizeof(char));

    strcpy(tok_str, str_tmp);

    return tok_str;
}

TokenStream *new_token_stream(Token *tokens) {
    TokenStream *self = calloc(1, sizeof(TokenStream));
    self->pos = 0;
    self->tokens = tokens;
    return self;
}

Token *tok_next(TokenStream *self) {
    return &self->tokens[self->pos++];
}

Token *tok_peek(TokenStream *self) {
    return &self->tokens[self->pos+1];
}