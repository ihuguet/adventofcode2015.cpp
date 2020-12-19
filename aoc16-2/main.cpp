#include <iostream>
#include <string>
#include <map>

using iterator_t = std::string::const_iterator;
using compound_t = std::pair<std::string,int>;
static bool get_next_compound(iterator_t &begin, iterator_t end, compound_t &compound);
static bool validate_compound(compound_t &compound);

static std::map<std::string, int> SueX;

int main()
{
  std::istream &input = std::cin;

  SueX["children"] = 3;
  SueX["cats"]     = 7;
  SueX["samoyeds"] = 2;
  SueX["pomeranians"] = 3;
  SueX["akitas"]   = 0;
  SueX["vizslas"]  = 0;
  SueX["goldfish"] = 5;
  SueX["trees"]    = 3;
  SueX["cars"]     = 2;
  SueX["perfumes"] = 1;

  std::string line;
  while (std::getline(input, line)) {
    auto it = line.cbegin() + line.find(':') + 2;
    bool is_this_Sue = true;
    compound_t compound;
    while (get_next_compound(it, line.cend(), compound)) {
      if (!validate_compound(compound)) {
        is_this_Sue = false;
        break;
      }
    }
    if (is_this_Sue)
      std::cout << line << '\n';
  }

  return 0;
}

static bool get_next_compound(iterator_t &begin, iterator_t end, compound_t &compound) {
  std::string_view sv(&*begin, end - begin);

  size_t name_pos_end, val_pos_beg, val_pos_end;
  name_pos_end = sv.find(':');

  if (name_pos_end == std::string::npos)
    return false;

  val_pos_beg  = name_pos_end + 2;
  val_pos_end  = sv.find(',', val_pos_beg);
  if (val_pos_end == std::string::npos) {
    val_pos_end = end - begin;
    begin = end;
  }
  else {
    std::advance(begin, val_pos_end + 2);
  }

  compound.first  = sv.substr(0, name_pos_end);
  compound.second = std::stoi(std::string(sv.substr(val_pos_beg, val_pos_end)));
  return true;
}

static bool validate_compound(compound_t &compound) {
  std::string &name = compound.first;
  int &val = compound.second;

  if (!SueX.count(name))
    return true;
  int SueX_val = SueX.at(name);

  if (name == "cats" || name == "trees")
    return val > SueX_val;
  if (name == "pomeranians" || name == "goldfish")
    return val < SueX_val;
  return val == SueX_val;
}
