#ifndef LEXER_H
#define LEXER_H

#include <string>
#include "token.h"

token::TokenStream lex(std::string src);

#endif
