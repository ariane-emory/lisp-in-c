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

  auto toks = lex(ifstream("examples/simple.lic"));

  for (auto tok = toks.begin(); tok != toks.end(); tok++)
    std::cout << *tok << std::endl;

  return 0;
}
