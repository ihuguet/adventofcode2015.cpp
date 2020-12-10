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
  coords santa_coords {0, 0}, robo_coords {0, 0};
  std::set<coords> visited({{0, 0}});

  char ch;
  coords *curr_coords = &santa_coords;
  while (std::cin.get(ch)) {
    switch (ch) {
      case '^': curr_coords->lat++; break;
      case 'v': curr_coords->lat--; break;
      case '>': curr_coords->lon++; break;
      case '<': curr_coords->lon--; break;
      default: throw std::invalid_argument(std::string("Wrong direction char: ") + ch);
    }
    visited.insert(*curr_coords);
    curr_coords = curr_coords == &santa_coords ? &robo_coords : &santa_coords;
  }

  std::cout << "Number of visited houses: " << visited.size() << std::endl;
  return 0;
}
