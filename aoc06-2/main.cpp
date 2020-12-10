#include <iostream>
#include <string>
#include <regex>

static unsigned int brights[1000][1000];

int main ()
{
  std::istream &input = std::cin;
  std::regex line_regex("(turn on|turn off|toggle) (\\d+),(\\d+) through (\\d+),(\\d+)");

  for (int i = 0; i < 1000; i++) {
    for (int j = 0; j < 1000; j++)
      brights[i][j] = false;
  }

  std::string line;
  while (std::getline(input, line)) {
    std::smatch matchs;
    if (!std::regex_match(line, matchs, line_regex)) {
      std::cerr << "Invalid line: " << line << '\n';
      continue;
    }

    std::string op = matchs[1];
    int x0 = std::stoi(matchs[2]);
    int y0 = std::stoi(matchs[3]);
    int x1 = std::stoi(matchs[4]);
    int y1 = std::stoi(matchs[5]);

    std::function<void(unsigned int&)> op_fn;
    if (op == "turn on")
      op_fn = [](unsigned int &bright) {bright += 1;};
    else if (op == "turn off")
      op_fn = [](unsigned int &bright) {if (bright > 0) bright -= 1;};
    else // toggle
      op_fn = [](unsigned int &bright) {bright += 2;};

    for (int x = x0; x <= x1; x++) {
      for (int y = y0; y <= y1; y++)
        op_fn(brights[x][y]);
    }
  }
  
  unsigned int total_bright = 0;
  for (int i = 0; i < 1000; i++) {
    for (int j = 0; j < 1000; j++) {
      total_bright += brights[i][j];
    }
  }

  std::cout << "Total brightness: " << total_bright << std::endl;
  return 0;
}
