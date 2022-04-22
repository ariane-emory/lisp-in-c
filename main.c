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

const unsigned int MAX_TOKENS = 10000;

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

char file_peek(File *self) {
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
        [RPAREN] = ")",
        [LET] = "let"
};

typedef struct {
    TokenType type;
    char *lit;
} Token;

Token new_token(TokenType type, char *lit) {
    Token tok;
    tok.type = type;
    tok.lit = lit;
    return tok;
}

char *token_to_str(Token *self) {
    static char str_tmp[256] = "";
    snprintf(
            str_tmp,
            256,
            "Token { Type: %s, Lit: %s }",
            TOKEN_TYPE_STR[self->type],
            self->lit);

    char *tok_str = calloc(strlen(str_tmp) + 1,sizeof(char));

    strcpy(tok_str, str_tmp);

    return tok_str;
}

//=================================================================
// Lexer
//=================================================================

bool is_whitespace(int c) {
    return c == ' ' || c == '\t' || c == '\f' || c == '\v';
}

Token read_number(File *src) {
    char c;
    int idx = 0;
    char *n = calloc(4, sizeof(char));
    while ((isdigit(c = file_peek(src)))) {
        n[idx++] = c;
        file_next(src);
    }
    return new_token(INT, n);
}

Token read_ident(File *src) {
    char c;
    int idx = 0;
    char ident[256] = "";
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

Token *lex(File *src) {
    Token *tokens = calloc(MAX_TOKENS, sizeof(Token));
    char c;
    int idx = 0;
    while ((c = file_peek(src)) != EOF) {
        switch (c) {
            case '+':
                tokens[idx++] = new_token(ADD, (char *) TOKEN_TYPE_STR[ADD]);
                file_next(src);
                break;
            case '-':
                tokens[idx++] = new_token(SUB, (char *) TOKEN_TYPE_STR[SUB]);
                file_next(src);
                break;
            case '*':
                tokens[idx++] = new_token(MUL, (char *) TOKEN_TYPE_STR[MUL]);
                file_next(src);
                break;
            case '/':
                tokens[idx++] = new_token(QUO, (char *) TOKEN_TYPE_STR[QUO]);
                file_next(src);
                break;
            case '%':
                tokens[idx++] = new_token(MOD, (char *) TOKEN_TYPE_STR[MOD]);
                file_next(src);
                break;
            case '(':
                tokens[idx++] = new_token(LPAREN, (char *) TOKEN_TYPE_STR[LPAREN]);
                file_next(src);
                break;
            case ')':
                tokens[idx++] = new_token(RPAREN, (char *) TOKEN_TYPE_STR[RPAREN]);
                file_next(src);
                break;
            default:
                if (is_whitespace(c)) {
                    file_next(src);
                    break;
                } else if (isdigit(c)) {
                    tokens[idx++] = read_number(src);
                    break;
                } else if (isalpha(c) || c == '_') {
                    tokens[idx++] = read_ident(src);
                    break;
                } else {
                    tokens[idx] = new_token(ILLEGAL, &c);
                    file_next(src);
                    break;
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
    int idx = 0;
    while (tokens[idx].type != TOK_EOF) {
        printf("%s\n", token_to_str(&tokens[idx++]));
    }
    return Atom;
}

Sexpr parse_atom() {
    return List;
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
    if (!getcwd(cwd, sizeof(cwd))) {
        perror("getcwd() error");
        return 1;
    }
    snprintf(cwd, PATH_MAX*sizeof(char), "%s", "../examples/simple.lic");
    File *file = new_file(cwd);
    Token* tokens = lex(file);
    int idx = 0;
    while (tokens[idx].type != TOK_EOF) {
        printf("%s\n", token_to_str(&tokens[idx++]));
    }
    return 0;
}
