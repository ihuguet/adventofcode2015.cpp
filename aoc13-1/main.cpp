#include <iostream>
#include <string>
#include <regex>
#include <map>
#include <set>

using happiness_rels_cont_t = std::map<std::string,std::map<std::string,int>>;

static void parse_names_and_relations(std::istream &input, 
              std::vector<std::string> &names, happiness_rels_cont_t &happiness_rels);
static int calc_happiness_sum(const std::vector<std::string> &names,
              const happiness_rels_cont_t &happiness_rels);

int main () {
  std::istream &input = std::cin;

  std::vector<std::string> names;
  happiness_rels_cont_t happiness_rels;
  parse_names_and_relations(input, names, happiness_rels);
  std::sort(names.begin(), names.end());

  int max_happiness_sum = 0;
  do {
    int happiness_sum = calc_happiness_sum(names, happiness_rels);
    if (happiness_sum > max_happiness_sum)
      max_happiness_sum = happiness_sum;
  } while (std::next_permutation(names.begin(), names.end()));

  std::cout << "Max. happiness = " << max_happiness_sum << std::endl;
  return 0;
}

static void parse_names_and_relations(std::istream &input, 
              std::vector<std::string> &names, happiness_rels_cont_t &happiness_rels) {
  std::regex line_regex("^([[:alpha:]]+) would (lose|gain) ([[:digit:]]+) happiness units by sitting next to ([[:alpha:]]+).$");

  std::string line;
  while (std::getline(input, line)) {
    std::smatch matchs;
    if (!std::regex_match(line, matchs, line_regex)) {
      std::cerr << "Invalid line: " << line << '\n';
      continue;
    }

    std::string who = matchs[1];
    std::string to_who = matchs[4];
    int happiness_chg = std::stoi(matchs[3]);
    if (matchs[2] == "lose")
      happiness_chg = -happiness_chg;

    happiness_rels[who][to_who] = happiness_chg;
    if (std::find(names.cbegin(), names.cend(), who) == names.cend())
      names.push_back(std::move(who));
    if (std::find(names.cbegin(), names.cend(), to_who) == names.cend())
      names.push_back(std::move(to_who));
  }
}

static int calc_happiness_sum(const std::vector<std::string> &names,
              const happiness_rels_cont_t &happiness_rels) {
  int happiness_sum = 0;
  for (auto it = names.cbegin(); it != names.cend() - 1; it++) {
    happiness_sum += happiness_rels.at(*it).at(*(it + 1));
    happiness_sum += happiness_rels.at(*(it + 1)).at(*it);
  }
  happiness_sum += happiness_rels.at(names.back()).at(names.front());
  happiness_sum += happiness_rels.at(names.front()).at(names.back());
  return happiness_sum;
}
