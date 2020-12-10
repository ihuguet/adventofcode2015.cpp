#include <iostream>

int main ()
{
  char ch;
  int floor = 0;
  while (std::cin.get(ch)) {
    floor += ch == '(' ? 1 : -1;
  }
  std::cout << "floor = " << floor << std::endl;
  return 0;
}
