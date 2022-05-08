#include <stdio.h>
#include "file.h"
#include "token.h"
#include "lex.h"
// #include "ast.h"
// #include "parse.h"
// #include "gc.h"
// #include "eval.h"

int main() {
    File *file = open_file("examples/test.lic");
    // char c;
    // while ((c = file_next(file)) != EOF) {
    //     putchar(c);
    // }
    // FILE *file = fopen("./examples/test.lic", "r");
    // while (true) {
    //     int c = fgetc(file);
    //     if (c == EOF) return 0;
    //     putchar(c);
    // }
    TokenStream *stream = lex(file);
    close_file(file);
    while (tok_peek(stream)->type != TOK_EOF) {
        printf("%s\n", token_to_str(tok_next(stream)));
    }
    // Object *ast = parse(tokens);
    // printf(ast_to_str(ast));
    return 0;
}
