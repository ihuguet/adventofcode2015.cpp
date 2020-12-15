#include <iostream>
#include <string>
#include <algorithm>

static bool validate_pwd(const std::string &pwd);
static void inc_pwd(std::string &pwd);

int main ()
{
  std::string pwd = "vzbxkghb";
  do {
    inc_pwd(pwd);
  } while (!validate_pwd(pwd));
  do {
    inc_pwd(pwd);
  } while (!validate_pwd(pwd));

  std::cout << "New pwd: " << pwd << std::endl;
  return 0;
}

static bool validate_pwd(const std::string &pwd) {
  int consecutive_cnt = 1;

  for (size_t i = 1; i < pwd.length(); i++) {
    char ch = pwd[i];

    if (ch == 'i' || ch == 'l' || ch == 'o')
      return false;
    
    if (consecutive_cnt < 3) {
      if (ch == pwd[i - 1] + 1)
        consecutive_cnt++;
      else
        consecutive_cnt = 1;
    }
  }

  if (consecutive_cnt < 3)
    return false;

  auto it = std::adjacent_find(pwd.cbegin(), pwd.cend());
  if (it == pwd.cend())
    return false;

  it = std::adjacent_find(std::next(it, 2), pwd.cend());
  if (it == pwd.cend())
    return false;

  return true;
}

static void inc_pwd (std::string &pwd) {
  auto it = pwd.rbegin();
  while (++(*it) == 'z' + 1) {
    *it = 'a';
    it++;
  }
}
