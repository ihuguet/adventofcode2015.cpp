#include <iostream>

int main ()
{
  char ch;
  int floor = 0;
  for (int ch_num = 1; std::cin.get(ch); ch_num++) {
    floor += ch == '(' ? 1 : -1;
    if (floor == -1) {
      std::cout << "basement first time = " << ch_num << std::endl;
      return 0;
    }
  }
  std::cerr << "basement never reached" << std::endl;
  return 1;
}
