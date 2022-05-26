#include "token.h"
#include "util.h"
#include <stdbool.h>

static const unsigned int MAX_TOKENS = 10000;

bool token_equal(Token * left, Token * right) {
    return ((left->type == right->type) && (left->lit == right->lit));
}

void token_copy(Token * dest, Token * src) {
    IN();
    
    INFO("Copy token @ %p to %p", src, dest);
    INFO("Copy token of type %s", TOKEN_TYPE_STR[src->type]);
    dest->type = src->type;
    dest->lit = src->lit;

    char * dstr = token_to_str(dest);
    char * sstr = token_to_str(src);
    INFO("d = '%s'", dstr);
    INFO("s = '%s'", sstr);
    free(dstr);
    free(sstr);

    OUT();
}

Token * new_token(TokenType type, char *lit) {
    IN();

    Token * tok;
    LOGCALLOC(tok, Token, 1);
    
    tok->type = type;
    tok->lit = lit;

    char * tmp = token_to_str(tok);
    INFO("Created '%s' @ %p.", tmp, tmp);
    free(tmp);

    OUT();
    return tok;
}

char *token_to_str(Token *self) {
    IN();
    INFO("type = %u", self->type);
    INFO("type_str @ %p = '%s'", TOKEN_TYPE_STR[self->type], TOKEN_TYPE_STR[self->type]);
    INFO("lit @ %p = '%s' ", self->lit, self->lit);
    
    static char str_tmp[256] = "";

    snprintf(
        str_tmp,
        256,
        "Token { Type: %s, Lit: %s }",
        TOKEN_TYPE_STR[self->type],
        self->lit);

    char *tok_str = calloc(strlen(str_tmp) + 1, sizeof(char));

    strcpy(tok_str, str_tmp);

    OUT();
    return tok_str;
}

TokenStream * new_token_stream(Token ** tokens) {
    TokenStream *self = calloc(1, sizeof(TokenStream));
    self->pos = 0;
    self->tokens = tokens;
    return self;
}

Token * tok_next(TokenStream *self) {
    return self->tokens[self->pos++];
}

Token * tok_current(TokenStream *self) {
    return self->tokens[self->pos];
}
