#include "token.h"

using namespace token;

const Token &TokenStream::peek() const
{
  return this->tokens.at(this->pos);
}

const Token &TokenStream::next()
{
  return this->tokens.at(this->pos++);
}