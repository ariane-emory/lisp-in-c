#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>

//=================================================================
// Helpers
//=================================================================

const unsigned long MAX_TOKENS = 10000;

typedef struct {
    FILE *file;
} File;

File *new_file(char* path) {
    File *f = malloc(sizeof(File));
    f->file = malloc(sizeof(FILE));
    f->file = fopen(path, "r");
    if (!f->file) {
        printf("Error: file \"%s\" does not exist!", path);
        exit(1);
    }
    return f;
}

char *file_to_str(File *self)
{
    char *buffer = NULL;
    long string_size;
    unsigned long read_size;
    FILE *handler = self->file;

    if (handler)
    {
        fseek(handler, 0, SEEK_END);
        string_size = ftell(handler);
        rewind(handler);
        buffer = (char*) malloc(sizeof(char) * (string_size + 1) );
        read_size = fread(buffer, sizeof(char), string_size, handler);
        buffer[string_size] = '\0';
        if (string_size != read_size)
        {
            free(buffer);
            buffer = NULL;
        }
        fclose(handler);
    }

    return buffer;
}

int file_next(File *self) {
    return fgetc(self->file);
}

int file_peek(File *self) {
    int c;
    c = fgetc(self->file);
    ungetc(c, self->file);
    return c;
}

//=================================================================
// Tokens
//=================================================================

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
        [RPAREN] = ")"
};

typedef struct {
    TokenType type;
    char *lit;
} Token;

char *token_to_str(Token *self) {
    const char *tok_type_str = TOKEN_TYPE_STR[self->type];
    char *tok_str = malloc(sizeof("Token { Type: , Lit:  }")+sizeof(tok_type_str)+sizeof(self->lit));
    snprintf(tok_str, sizeof(tok_str), "Token { Type: %s, Lit: %s }", tok_type_str, self->lit);
    printf("%s\n", tok_type_str);
    return tok_str;
}

Token new_token(TokenType type, char *lit) {
    Token tok;
    tok.type = type;
    tok.lit = lit;
    return tok;
}

//=================================================================
// Lexer
//=================================================================

bool is_whitespace(int c) {
    return c == ' ' || c == '\t' || c == '\f' || c == '\v';
}

Token read_number(File *src) {
    int c;
    char *n = malloc(4*sizeof(char));
    while ((isdigit(c = file_peek(src)))) {
        n += c;
        file_next(src);
    }
    return new_token(INT, n);
}

Token read_ident(File *src) {
    int c;
    int len = 8;
    char *ident = malloc(len*sizeof(char));
    while (isalnum(c = file_peek(src) || c == '_')) {
        if (strlen(ident) >= len) {
            len *= 2;
            ident = (char *) realloc(ident, len*sizeof(char));
        }
        ident += c;
        file_next(src);
    }
    return new_token(IDENT, ident);
}

Token *lex(File *src) {
    Token *tokens = malloc(MAX_TOKENS * sizeof(Token));
    int c;
    int i = 0;
    while ((c = file_peek(src)) != EOF) {
        printf("char: %c\n", c);
        switch (c) {
            case '+':
                tokens[i++] = new_token(ADD, TOKEN_TYPE_STR[ADD]);
                file_next(src);
            case '-':
                tokens[i++] = new_token(SUB, TOKEN_TYPE_STR[SUB]);
                file_next(src);
            case '*':
                tokens[i++] = new_token(MUL, TOKEN_TYPE_STR[MUL]);
                file_next(src);
            case '/':
                tokens[i++] = new_token(QUO, TOKEN_TYPE_STR[QUO]);
                file_next(src);
            case '%':
                tokens[i++] = new_token(MOD, TOKEN_TYPE_STR[MOD]);
                file_next(src);
            case '(':
                tokens[i++] = new_token(LPAREN, TOKEN_TYPE_STR[LPAREN]);
                file_next(src);
            case ')':
                tokens[i++] = new_token(RPAREN, TOKEN_TYPE_STR[RPAREN]);
                file_next(src);
            default:
                if (is_whitespace(c)) {
                    file_next(src);
                } else if (isdigit(c)) {
                    tokens[i++] = read_number(src);
                } else if (isalpha(c) || c == '_') {
                    tokens[i++] = read_ident(src);
                    file_next(src);
                } else {
                    char *ch = malloc(sizeof(char));
                    snprintf(ch, sizeof(char), "%c", c);
                    tokens[i] = new_token(ILLEGAL, ch);
                    file_next(src);
                }
        }
    }
    return tokens;
}

//=================================================================
// Ast
//=================================================================

typedef enum {
    Atom,
    List
} Sexpr;

//=================================================================
// Parser
//=================================================================

Sexpr parse(Token *tokens) {
    return Atom;
}

//=================================================================
// Eval
//=================================================================

int eval(Sexpr *sexpr) {
    return 0;
}

//=================================================================
// Entry Point
//=================================================================

int main() {
    char cwd[PATH_MAX];
    if (getcwd(cwd, sizeof(cwd)) == NULL) {
        perror("getcwd() error");
        return 1;
    }
    snprintf(cwd, sizeof(cwd), "%s", "../examples/simple.lic");
    File *file = new_file(cwd);
    lex(file);
//    Token* tokens = lex(file);
//    for (int i = 0; i < sizeof(*tokens); i++) {
//        printf("%s\n", token_to_str(&tokens[i]));
//    }
    return 0;
}
