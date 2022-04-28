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
const unsigned int MAX_OBJECTS = 10000;

typedef struct {
    FILE *file;
} File;

File *open_file(char* filename) {
    char path[PATH_MAX];
    if (!getcwd(path, sizeof(path))) {
        perror("getcwd() error");
        exit(1);
    }
    snprintf(path, PATH_MAX*sizeof(char), "../%s", filename);

    File *f = malloc(sizeof(File));
    f->file = fopen(path, "r");
    if (!f->file) {
        printf("Error: file \"%s\" does not exist!", path);
        exit(1);
    }
    return f;
}

void close_file(File *file) {
    fclose(file->file);
    free(file);
    file = NULL;
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

char file_next(File *self) {
    return (char) fgetc(self->file);
}

char file_peek(File *self) {
    int c;
    c = fgetc(self->file);
    ungetc(c, self->file);
    return (char) c;
}

//=================================================================
// Tokens
//=================================================================

typedef enum TokenType {
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

//typedef struct {
//    int pos;
//    Token *tokens;
//} TokenStream;
//
//Token *tok_next(TokenStream *self) {
//    return &self->tokens[0];
//}

//=================================================================
// Lexer
//=================================================================

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

Token *lex(File *src) {
    Token t[MAX_TOKENS];
    char c;
    int idx = 0;
    while ((c = file_peek(src)) != EOF) {
//        printf("char: %c\n", c);
        switch (c) {
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

    return tokens;
}

//=================================================================
// Ast
//=================================================================


typedef struct Object Object;

typedef enum Type {
    NUMBER,
    SYMBOL,
    CONS,
    ENV
} Type;

struct Object {
    Type type;
    size_t size;
    union {
        struct { long number; };                        // number
        struct { Object *car, *cdr; };                  // cons
        struct { char *name; };                         // symbol
//        struct { Object *parent, *vars, *vals; };       // env
//        struct { Object *forward; };                    // forwarding pointer
    };
};

Object *new_object(Type type) {
    Object *obj = calloc(1, sizeof(Object));
    obj->type = type;
    return obj;
}

Object *new_number(long n) {
    Object *obj = new_object(NUMBER);
    obj->number = n;
    return obj;
}

Object *new_symbol(char *name) {
    Object *obj = new_object(SYMBOL);
    obj->name = name;
    return obj;
}

char *ast_to_str(Object *ast) {

}

//=================================================================
// Parser
//=================================================================

//Object *parse_atom(Token *tokens, int pos) {
//    int idx = pos;
//    while (tokens[idx].type != TOK_EOF) {
//        Token tok = tokens[idx];
//        switch (tok.type) {
//            case IDENT:
//                return new_symbol(tok.lit);
//            case INT:
//                return new_number(atol(tok.lit));
//            default:
//                break;
//        }
//    }
//}

Object *parse_list(Token *tokens, int pos) {
    int idx = pos;
    Object cons;
    while (tokens[idx++].type != TOK_EOF) {
        Token tok = tokens[idx-1];
        switch (tok.type) {
            case IDENT:
            case ADD:
            case SUB:
            case MUL:
            case QUO:
            case MOD:
                cons.car = new_symbol(tok.lit);
                cons.cdr = parse_list(tokens, idx-1);
                break;
            case INT:
                cons.car = new_number(strtol(tok.lit, NULL, 10));
                cons.cdr = parse_list(tokens, idx-1);
                break;
            case LPAREN:
                cons.car = parse_list(tokens, idx-1);
                cons.cdr = parse_list(tokens, idx);
                break;
            case RPAREN:
                break;
            default:
                printf("error: invalid list token: %s", token_to_str(&tok));
                exit(1);
        }
    }
    Object *list = calloc(idx-pos+1, sizeof(Object));
    memcpy(list, &cons, (idx-pos+1)*sizeof(Object));

    return list;
}

Object *parse_expr() {
    return NULL;
}

Object *parse(Token *tokens) {
    int idx = 0;
    int obj_idx = 0;
    Object objs[MAX_OBJECTS];
    while (tokens[idx++].type != TOK_EOF) {
        printf("%s\n", token_to_str(&tokens[idx-1]));
        Token tok = tokens[idx-1];
        switch (tok.type) {
            case IDENT:
            case ADD:
            case SUB:
            case MUL:
            case QUO:
            case MOD:
                objs[obj_idx++] = *new_symbol(tok.lit);
                printf("obj: %s\n", objs[obj_idx-1]);
                break;
            case INT:
                objs[obj_idx++] = *new_number(strtol(tok.lit, NULL, 10));
                break;
            case LPAREN:
                objs[obj_idx++] = *parse_list(tokens, idx-1);
                break;
            default:
                printf("error: invalid top level token: %s", token_to_str(&tok));
                exit(1);
        }
    }
    Object *ast = calloc(obj_idx+1, sizeof(Object));
    memcpy(ast, objs, obj_idx+1*sizeof(Object));

    return ast;
}

//=================================================================
// Garbage Collection
//=================================================================

void init() {

}

void allocate(int n) {

}

void collect(int n) {}

//=================================================================
// Eval
//=================================================================

int eval(Object objects[]) {
    return 0;
}

//=================================================================
// Entry Point
//=================================================================

int main() {
    File *file = open_file("examples/test.lic");
    Token* tokens = lex(file);
    close_file(file);
//    int idx = 0;
//    while (tokens[idx].type != TOK_EOF) {
//        printf("%s\n", token_to_str(&tokens[idx++]));
//    }
    Object *ast = parse(tokens);
    printf(ast_to_str(ast));

    return 0;
}
