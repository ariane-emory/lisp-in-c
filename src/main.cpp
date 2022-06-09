#include <iostream>
#include <fstream>

int main()
{
  char c;
  std::ifstream file("examples/simple.lic");
  while (file.get(c))
    std::cout << c;
  file.close();
  return 0;
}
