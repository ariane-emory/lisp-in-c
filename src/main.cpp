#include <iostream>
#include <fstream>
#include "token.h"
#include "lex.h"

using std::ifstream;
using token::TokenStream;
using token::TokenType;

int main()
{
  // char c;
  // std::ifstream file("examples/simple.lic");
  // while (file.get(c))
  //   std::cout << c;
  // file.close();

  auto tokens = lex(ifstream("examples/simple.lic"));

  for (auto token = tokens.begin(); token != tokens.end(); token++)
    std::cout << *token << std::endl;

  return 0;
}
