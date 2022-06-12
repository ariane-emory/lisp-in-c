#ifndef PARSER_H
#define PARSER_H

#include "token.h"
#include "ast.h"

using token::TokenStream;
using ast::Object;

namespace parser
{
  Object parse(TokenStream);
}

#endif