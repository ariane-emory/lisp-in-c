#include "lex.h"

bool is_whitespace(char c) {
    return c == ' ' || c == '\t' || c == '\f' || c == '\v';
}

Token read_number(File *src) {
    char c;
    int idx = 0;
    char n[31] = "";
    while ((isdigit(c = file_peek(src)))) {
        if (strlen(n) >= 31) {
            return new_token(ILLEGAL, (char *) TOKEN_TYPE_STR[ILLEGAL]);
        }
        n[idx++] = c;
        file_next(src);
    }
    char *num = calloc(31, sizeof(char));
    strcpy(num, n);
    return new_token(INT, num);
}

Token read_ident(File *src) {
    int idx = 0;
    char ident[256] = "";
    char c;
    while (isalnum(c = file_peek(src)) || c == '_') {
        if (strlen(ident) >= 256) {
            return new_token(ILLEGAL, (char *) TOKEN_TYPE_STR[ILLEGAL]);
        }
        ident[idx++] = c;
        file_next(src);
    }
    char *id = calloc(strlen(ident) + 1,sizeof(char));
    strcpy(id, ident);
    return (strcmp(ident, TOKEN_TYPE_STR[LET]) == 0)
           ? new_token(LET, (char *) TOKEN_TYPE_STR[LET])
           : new_token(IDENT, id);
}

TokenStream *lex(File *src) {
    Token t[MAX_TOKENS];
    char c;
    int idx = 0;
    while ((c = file_peek(src)) != EOF) {
//        printf("char: %c\n", c);
        switch (c) {
            case EOF:
                t[idx] = new_token(TOK_EOF, (char *) TOKEN_TYPE_STR[EOF]);
                break;
            case '+':
                t[idx++] = new_token(ADD, (char *) TOKEN_TYPE_STR[ADD]);
                file_next(src);
                break;
            case '-':
                t[idx++] = new_token(SUB, (char *) TOKEN_TYPE_STR[SUB]);
                file_next(src);
                break;
            case '*':
                t[idx++] = new_token(MUL, (char *) TOKEN_TYPE_STR[MUL]);
                file_next(src);
                break;
            case '/':
                t[idx++] = new_token(QUO, (char *) TOKEN_TYPE_STR[QUO]);
                file_next(src);
                break;
            case '%':
                t[idx++] = new_token(MOD, (char *) TOKEN_TYPE_STR[MOD]);
                file_next(src);
                break;
            case '(':
                t[idx++] = new_token(LPAREN, (char *) TOKEN_TYPE_STR[LPAREN]);
                file_next(src);
                break;
            case ')':
                t[idx++] = new_token(RPAREN, (char *) TOKEN_TYPE_STR[RPAREN]);
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
                    t[idx] = new_token(ILLEGAL, &c);
                    file_next(src);
                }
                break;
        }
    }
    Token *tokens = calloc(idx+1, sizeof(Token));
    memcpy(tokens, t, (idx+1)*sizeof(Token));
    return new_token_stream(tokens);
}