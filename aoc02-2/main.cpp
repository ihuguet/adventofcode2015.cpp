#include <iostream>
#include <string>

int main ()
{
  std::istream &input = std::cin;

  int m_total = 0;

  std::string line;
  while (std::getline(input, line)) {
    size_t sep1 = line.find('x', 0);
    size_t sep2 = line.find('x', sep1 + 1);

    int x = std::stoi(line.substr(0, sep1));
    int y = std::stoi(line.substr(sep1 + 1, sep2 - sep1 - 1));
    int z = std::stoi(line.substr(sep2 + 1));
    int perimeter = 2 * (x + y + z - std::max(x, std::max(y, z)));
    int vol = x * y * z;

    m_total += perimeter + vol;
  }

  std::cout << "m total = " << m_total << std::endl;
  return 0;
}
