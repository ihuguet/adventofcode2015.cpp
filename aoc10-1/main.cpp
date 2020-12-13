#include <iostream>
#include <string>

int main ()
{
  std::string str = "1321131112";

  for (int i = 0; i < 40; i++) {
    size_t pos = 0;
    std::string str_new;
    while (pos < str.length()) {
      char ch = str[pos];
      size_t pos_end = str.find_first_not_of(ch, pos);
      if (pos_end == std::string::npos)
        pos_end = str.length();
      str_new += std::to_string(pos_end - pos),
      str_new += ch;
      pos = pos_end;
    }
    str = str_new;
  }

  std::cout << str << " (length = " << str.length() << ")" << std::endl;
  return 0;
}
