#include <iostream>
#include <string>
#include <algorithm>

int main ()
{
  std::istream &input = std::cin;
  unsigned int nice_strings_cnt = 0;

  std::string line;
  while (std::getline(input, line)) {
    bool rule1 = false, rule2 = false;

    for (auto it = line.cbegin(); it != line.cend() - 2; it++) {
      if (!rule1 && std::search(it + 2, line.cend(), it, it + 2) != line.cend())
        rule1 = true;
      if (!rule2 && *it == *std::next(it, 2))
        rule2 =true;
      if (rule1 && rule2) {
        nice_strings_cnt++;
        break;
      }
    }
  }

  std::cout << "Nice strings count: " << nice_strings_cnt << std::endl;
  return 0;
}
