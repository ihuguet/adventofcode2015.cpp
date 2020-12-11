#include <iostream>
#include <string>
#include <regex>

int main ()
{
  std::istream &input = std::cin;
  std::regex escape_2ch_regex(R"(\\[\\"])");
  std::regex escape_4ch_regex(R"(\\x[a-f0-9]{2})");
  unsigned long cnt_ch_code = 0, cnt_ch_bin = 0;
  
  std::string line;
  while (std::getline(input, line)) {
    std::sregex_iterator it_matches_2ch(line.cbegin() + 1, line.cend() - 1, escape_2ch_regex);
    std::sregex_iterator it_matches_4ch(line.cbegin() + 1, line.cend() - 1, escape_4ch_regex);
    std::sregex_iterator it_matches_end;

    cnt_ch_code += line.length(); // new line must be ignored
    cnt_ch_bin += line.length() - 2  // -2: open & close quotes
                  - std::distance(it_matches_2ch, it_matches_end)  // escape sequences with 2 chars (\\ and \")
                  - 3 * std::distance(it_matches_4ch, it_matches_end);  // escape sequences with 3 chars (\x00)
  }

  std::cout << "Characters in code: " << cnt_ch_code << '\n'
            << "Characters in memory: " << cnt_ch_bin << '\n'
            << "Chars code - chars memory: " << (cnt_ch_code - cnt_ch_bin) << std::endl;
  return 0;
}
