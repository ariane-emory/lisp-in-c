#ifndef TOKEN_H
#define TOKEN_H

#include <string>
#include <vector>
#include <iostream>
#include <map>

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

  static std::map<TokenType, string> TokenTypeNames = 
  {
    {TokenType::Eof, "Eof"},
    {TokenType::Err, "Err"},
    {TokenType::Comment, "Comment"},

    {TokenType::Ident, "Ident"},
    {TokenType::Number, "Number"},
    {TokenType::String, "String"},

    {TokenType::Add, "Add"},
    {TokenType::Sub, "Sub"},
    {TokenType::Mul, "Mul"},
    {TokenType::Quo, "Quo"},
    {TokenType::Mod, "Mod"},

    {TokenType::LParen, "LParen"},
    {TokenType::RParen, "RParen"},

    {TokenType::Let, "Let"},
    {TokenType::Lambda, "Lambda"}
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
      os << "Token {Type: " << TokenTypeNames[tok.type] << ", Lit: " << tok.lit << "}";
      return os;
    }
  };
}

#endif
