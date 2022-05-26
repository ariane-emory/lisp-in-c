#include "lex.h"
#include "util.h"

bool is_whitespace(char c) {
    return c == ' ' || c == '\t' || c == '\f' || c == '\v';
}

Token * read_number(FILE *src) {
    IN();
    
    char c;
    int idx = 0;
    char n[32] = "";
    while ((strlen(n) < 31) && (isdigit(c = file_peek(src)))) {
        n[idx++] = c;
        file_next(src);
    }
    n[idx] = 0;
    
    char * num;
    LOGCALLOC(num, char, (1 + strlen(n)));
    
    strcpy(num, n);

    Token * tok = new_token(TOK_INT, num);

    OUT();
    return tok;
}

Token * read_ident(FILE *src) {
    IN();
    
    int idx = 0;
    char ident[256] = "";
    char c;
    while ((strlen(ident) < 255) && isalnum(c = file_peek(src)) || c == '_') {
        ident[idx++] = c;
        file_next(src);
    }
    char * id = calloc(strlen(ident) + 1,sizeof(char));
    strcpy(id, ident);
    Token * tok = (strcmp(ident, TOKEN_TYPE_STR[TOK_LET]) == 0)
        ? new_token(TOK_LET, (char *) TOKEN_TYPE_STR[TOK_LET])
        : new_token(TOK_IDENT, id);

    OUT();

    return tok;
}

TokenStream *lex(FILE *src) {
    IN();

#define PUSH_TOKEN(index, token)                                                \
    t[index] = token;                                                           \
    INFO("Pushed token %p to index %u", t[index], index);                       \
    index++
    
    Token ** t;
    LOGCALLOC(t, Token *, MAX_TOKENS);

    char c;
    int idx = 0;
    while ((c = file_peek(src)) != (char)EOF) {
        INFO("char: %c", c);
        switch (c) {
        case '+':
            PUSH_TOKEN(idx, new_token(TOK_ADD, (char *) TOKEN_TYPE_STR[TOK_ADD]));
            file_next(src);
            break;
        case '-':
            PUSH_TOKEN(idx, new_token(TOK_SUB, (char *) TOKEN_TYPE_STR[TOK_SUB]));
            file_next(src);
            break;
        case '*':
            PUSH_TOKEN(idx, new_token(TOK_MUL, (char *) TOKEN_TYPE_STR[TOK_MUL]));
            file_next(src);
            break;
        case '/':
            PUSH_TOKEN(idx, new_token(TOK_QUO, (char *) TOKEN_TYPE_STR[TOK_QUO]));
            file_next(src);
            break;
        case '%':
            PUSH_TOKEN(idx, new_token(TOK_MOD, (char *) TOKEN_TYPE_STR[TOK_MOD]));
            file_next(src);
            break;
        case '(':
            PUSH_TOKEN(idx, new_token(TOK_LPAREN, (char *) TOKEN_TYPE_STR[TOK_LPAREN]));
            file_next(src);
            break;
        case ')':
            PUSH_TOKEN(idx, new_token(TOK_RPAREN, (char *) TOKEN_TYPE_STR[TOK_RPAREN]));
            file_next(src);
            break;
        default:
            if (is_whitespace(c)) {
                file_next(src);
            } else if (isdigit(c)) {
                PUSH_TOKEN(idx, read_number(src));
            } else if (isalpha(c) || c == '_') {
                PUSH_TOKEN(idx, read_ident(src));
            } else {
                char * buf;
                LOGCALLOC(buf, char, 2);
                snprintf(buf, 2, "%c", c);
                PUSH_TOKEN(idx, new_token(TOK_ILLEGAL, buf));
                file_next(src);
            }
            break;
        }
    }
    
    PUSH_TOKEN(idx, new_token(TOK_EOF, (char *) TOKEN_TYPE_STR[TOK_EOF]));

    TokenStream * tokens;
    LOGCALLOC(tokens, TokenStream, 1);
    LOGCALLOC(tokens->tokens, Token, idx);

    for (size_t ix = 0; ix < idx; ix++) {
        INFO("Copying item %zu.", ix);
        LOGCALLOC(tokens->tokens[ix], Token , 1);
        token_copy(tokens->tokens[ix], t[ix]);
    }
    
    //memcpy(tokens->tokens, t, sizeof(Token) * (1 + idx));

    OUT();
    return tokens; // new_token_stream(tokens);
#undef PUSH_TOKEN
}
