#include "lex.h"
#include "util.h"

bool is_whitespace(char c) {
    IN();

    bool r = c == ' ' || c == '\t' || c == '\f' || c == '\v';

    OUT();
    return r;
}

Token read_number(File *src) {
    IN();
    
    char c;
    int idx = 0;
    char n[32] = "";
    while ((isdigit(c = file_peek(src)))) {
        if (strlen(n) == 31) {
            Token tok = tok;

            OUT();
            return tok; 
        }
        n[idx++] = c;
        file_next(src);
    }
    n[idx] = 0;
    char *num = calloc(32, sizeof(char));
    strcpy(num, n);
    Token tok = new_token(TOK_INT, num);

    OUT();
    return tok;
}

Token read_ident(File *src) {
    IN();
    
    int idx = 0;
    char ident[256] = "";
    char c;
    while (isalnum(c = file_peek(src)) || c == '_') {
        if (strlen(ident) == 255) {
            Token tok =  new_token(TOK_ILLEGAL, (char *) TOKEN_TYPE_STR[TOK_ILLEGAL]);

            OUT();
            return tok;
        }
        ident[idx++] = c;
        file_next(src);
    }
    char *id = calloc(strlen(ident) + 1,sizeof(char));
    strcpy(id, ident);
    Token tok = (strcmp(ident, TOKEN_TYPE_STR[TOK_LET]) == 0)
        ? new_token(TOK_LET, (char *) TOKEN_TYPE_STR[TOK_LET])
        : new_token(TOK_IDENT, id);

    OUT();
    return tok;
}

TokenStream *lex(File *src) {
    IN();

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

    TokenStream * tokens;
    LOGCALLOC(tokens, TokenStream, 1);
    LOGCALLOC(tokens->tokens, Token, 1 + idx);

    for (size_t ix = 0; ix < (1 + idx); ix++) {
        INFO("Copying item %zu.", ix);
        token_copy(&tokens->tokens[ix], &t[ix]);
    }
    
    //memcpy(tokens->tokens, t, sizeof(Token) * (1 + idx));

    OUT();
    return tokens; // new_token_stream(tokens);
}
