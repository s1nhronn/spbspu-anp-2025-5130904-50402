#include <cstdlib>
#include <cstring>
#include <ios>
#include <iostream>
#include <cstddef>
#include <istream>

namespace shirokov
{
  size_t LATIN_ALPHABET_LENGTH = 26;
  const int LETTER_DELTA = 32;
  const char LITERAL[] = "def ";
  char *uniq(char *res, const char *str, size_t &rsize);
  void expand(char **str, size_t size, size_t &capacity);
  char *getline(std::istream &in, size_t &s);
  char *otherLatinLetters(const char *str, char *res, char *buffer);
  void combineLines(const char *str1, size_t s1, const char *str2, size_t s2, char *res);
}

int main()
{
  size_t s = 0;
  char *str = shirokov::getline(std::cin, s);

  if (str == nullptr)
  {
    free(str);
    std::cerr << "Couldn't read the line\n";
    return 1;
  }

  char *res1 = reinterpret_cast< char * >(malloc((shirokov::LATIN_ALPHABET_LENGTH + 1) * sizeof(char)));
  char *res2 = reinterpret_cast< char * >(malloc((std::strlen(shirokov::LITERAL) + s + 1) * sizeof(char)));
  if (res1 == nullptr || res2 == nullptr)
  {
    free(str);
    free(res1);
    free(res2);
    std::cerr << "Memory allocation error\n";
    return 1;
  }
  res1[shirokov::LATIN_ALPHABET_LENGTH] = '\0';
  res2[std::strlen(shirokov::LITERAL) + s] = '\0';
  char *buffer = reinterpret_cast< char * >(malloc(sizeof(char) * s));
  if (buffer == nullptr)
  {
    free(str);
    free(res1);
    free(res2);
    std::cerr << "Memory allocation error\n";
    return 1;
  }
  shirokov::otherLatinLetters(str, res1, buffer);
  shirokov::combineLines(str, s, shirokov::LITERAL, std::strlen(shirokov::LITERAL), res2);
  if (res1 == nullptr || res2 == nullptr)
  {
    free(str);
    free(res1);
    free(res2);
    std::cerr << "Error during conversion\n";
    return 1;
  }

  std::cout << "1. " << res1 << '\n';
  std::cout << "2. " << res2 << '\n';
  free(str);
  free(res1);
  free(res2);
}

char *shirokov::getline(std::istream &in, size_t &s)
{
  bool is_skipws = in.flags() & std::ios_base::skipws;
  if (is_skipws)
  {
    in >> std::noskipws;
  }
  size_t capacity = 1;
  s = 0;
  char *str = reinterpret_cast< char * >(malloc(capacity * sizeof(char)));
  if (str == nullptr)
  {
    if (is_skipws)
    {
      in >> std::skipws;
    }
    return nullptr;
  }
  while (in)
  {
    if (s == capacity)
    {
      shirokov::expand(&str, s, capacity);
    }
    if (str == nullptr)
    {
      if (is_skipws)
      {
        in >> std::skipws;
      }
      return nullptr;
    }
    in >> str[s];
    if (!in || str[s] == '\0')
    {
      break;
    }
    s++;
  }
  if (in.bad() || s == 0)
  {
    free(str);
    if (is_skipws)
    {
      in >> std::skipws;
    }
    return nullptr;
  }
  str[s] = '\0';
  if (is_skipws)
  {
    in >> std::skipws;
  }
  return str;
}

char *shirokov::otherLatinLetters(const char *str, char *res, char *buffer)
{
  size_t rsize = 0;
  char *ustr = uniq(buffer, str, rsize);
  size_t pos = 0;
  for (char letter = 'a'; letter <= 'z'; ++letter)
  {
    bool in_str = false;
    for (size_t i = 0; i < rsize; ++i)
    {
      if (ustr[i] == letter)
      {
        in_str = true;
        break;
      }
    }
    if (!in_str)
    {
      res[pos++] = letter;
    }
  }
  res[pos] = '\0';
  free(ustr);
  return res;
}

void shirokov::combineLines(const char *str1, size_t s1, const char *str2, size_t s2, char *res)
{
  size_t minn = s1 < s2 ? s1 : s2;
  for (size_t i = 0; i < minn; ++i)
  {
    res[2 * i] = str1[i];
    res[2 * i + 1] = str2[i];
  }
  for (size_t i = minn * 2; i < s1 + s2; ++i)
  {
    res[i] = (s1 > s2 ? str1[i - minn] : str2[i - minn]);
  }
}

char *shirokov::uniq(char *res, const char *str, size_t &rsize)
{
  rsize = 0;
  for (size_t i = 0; str[i] != '\0'; ++i)
  {
    bool in_res = false;
    char temp = str[i];
    if ('A' <= temp && temp <= 'Z')
    {
      temp += shirokov::LETTER_DELTA;
    }
    for (size_t j = 0; j < rsize; ++j)
    {
      if (temp == res[j])
      {
        in_res = true;
      }
    }
    if (!in_res)
    {
      char temp = str[i];
      if ('A' <= temp && temp <= 'Z')
      {
        temp += 32;
      }
      res[rsize++] = temp;
    }
  }
  return res;
}

void shirokov::expand(char **str, size_t size, size_t &capacity)
{
  char *temp_str = nullptr;
  temp_str = reinterpret_cast< char * >(malloc(capacity * 2));
  if (temp_str == nullptr)
  {
    *str = nullptr;
    return;
  }
  for (size_t i = 0; i < size; ++i)
  {
    temp_str[i] = (*str)[i];
  }
  free(*str);
  *str = temp_str;
  capacity *= 2;
}
