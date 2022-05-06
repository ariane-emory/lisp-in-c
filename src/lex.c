#include "lex.h"

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
                    t[idx] = new_token(TOK_ILLEGAL, &c);
                    file_next(src);
                }
                break;
        }
    }
    t[++idx] = new_token(TOK_EOF, (char *) TOKEN_TYPE_STR[EOF]);
    Token *tokens = calloc(idx+1, sizeof(Token));
    memcpy(tokens, t, (idx+1)*sizeof(Token));
    return new_token_stream(tokens);
}