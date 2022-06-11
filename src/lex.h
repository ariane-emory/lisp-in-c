#ifndef LEXER_H
#define LEXER_H

#include "token.h"
#include <string>
#include <fstream>

using std::vector;
using token::Token;

vector<Token> lex(std::ifstream src);

#endif
