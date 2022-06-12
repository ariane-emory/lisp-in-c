#ifndef PARSER_H
#define PARSER_H

#include "token.h"
#include "ast.h"

using ast::Object;
using token::Token;

namespace parser
{
  Object parse(vector<Token>);
}

#endif