#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>

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

char* token_pretty_str(Token* self) {
    return self->lit;
}

/*
 * Lexer
 */

Token* lex(char* src) {
    for (int i = 0; i < strlen(src); i++) {

    }
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
    return Atom;
}

/*
 * Eval
 */

/*
 * Entry point
 */

int main() {
    char cwd[PATH_MAX];
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        printf("Current working dir: %s\n", cwd);
    } else {
        perror("getcwd() error");
        return 1;
   }

    int c;
    int i = 0;
    char *src;
    snprintf(cwd, sizeof(cwd), "%s", "../examples/simple.lic");
    FILE* file = fopen(cwd, "r");
    if (file) {
        while ((c = getc(file)) != EOF) {
            src[i++] = c;
        }
        fclose(file);
    } else {
        printf("File \"%s\" does not exist!", cwd);
    }
//    printf("Source: %s", src);
    Token* tokens = lex(src);
    printf("%v", tokens);
    return 0;
}
