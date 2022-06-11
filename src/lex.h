#ifndef LEXER_H
#define LEXER_H

#include "token.h"
#include <string>
#include <fstream>


vector<token::Token> lex(std::ifstream src);

#endif
