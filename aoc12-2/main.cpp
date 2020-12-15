#include <iostream>
#include <string>

/*
 * Why the hell I had the "great" idea that parsing JSON data manually
 * would be fun because "it was an easy task"?
 * Please, don't
 */

using iterator_t = std::istreambuf_iterator<char>;
static long sum_nums_not_in_red_object(iterator_t &it, iterator_t &end);
static int parse_num(iterator_t &it);
static bool prop_val_is_red(iterator_t &it);
static void discard_until_obj_end(iterator_t &it);

int main ()
{
  std::istream &input = std::cin;
  auto beg = (std::istreambuf_iterator<char>(input));
  auto end = std::istreambuf_iterator<char>();
  long sum = sum_nums_not_in_red_object(beg, end);
  std::cout << "Sum = " << sum << std::endl;
  return 0;
}

static long sum_nums_not_in_red_object(iterator_t &it, iterator_t &end) {
  bool in_object = *it == '{';
  if (in_object)
    it++;

  long sum = 0;

  while (it != end) {
    char ch = *it;

    if (ch == '+' || ch == '-' || (ch >= '0' && ch <= '9')) {
      sum += parse_num(it);
    }
    else if (ch == '{') {
      sum += sum_nums_not_in_red_object(it, end);
    }
    else if (in_object && ch == ':') {
      if (it++; *it == '"' && prop_val_is_red(it)) {
        discard_until_obj_end(it);
        return 0;
      }
    }
    else if (in_object && ch == '}') {
      it++;
      return sum;
    }
    else {
      it++;
    }
  }

  return sum;
}

/// parses the number that begins in the position pointed by the iterator
/// asumes that first char has been checked and is a valid first digit for the number
/// moves input iterator to the next position after the number
static int parse_num(iterator_t &it) {
  std::string str;
  str += *it;
  for (it++; *it >= '0' && *it <= '9'; it++)
    str += *it;
  if (str.length() == 1 && (str[0] == '+' || str[0] == '-'))
    return 0;
  return std::stoi(str);
}

/// checks if next token is "red" (quotes included)
/// assumes first character is '"' and read until closing '"'
/// moves input iterator to the next position after the closing '"'
static bool prop_val_is_red(iterator_t &it) {
  std::string str;
  str += *(it++);
  while (*it != '"') {
    if (*it == '\\') str += *(it++);
    str += *(it++);
  }
  str += *(it++);
  return str == "\"red\"";
}

/// discard next data until closing current object
/// assumes we are really inside and object and the first char is NOT the opening '{'
/// moves input iterator to the next position after the closing '}'
static void discard_until_obj_end(iterator_t &it) {
  int obj_depth = 1;
  while (obj_depth > 0) {
    if (*it == '{')
      obj_depth++;
    else if (*it == '}')
      obj_depth--;
    it++;
  }
}