#include <iostream>
#include <string>
#include <sstream>
#include <openssl/md5.h> // required libssl-dev (ubuntu: apt install libssl-dev)
#include <iomanip>

int main ()
{
  std::string secret_key("iwrupvqb");
  std::string answer;
  unsigned char hash[MD5_DIGEST_LENGTH];
  for (unsigned long answer_num = 0; answer.length() == 0; answer_num++) {
    std::stringstream sstream;
    sstream << answer_num;

    std::string str_to_hash(secret_key + sstream.str());
    MD5(reinterpret_cast<const unsigned char*>(str_to_hash.data()), str_to_hash.size(), hash);

    if (hash[0] == 0 && hash[1] == 0 && hash[2] == 0)
      answer = sstream.str();
  }

  std::cout << "answer: " << answer  << '\n';
  std::cout << "md5: " << std::hex << std::setfill('0');
  for (int i = 0; i < MD5_DIGEST_LENGTH; i++)
    std::cout << std::setw(2) << static_cast<int>(hash[i]);
  std::cout << std::endl;
  return 0;
}
