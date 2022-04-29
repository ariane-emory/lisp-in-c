#ifndef AST_H
#define AST_H

#include <stdlib.h>

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

Object *new_object(Type type);
Object *new_number(long n);
Object *new_symbol(char *name);
char *ast_to_str(Object *ast);

#endif
