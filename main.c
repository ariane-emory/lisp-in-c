#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>
#include <stdlib.h>

//=================================================================
// Helper Types
//=================================================================

typedef struct {
    FILE *file;
} File;

char* ReadFile(char *filename)
{
    char *buffer = NULL;
    int string_size, read_size;
    FILE *handler = fopen(filename, "r");

    if (handler)
    {
        // Seek the last byte of the file
        fseek(handler, 0, SEEK_END);
        // Offset from the first to the last byte, or in other words, filesize
        string_size = ftell(handler);
        // go back to the start of the file
        rewind(handler);

        // Allocate a string that can hold it all
        buffer = (char*) malloc(sizeof(char) * (string_size + 1) );

        // Read it all in one operation
        read_size = fread(buffer, sizeof(char), string_size, handler);

        // fread doesn't set it so put a \0 in the last position
        // and buffer is now officially a string
        buffer[string_size] = '\0';

        if (string_size != read_size)
        {
            // Something went wrong, throw away the memory and set
            // the buffer to NULL
            free(buffer);
            buffer = NULL;
        }

        // Always remember to close the file.
        fclose(handler);
    }

    return buffer;
}

File *new_file(char* path) {
    File *f;
    f->file = fopen(path, "r");
    if (!f->file)
        printf("Error: file \"%s\" does not exist!", path);
    return f;
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
    TOK_EOF = -1,
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

//=================================================================
// Lexer
//=================================================================

Token* lex(FILE *src) {

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

Sexpr parse(Token* tokens) {
    return Atom;
}

//=================================================================
// Eval
//=================================================================

//=================================================================
// Entry Point
//=================================================================

int main() {
    char cwd[PATH_MAX];
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        printf("Current working dir: %s\n", cwd);
    } else {
        perror("getcwd() error");
        return 1;
    }
    snprintf(cwd, sizeof(cwd), "%s", "../examples/simple.lic");
    File *file = new_file(cwd);

    int c;
    while ((c = file_peek(file) != EOF)) {
        putchar(c);
    }

//    Token* tokens = lex(src);
//    printf("%v", tokens);
//    TokenType tk = ILLEGAL;
//    printf("Illegal: %d\n", tk);
    return 0;
}
