#include <iostream>
#include <string>
#include <vector>

constexpr int LITERS = 150;

static int combinations_cnt = 0;
static std::vector<int> recipes;
static void calc_combinations_cnt(size_t recipes_pos = 0, int liters = 0);

int main()
{
  std::istream &input = std::cin;

  int num;
  while (input >> num)
    recipes.push_back(num);

  calc_combinations_cnt();

  std::cout << "Combinations that sum 150l: " << combinations_cnt << std::endl;
  return 0;
}

static void calc_combinations_cnt(size_t pos, int liters) {
  while (pos < recipes.size()) {
    int liters_sum = liters + recipes[pos];
    if (liters_sum == LITERS)
      combinations_cnt++;
    else if (liters_sum < LITERS)
      calc_combinations_cnt(pos + 1, liters_sum);
    pos++;
  }
}
