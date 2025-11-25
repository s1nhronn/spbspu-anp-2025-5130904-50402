#include <iostream>
#include <cstring>
#include <iomanip>

namespace lavrentev
{
  size_t dif_lat(char* ans, char* s1);
  void uni_two(char* s1, char* s2, size_t ex, size_t ex2, char* result);
  char * getline(std::istream & in, size_t & n);
}

int main()
{
  char* s1 = nullptr;
  size_t n = 0;
  s1 = lavrentev::getline(std::cin, n);
  if (s1 == nullptr)
  {
    std::cerr << "Memory allocation fail" << '\n';
    return 1;
  }
  
  size_t ex = sizeof(s1);

  if(ex == 0)
  {
    std::cerr << "Invalid string";
    return 1;
  }

  char* buf1 = new char[ex];
  if (buf1 == nullptr)
  {
    std::cerr << "Memory allocation fail" << '\n';
    delete[] s1;
    return 1;
  }

  char* s2 = nullptr;
  size_t n2 = 0;
  s2 = lavrentev::getline(std::cin, n2);
  if (s2 == nullptr)
  {
    std::cerr << "Memory allocation fail" << '\n';
    return 1;
  }
  
  size_t ex2 = sizeof(s2);

  if(ex2 == 0)
  {
    std::cerr << "Invalid string";
    return 1;
  }

  char* buf2 = new char[ex2];
  if (buf2 == nullptr)
  {
    std::cerr << "Memory allocation fail" << '\n';
    delete[] s1;
    delete[] buf1;
    delete[] s2;
    return 1;
  }

  char* result = new char[ex + ex2];
  if (result == nullptr)
  {
    std::cerr << "Memory allocation fail" << '\n';
    delete[] s1;
    delete[] buf1;
    delete[] s2;
    delete[] buf2;
    return 1;
  }

  int ans_7 = lavrentev::dif_lat(buf1, s1);
  std::cout << "Ans 7: " << ans_7 << '\n';

  lavrentev::uni_two(s1, s2, ex, ex2, result);
  std::cout << "Ans 12: ";
  for (size_t i = 0; i < ex + ex2; ++i)
  {
    std::cout << result[i];
  }
  std::cout << '\n';

  delete[] s1;
  delete[] buf1;
  delete[] s2;
  delete[] buf2;
  delete[] result;
}

size_t lavrentev::dif_lat(char* buf1, char* s1)
{
  size_t ex = sizeof(s1);
  size_t answer = 0;

  for (size_t i = 0; i < ex; ++i)
  {
    buf1[i] = '#';
  }

  for (size_t i = 0; i < ex; ++i)
  {
    bool flag = false;
    for (size_t j = 0; j < ex; ++j)
    {
      if (buf1[j] == s1[i])
      {
        flag = true;
        break;
      }
    }

    if (!flag && isalpha(s1[i]))
    {
      buf1[i] = s1[i];
    }
  }

  for (size_t i = 0; i < ex; ++i)
  {
    if (buf1[i] != '#')
    {
      ++answer;
    }
  }

  return answer;
}

void lavrentev::uni_two(char* s1, char* s2, size_t ex, size_t ex2, char* result)
{
  size_t min;
  std::string max_s;
  if (ex < ex2)
  {
    min = ex;
    max_s = s2;
  }
  else
  {
    min = ex2;
    max_s = s1;
  }

  size_t t = 0;

  for (size_t i = 0; i < min; ++i)
  {
    result[t] =  s1[i];
    result[t + 1] =  s2[i];
    t += 2;
  }

  t = min;

  for (size_t i = min * 2; i < ex + ex2; ++i)
  {
    result[i] = max_s[min];
    ++min;
  }
}

char * lavrentev::getline(std::istream & in, size_t & n)
{
  bool is_skipws = in.flags() & std::ios_base::skipws;
  if (is_skipws)
  {
    in >> std::noskipws;
  }
  char * s = new char[1];
  char st;
  in >> st;
  size_t i = 0;
  while (st != '\n')
  {
    s[i] = st;
    ++i;
    if (i == sizeof(s))
    {
      std::string buf = "";
      size_t q = sizeof(s);
      for(size_t i = 0; i < q; ++i)
      {
        buf += s[i];
      }
      delete[] s;
      char * s = new char[q + q / 2];
      for(size_t i = 0; i < q + 1; ++i)
      {
        s[i] = buf[i];
      }
    }
    in >> st;
  }

  if(is_skipws)
  {
    in >> std::skipws;
  }

  n = sizeof(s);
  return s;
}
