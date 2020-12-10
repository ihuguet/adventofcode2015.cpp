#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

int main ()
{
  std::istream &input = std::cin;
  std::string vowels = "aeiou";
  std::vector<std::string> forbiden = {"ab", "cd", "pq", "xy"};
  unsigned int nice_strings_cnt = 0;

  std::string line;
  while (std::getline(input, line)) {
    size_t vowels_cnt = std::count_if(line.cbegin(), line.cend(),
      [&vowels](char ch) -> bool { return vowels.find(ch) != std::string::npos; }
    );
    if (vowels_cnt < 3)
      continue;
    
    auto adj_it = std::adjacent_find(line.cbegin(), line.cend());
    if (adj_it == line.cend())
      continue;
    
    bool forbiden_any = std::any_of(forbiden.cbegin(), forbiden.cend(),
      [&line](const std::string &forbiden_elem) { return line.find(forbiden_elem) != std::string::npos;}
    );
    if (forbiden_any)
      continue;

    nice_strings_cnt++;
  }

  std::cout << "Nice strings count: " << nice_strings_cnt << std::endl;
  return 0;
}
