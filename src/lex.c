#include "lex.h"

#define IN() printf("Enter %s at %s:%u.\n", __FUNCTION__, __FILE__, __LINE__);
#define OUT() printf("Leave %s at %s:%u.\n", __FUNCTION__, __FILE__, __LINE__);
#define INFO(x) printf("%s in %s at %s:%u.\n", x, __FUNCTION__, __FILE__, __LINE__);
#define LOGCALLOC(x, y)                                                         \
    (printf("Allocating %zu bytes for %zu objs of size %zu.\n", (long)((x) * (y)), (long)(x), (long)(y)), calloc((x), (y)))

bool is_whitespace(char c) {
    return c == ' ' || c == '\t' || c == '\f' || c == '\v';
}

Token read_number(File *src) {
    char c;
    int idx = 0;
    char n[32] = "";
    while ((isdigit(c = file_peek(src)))) {
        if (strlen(n) == 31) {
            return new_token(TOK_ILLEGAL, (char *) TOKEN_TYPE_STR[TOK_ILLEGAL]);
        }
        n[idx++] = c;
        file_next(src);
    }
    n[idx] = 0;
    char *num = calloc(32, sizeof(char));
    strcpy(num, n);
    return new_token(TOK_INT, num);
}

Token read_ident(File *src) {
    int idx = 0;
    char ident[256] = "";
    char c;
    while (isalnum(c = file_peek(src)) || c == '_') {
        if (strlen(ident) == 255) {
            return new_token(TOK_ILLEGAL, (char *) TOKEN_TYPE_STR[TOK_ILLEGAL]);
        }
        ident[idx++] = c;
        file_next(src);
    }
    char *id = calloc(strlen(ident) + 1,sizeof(char));
    strcpy(id, ident);
    return (strcmp(ident, TOKEN_TYPE_STR[TOK_LET]) == 0)
           ? new_token(TOK_LET, (char *) TOKEN_TYPE_STR[TOK_LET])
           : new_token(TOK_IDENT, id);
}

TokenStream *lex(File *src) {
    Token t[MAX_TOKENS];
    memset(t, 0, MAX_TOKENS*sizeof(Token));
    char c;
    int idx = 0;
    while ((c = file_peek(src)) != EOF) {
//        printf("char: %c\n", c);
        switch (c) {
            case '+':
                t[idx++] = new_token(TOK_ADD, (char *) TOKEN_TYPE_STR[TOK_ADD]);
                file_next(src);
                break;
            case '-':
                t[idx++] = new_token(TOK_SUB, (char *) TOKEN_TYPE_STR[TOK_SUB]);
                file_next(src);
                break;
            case '*':
                t[idx++] = new_token(TOK_MUL, (char *) TOKEN_TYPE_STR[TOK_MUL]);
                file_next(src);
                break;
            case '/':
                t[idx++] = new_token(TOK_QUO, (char *) TOKEN_TYPE_STR[TOK_QUO]);
                file_next(src);
                break;
            case '%':
                t[idx++] = new_token(TOK_MOD, (char *) TOKEN_TYPE_STR[TOK_MOD]);
                file_next(src);
                break;
            case '(':
                t[idx++] = new_token(TOK_LPAREN, (char *) TOKEN_TYPE_STR[TOK_LPAREN]);
                file_next(src);
                break;
            case ')':
                t[idx++] = new_token(TOK_RPAREN, (char *) TOKEN_TYPE_STR[TOK_RPAREN]);
                file_next(src);
                break;
            default:
                if (is_whitespace(c)) {
                    file_next(src);
                } else if (isdigit(c)) {
                    t[idx++] = read_number(src);
                } else if (isalpha(c) || c == '_') {
                    t[idx++] = read_ident(src);
                } else {
                    t[idx++] = new_token(TOK_ILLEGAL, &c);
                    file_next(src);
                }
                break;
        }
    }
    
    t[idx] = new_token(TOK_EOF, (char *) TOKEN_TYPE_STR[TOK_EOF]);
    
    IN();
    for (size_t ix = 0; ix < idx; ix++)
        printf("T %zu => %s\n", ix, token_to_str(&t[ix]));
            
    TokenStream * tokens = LOGCALLOC(1, sizeof(TokenStream));
    tokens->tokens = LOGCALLOC(idx+0, sizeof(Token));

    /* for (size_t ix = 0; ix < idx; ix++) { */
    /*     printf("\nIX = %zu\n", ix); */
    /*     printf("Copying %s.\n", token_to_str(&t[ix])); */
    /*     tokens->tokens[ix].type = t[ix].type; */
    /*     INFO("Tick"); */
    /*     strlen(t[ix].lit); */
    /*     INFO("Did strlen"); */
    /*     tokens->tokens[ix].lit = calloc(1 + strlen(t[ix].lit), sizeof(char)); */
    /*     INFO("Tock"); */
    /*     strcpy(tokens->tokens[ix].lit, t[ix].lit); */
    /*     INFO("Tack"); */
    /* } */
    
//    memcpy(tokens, t, (idx+0)*sizeof(Token));
    OUT();
    return tokens; // new_token_stream(tokens);
}
