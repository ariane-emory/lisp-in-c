#include "parser.h"

Object parse_atom(std::vector<token::Token>::iterator &iter)
{

}

Object parse_list(std::vector<token::Token>::iterator &iter) 
{

}

Object parse(vector<Token> tokens)
{
  for (auto iter = tokens.begin(); iter != tokens.end(); iter++)
  {
    std::cout << *iter << std::endl;

    switch (iter->type)
    {
    case TokenType::LParen:
      return parse_list(iter);
    default:
      return parse_atom(iter);
    } 
  }
}