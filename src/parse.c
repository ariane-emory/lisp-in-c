#include "parse.h"

static const unsigned int MAX_OBJECTS = 10000;

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

//Object *parse_list(Token *tokens, int pos) {
//    int idx = pos;
//    Object cons;
//    while (tokens[idx++].type != TOK_EOF) {
//        Token tok = tokens[idx-1];
//        switch (tok.type) {
//            case IDENT:
//            case ADD:
//            case SUB:
//            case MUL:
//            case QUO:
//            case MOD:
//                cons.car = new_symbol(tok.lit);
//                cons.cdr = parse_list(tokens, idx-1);
//                break;
//            case INT:
//                cons.car = new_number(strtol(tok.lit, NULL, 10));
//                cons.cdr = parse_list(tokens, idx-1);
//                break;
//            case LPAREN:
//                cons.car = parse_list(tokens, idx-1);
//                cons.cdr = parse_list(tokens, idx);
//                break;
//            case RPAREN:
//                break;
//            default:
//                printf("error: invalid list token: %s", token_to_str(&tok));
//                exit(1);
//        }
//    }
//    Object *list = calloc(idx-pos+1, sizeof(Object));
//    memcpy(list, &cons, (idx-pos+1)*sizeof(Object));
//
//    return list;
//}
//
//Object *parse_expr() {
//    return NULL;
//}

Object *parse(TokenStream *tokens) {
    int idx = 0;
    int obj_idx = 0;
    Object objs[MAX_OBJECTS];
//    while (tokens[idx++].type != TOK_EOF) {
//        printf("%s\n", token_to_str(&tokens[idx-1]));
//        Token tok = tokens[idx-1];
//        switch (tok.type) {
//            case IDENT:
//            case ADD:
//            case SUB:
//            case MUL:
//            case QUO:
//            case MOD:
//                objs[obj_idx++] = *new_symbol(tok.lit);
//                printf("obj: %s\n", objs[obj_idx-1]);
//                break;
//            case INT:
//                objs[obj_idx++] = *new_number(strtol(tok.lit, NULL, 10));
//                break;
//            case LPAREN:
//                objs[obj_idx++] = *parse_list(tokens, idx-1);
//                break;
//            default:
//                printf("error: invalid top level token: %s", token_to_str(&tok));
//                exit(1);
//        }
//    }
    Object *ast = calloc(obj_idx+1, sizeof(Object));
    memcpy(ast, objs, obj_idx+1*sizeof(Object));

    return ast;
}