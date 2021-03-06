#include "lex.h"

static std::map<string, TokenType> keywords = {
  {"let", TokenType::Let},
  {"lambda", TokenType::Lambda}
};

Token read_number(std::ifstream &src)
{
  int c;
  string lit = "";
  while ((!src.eof()) && isdigit(c = src.peek()))
  {
    lit += static_cast<char>(c);
    src.get();
  }
  return Token(TokenType::Number, lit);
}

Token read_ident(std::ifstream &src)
{
  int c;
  string lit = "";
  while ((! src.eof()) && (isalnum(c = src.peek()) || c == '_'))
  {
    lit += static_cast<char>(c);
    src.get();
  }
  return keywords.find(lit) != keywords.end()
  ? Token(keywords[lit], lit)
  : Token(TokenType::Ident, lit);
}

vector<Token> lex(std::ifstream src)
{
  int c;
  vector<Token> tokens;
  tokens.push_back(Token(TokenType::LParen, "("));

  while ((!src.eof()) && (c = src.peek()))
  {
    putchar(src.peek());
    switch (c)
    {
    case '+':
      tokens.push_back(Token(TokenType::Add, "+"));
      src.get();
      break;
    case '-':
      tokens.push_back(Token(TokenType::Sub, "-"));
      src.get();
      break;
    case '*':
      tokens.push_back(Token(TokenType::Mul, "*"));
      src.get();
      break;
    case '/':
      tokens.push_back(Token(TokenType::Quo, "/"));
      src.get();
      break;
    case '%':
      tokens.push_back(Token(TokenType::Mod, "%"));
      src.get();
      break;
    case '(':
      tokens.push_back(Token(TokenType::LParen, "("));
      src.get();
      break;
    case ')':
      tokens.push_back(Token(TokenType::RParen, ")"));
      src.get();
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
        tokens.push_back(Token(TokenType::Err, string{static_cast<char>(c)}));
      }
      break;
    }
  }
  tokens.push_back(Token(TokenType::RParen, ")"));
  tokens.push_back(Token(TokenType::Eof, ""));

  return tokens;
}
