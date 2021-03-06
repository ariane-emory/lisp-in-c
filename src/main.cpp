#include <iostream>
#include <fstream>
#include "token.h"
#include "lex.h"

using std::ifstream;
using std::vector;
using token::TokenType;

int main()
{
  // char c;
  // std::ifstream file("examples/simple.lic");
  // while (file.get(c))
  //   std::cout << c;
  // file.close();

  vector<Token> tokens = lex(ifstream("examples/simple.lic"));
  // while (tokens.peek().type != TokenType::Eof)
  //   std::cout << tokens.next() << std::endl;

  return 0;
}
