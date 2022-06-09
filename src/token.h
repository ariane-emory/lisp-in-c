#ifndef TOKEN_H
#define TOKEN_H

#include <string>
#include <vector>

typedef std::string string;

namespace token
{
  enum class TokenType
  {
    Eof,
    Err,
    Comment,

    Ident,
    Int,
    String,

    Add,
    Sub,
    Mul,
    Quo,
    Mod,

    LParen,
    RParen,

    Let,
    Lambda
  };

  class Token
  {
  public:
    TokenType type;
    string lit;

    Token(TokenType type, string lit)
      : type(type),
        lit(lit)
    {
    }
  };

  class TokenStream
  {
    size_t pos;
    std::vector<Token> tokens;

  public:
    const Token &peek() const;
    const Token &next();
  };
}

#endif
