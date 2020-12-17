#include <iostream>
#include <string>
#include <regex>
#include <vector>
#include <numeric>

constexpr int MAX_UNITS = 100;
constexpr int REQ_CALORIES = 500;

struct Properties {
    long cap, dur, flv, tex, cal;
    long score() const noexcept;
    Properties() noexcept;
    Properties(long cap, long dur, long flv, long tex, long cal) noexcept;
};

struct Ingredient {
  std::string name;
  Properties props;
  unsigned int quantity;
};

const Properties operator*(int mult, const Properties &p) {
  return Properties{mult*p.cap, mult*p.dur, mult*p.flv, mult*p.tex, mult*p.cal};
}

const Properties operator+(const Properties &a, const Properties &b) {
  return Properties{a.cap+b.cap, a.dur+b.dur, a.flv+b.flv, a.tex+b.tex, a.cal+b.cal};
}

static std::vector<Ingredient> get_ingredients_data(std::istream &input);
static long get_max_score (std::vector<Ingredient> &ingredients, int recipe_capacity);

int main () {
  std::istream &input = std::cin;

  auto ingredients = get_ingredients_data(input);
  long max_score = get_max_score(ingredients, MAX_UNITS);

  std::cout << "Max. score: " << max_score << std::endl;
  return 0;
}

static std::vector<Ingredient> get_ingredients_data(std::istream &input) {
  std::regex line_regex("^([[:alpha:]]+): capacity ([+-]?[[:digit:]]+), durability ([+-]?[[:digit:]]+), flavor ([+-]?[[:digit:]]+), texture ([+-]?[[:digit:]]+), calories ([+-]?[[:digit:]]+)$");

  std::vector<Ingredient> ingrs;

  std::string line;
  while (std::getline(input, line)) {
    std::smatch matchs;
    if (!std::regex_match(line, matchs, line_regex)) {
      std::cerr << "Invalid line: " << line << '\n';
      continue;
    }
    ingrs.emplace_back(Ingredient{matchs[1], Properties{std::stoi(matchs[2]), std::stoi(matchs[3]), std::stoi(matchs[4]),
        std::stoi(matchs[5]), std::stoi(matchs[6])}, 0});
  }

  return ingrs;
}

static inline int sum_used_capacity(std::vector<Ingredient> &ingredients, size_t ingr_idx) {
  int sum = 0;
  for (size_t i = 0; i < ingr_idx; i++)
    sum += ingredients[i].quantity;
  return sum;
}

static void find_max_score (std::vector<Ingredient> &ingredients, int recipe_capacity, size_t ingr_idx, long &max_score) {
  int used_capacity = sum_used_capacity(ingredients, ingr_idx);
  int remaining_capacity = recipe_capacity - used_capacity;

  if (ingr_idx == ingredients.size() - 1) {
    ingredients[ingr_idx].quantity = remaining_capacity;
    Properties props;
    for (auto ingr : ingredients)
      props = props + ingr.quantity * ingr.props;
    long score = props.cal == REQ_CALORIES ? props.score() : 0;
    if (score > max_score)
      max_score = score;
  }
  else {
    for (int i = 0; i <= remaining_capacity; i++) {
      ingredients[ingr_idx].quantity = i;
      find_max_score(ingredients, recipe_capacity, ingr_idx + 1, max_score);
    }
  }
}

static long get_max_score (std::vector<Ingredient> &ingredients, int recipe_capacity) {
  long max_score = 0;
  find_max_score(ingredients, recipe_capacity, 0, max_score);
  return max_score;
}

Properties::Properties() noexcept : cap(0), dur(0), flv(0), tex(0), cal(0) {}

Properties::Properties(long cap, long dur, long flv, long tex, long cal) noexcept :
    cap(cap), dur(dur), flv(flv), tex(tex), cal(cal) {}

long Properties::score() const noexcept {
  return std::max(cap, 0L) * std::max(dur, 0L) * std::max(flv, 0L) * std::max(tex, 0L);
}
