#include <iostream>
#include <set>

struct coords {
  int lat, lon;
};

bool operator<(const coords a, const coords b) {
  return a.lat != b.lat ? a.lat < b.lat : a.lon < b.lon;
}

int main ()
{
  coords curr_cords {0, 0};
  std::set<coords> visited({curr_cords});

  char ch;
  while (std::cin.get(ch)) {
    switch (ch) {
      case '^': curr_cords.lat++; break;
      case 'v': curr_cords.lat--; break;
      case '>': curr_cords.lon++; break;
      case '<': curr_cords.lon--; break;
      default: throw std::invalid_argument(std::string("Wrong direction char: ") + ch);
    }
    visited.insert(curr_cords);
  }

  std::cout << "Number of visited houses: " << visited.size() << std::endl;
  return 0;
}
