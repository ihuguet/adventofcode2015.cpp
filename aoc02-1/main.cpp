#include <iostream>
#include <string>

int main ()
{
  std::istream &input = std::cin;

  int m2_total = 0;

  std::string line;
  while (std::getline(input, line)) {
    size_t sep1 = line.find('x', 0);
    size_t sep2 = line.find('x', sep1 + 1);

    int x = std::stoi(line.substr(0, sep1));
    int y = std::stoi(line.substr(sep1 + 1, sep2 - sep1 - 1));
    int z = std::stoi(line.substr(sep2 + 1));
    int a1 = x * y;
    int a2 = x * z;
    int a3 = z * y;

    m2_total += 2*a1 + 2*a2 + 2*a3 + std::min(a1, std::min(a2, a3));
  }

  std::cout << "m2 total = " << m2_total << std::endl;
  return 0;
}
