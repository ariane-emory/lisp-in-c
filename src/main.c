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
    IN();
    
    File *file = open_file("examples/test.lic");
    TokenStream *stream = lex(file);
    close_file(file);

    LINE();
        
    do {
        char * tstr = token_to_str(tok_next(stream));
        INFO("%s", tstr);
        free(tstr);        
    }  while (tok_peek(stream)->type != TOK_EOF);

//    Object *ast = parse(tokens);
//    printf(ast_to_str(ast));

    OUT();
    return 0;
}
