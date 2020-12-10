#include <iostream>
#include <string>
#include <regex>

static bool lights[1000][1000];

int main ()
{
  std::istream &input = std::cin;
  std::regex line_regex("(turn on|turn off|toggle) (\\d+),(\\d+) through (\\d+),(\\d+)");

  for (int i = 0; i < 1000; i++) {
    for (int j = 0; j < 1000; j++)
      lights[i][j] = false;
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

    std::function<void(bool&)> op_fn;
    if (op == "turn on")
      op_fn = [](bool &light) {light = true;};
    else if (op == "turn off")
      op_fn = [](bool &light) {light = false;};
    else // toggle
      op_fn = [](bool &light) {light = !light;};

    for (int x = x0; x <= x1; x++) {
      for (int y = y0; y <= y1; y++)
        op_fn(lights[x][y]);
    }
  }
  
  unsigned int lights_on = 0;
  for (int i = 0; i < 1000; i++) {
    for (int j = 0; j < 1000; j++) {
      if (lights[i][j])
        lights_on++;
    }
  }

  std::cout << "Lights on: " << lights_on << std::endl;
  return 0;
}
