#include "lex.h"

using namespace token;
using std::string;
using std::vector;

Token read_number(std::ifstream &src)
{
  char c;
  string lit = "";
  while (isdigit(c = src.peek()))
  {
    lit += c;
    src.get();
  }
  return Token(TokenType::Number, lit);
}

Token read_ident(std::ifstream &src)
{
  char c;
  string lit = "";
  while (isalnum(c = src.peek()) || c == '_')
  {
    lit += c;
    src.get();
  }
  return Token(TokenType::Number, lit);
}

TokenStream lex(std::ifstream &src)
{
  char c;
  vector<Token> tokens;
  TokenStream stream;
  while ((c = src.peek()))
  {
    switch (c)
    {
    case '+':
      tokens.push_back(Token(TokenType::Add, "+"));
      break;
    case '-':
      tokens.push_back(Token(TokenType::Sub, "-"));
      break;
    case '*':
      tokens.push_back(Token(TokenType::Mul, "*"));
      break;
    case '/':
      tokens.push_back(Token(TokenType::Quo, "/"));
      break;
    case '%':
      tokens.push_back(Token(TokenType::Mod, "%"));
      break;
    case '(':
      tokens.push_back(Token(TokenType::LParen, "("));
      break;
    case ')':
      tokens.push_back(Token(TokenType::RParen, ")"));
      break;
    default:
      if (isspace(c))
      {
        src.get();
      }
      else if (isdigit(c))
      {
        tokens.push_back(read_number(src));
      }
      else if (isalpha(c) || c == '_')
      {
        tokens.push_back(read_ident(src));
      }
      else
      {
        tokens.push_back(Token(TokenType::Err, string{c}));
      }
      break;
    }
  }
  tokens.push_back(Token(TokenType::Eof, ""));
  return stream;
}
