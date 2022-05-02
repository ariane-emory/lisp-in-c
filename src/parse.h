#ifndef PARSE_H
#define PARSE_H

#include "token.h"
#include "ast.h"

const unsigned int MAX_OBJECTS;

Object *parse(TokenStream *tokens);

#endif