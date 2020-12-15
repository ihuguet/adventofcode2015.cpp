#include <iostream>
#include <string>
#include <regex>


int main ()
{
  std::istream &input = std::cin;
  std::string input_str((std::istreambuf_iterator<char>(input)), std::istreambuf_iterator<char>());

  std::regex num_regex("[+-]?\\d+");
  std::sregex_iterator it(input_str.cbegin(), input_str.cend(), num_regex);
  std::sregex_iterator it_end;
  long sum = 0;
  while (it != it_end) {
    sum += std::stoi(it->str());
    it++;
  }

  std::cout << "Sum = " << sum << std::endl;
  return 0;
}
