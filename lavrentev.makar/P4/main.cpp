#include <iostream>
#include <cstring>
#include <cctype>

size_t dif_lat(char * ans, std::string s);
std::string uni_two(std::string s);

int main()
{
  std::string s;
  std::getline(std::cin, s);

  size_t ex = s.size();
  char * ans = new char[ex];
  if (ans == nullptr)
  {
    std::cerr << "Memory allocation fail" << "\n";
    return 1;
  }

  int ans_7 = dif_lat(ans, s);

  //std::string ans_12 = uni_two(s);

  std::cout << "Ans 7: " << ans_7 << "\n";
  //std::cout << "Ans 12: " << ans_12 << "\n";

  delete[] ans;
}
