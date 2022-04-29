#include "ast.h"

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