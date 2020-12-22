#include <iostream>
#include <string>
#include <vector>

constexpr int LITERS = 150;

static std::vector<int> recipes;
static std::vector<int> combinations_cnt;
static void calc_combinations_cnt_min_recipes(size_t recipes_pos = 0,
                                   int liters = 0, int recipes_cnt = 1);

int main()
{
  std::istream &input = std::cin;

  int num;
  while (input >> num)
    recipes.push_back(num);
  combinations_cnt.resize(recipes.size(), 0);

  calc_combinations_cnt_min_recipes();

  for (size_t i = 0; i < combinations_cnt.size(); i++) {
    if (combinations_cnt[i] != 0) {
      std::cout << "Combinations that sum 150l with min. num. of recipes ("
                << i << "): " << combinations_cnt[i] << std::endl;
      break;
    }
  }
  return 0;
}

static void calc_combinations_cnt_min_recipes(size_t pos, int liters, int recipes_cnt) {
  while (pos < recipes.size()) {
    int liters_sum = liters + recipes[pos];
    if (liters_sum == LITERS)
      combinations_cnt[recipes_cnt]++;
    else if (liters_sum < LITERS)
      calc_combinations_cnt_min_recipes(pos + 1, liters_sum, recipes_cnt + 1);
    pos++;
  }
}
