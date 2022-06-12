#ifndef AST_H
#define AST_H

#include <string>

namespace ast
{
  class Object
  {
    union
    {
      double number;
      std::string symbol;
      class List
      {
        Object *car;
        Object *cdr;
      };
    };
  };
}

#endif