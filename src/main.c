#include <stdio.h>
#include "file.h"
#include "token.h"
#include "lex.h"
#include "util.h"
// #include "ast.h"
// #include "parse.h"
// #include "gc.h"
// #include "eval.h"

int main() {
    File *file = open_file("examples/test.lic");
    TokenStream *stream = lex(file);
    close_file(file);

    fflush(stdout);
    //printf("Blaah\n");
    
    while (tok_peek(stream)->type != TOK_EOF) {
        printf("%s\n", token_to_str(tok_next(stream)));
    }
    INFO("Done.")
//    Object *ast = parse(tokens);
//    printf(ast_to_str(ast));

    return 0;
}
