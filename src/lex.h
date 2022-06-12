#ifndef LEXER_H
#define LEXER_H

#include "token.h"
#include <string>
#include <fstream>
#include <map>

using std::vector;
using namespace token;

vector<Token> lex(std::ifstream src);

#endif
