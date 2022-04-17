#include <stdio.h>

/*
 * Tokens
 */

typedef enum {
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

typedef struct {
    TokenType type;
    char* lit;
} Token;

/*
 * Lexer
 */

Token* lex(char* str) {

}

/*
 * Ast
 */

typedef enum {
    Atom,
    List
} Sexpr;

/*
 * Parser
 */

Sexpr parse(Token* tokens) {

}

int main() {
    printf("Hello, World!\n");
    return 0;
}
