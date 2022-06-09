#ifndef LEXER_H
#define LEXER_H

#include <string>
#include "token.h"
#include <fstream>

token::TokenStream lex(std::ifstream src);

#endif
