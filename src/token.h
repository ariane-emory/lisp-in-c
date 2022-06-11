#ifndef TOKEN_H
#define TOKEN_H

#include <string>
#include <vector>
#include <iostream>
#include <array>

using std::string;
using std::ostream;
using std::vector;

namespace token
{
  enum class TokenType
  {
    Eof,
    Err,
    Comment,

    Ident,
    Number,
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

  static constexpr std::string TokenTypeNames[] = 
  {
    "Eof",
    "Err",
    "Comment",

    "Ident",
    "Number",
    "String",

    "Add",
    "Sub",
    "Mul",
    "Quo",
    "Mod",

    "LParen",
    "RParen",

    "Let",
    "Lambda"
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
     
    friend ostream& operator<<(ostream& os, const Token& tok)
    {
      os << "Token {" << TokenTypeNames[static_cast<int>(tok.type)] << ", " << tok.lit << "}";
      return os;
    }
  };

  class TokenStream
  {
    size_t pos;
    vector<Token> tokens;

  public:
    const Token &peek() const;
    const Token &next();
  };
}

#endif
