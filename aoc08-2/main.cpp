#include <iostream>
#include <string>
#include <regex>

int main ()
{
  std::istream &input = std::cin;
  std::regex encoding_regex(R"([\\"])");
  unsigned long cnt_ch_code = 0, cnt_ch_encoded = 0;
  
  std::string line;
  while (std::getline(input, line)) {
    std::string encoded_str = '"' + std::regex_replace(line, encoding_regex, "\\$0") + '"';
    cnt_ch_code += line.length();
    cnt_ch_encoded += encoded_str.length();
  }

  std::cout << "Characters in code: " << cnt_ch_code << '\n'
            << "Characters encoded: " << cnt_ch_encoded << '\n'
            << "Chars encoded - chars code: " << (cnt_ch_encoded - cnt_ch_code) << std::endl;
  return 0;
}
