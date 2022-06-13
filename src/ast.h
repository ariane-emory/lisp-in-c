#ifndef AST_H
#define AST_H

#include <string>

namespace ast
{
  class Object;
  
  union ObjectValue
  {
    double number;
    std::string symbol;
    class List
    {
      Object *car;
      Object *cdr;
    };

    ~ObjectValue() {}
  };

  class Object
  {
  public:
    ObjectValue value;
  };
}

#endif
