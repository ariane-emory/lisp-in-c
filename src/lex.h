#ifndef LEXER_H
#define LEXER_H

#include "token.h"
#include <string>
#include <fstream>

token::TokenStream lex(std::ifstream src);

#endif
