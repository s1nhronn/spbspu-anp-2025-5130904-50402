#include <iostream>
#include <cstring>

namespace lavrentev
{
  size_t dif_lat(char * ans, std::string s);
  void uni_two(std::string s, std::string s2, size_t ex, size_t ex2, char* result);
}

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

  std::string s2;
  std::getline(std::cin, s2);

  size_t ex2 = s2.size();
  char * ans2 = new char[ex2];
  if (ans2 == nullptr)
  {
    std::cerr << "Memory allocation fail" << "\n";
    return 1;
  }

  char* result = new char[ex + ex2];
  if (result == nullptr)
  {
    std::cerr << "Memory allocation fail" << "\n";
    return 1;
  }

  lavrentev::uni_two(s, s2, ex, ex2, result);
  int ans_7 = lavrentev::dif_lat(ans, s);

  std::cout << "Ans 7: " << ans_7 << "\n";
  std::cout << "Ans 12: " << result << "\n";

  delete[] ans;
  delete[] result;
}

size_t lavrentev::dif_lat(char * ans, std::string s)
{
  size_t ex = s.size();

  size_t answer = 0;

  for (size_t i = 0; i < ex; ++i)
  {
    ans[i] = '#';
  }

  for (size_t i = 0; i < ex; ++i)
  {
    bool flag = false;
    for (size_t j = 0; j < ex; ++j)
    {
      if (ans[j] == s[i])
      {
        flag = true;
        break;
      }
    }

    if (!flag && isalpha(s[i]))
    {
      ans[i] = s[i];
    }
   
  }

  for (size_t i = 0; i < ex; ++i)
  {
    if (ans[i] != '#')
    {
      ++answer;
    }
  }

  return answer;
}

void lavrentev::uni_two(std::string s, std::string s2, size_t ex, size_t ex2, char* result)
{
  size_t min;
  size_t max;
  std::string max_s;
  if (ex < ex2)
  {
    min = ex;
    max = ex2;
    max_s = s2;
  }
  else
  {
    min = ex2;
    max = ex;
    max_s = s;
  }

  size_t buf = 0;

  for (size_t i = 0; i < min; ++i)
  {
    result[buf] =  s[i];
    result[buf + 1] =  s2[i];
    buf += 2;
  }

  buf = min;

  for (size_t i = min * 2; i < ex + ex2; ++i)
  {
    result[i] = max_s[min];
    ++min;
  }
}