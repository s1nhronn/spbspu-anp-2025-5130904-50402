#include <cstdlib>
#include <cstring>
#include <ios>
#include <iostream>
#include <cstddef>
#include <istream>

namespace shirokov
{
  size_t LATIN_ALPHABET_LENGTH = 26;
  const char LITERAL[] = "def ";
  char *uniq(const char *str, size_t s, size_t &rsize);
  void expand(char **str, size_t size, size_t &capacity);
  char *getline(std::istream &in, size_t &s);
  void SHR_SYM(const char *str, size_t s, char *res);
  void UNI_TWO(const char *str1, size_t s1, const char *str2, size_t s2, char *res);
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

  char *res1 = static_cast< char * >(malloc((shirokov::LATIN_ALPHABET_LENGTH) * sizeof(char)));
  char *res2 = static_cast< char * >(malloc((std::strlen(shirokov::LITERAL) + s) * sizeof(char)));
  if (res1 == nullptr || res2 == nullptr)
  {
    free(str);
    free(res1);
    free(res2);
    std::cerr << "Memory allocation error\n";
    return 1;
  }

  shirokov::SHR_SYM(str, s, res1);
  shirokov::UNI_TWO(str, s, shirokov::LITERAL, std::strlen(shirokov::LITERAL), res2);
  if (res1 == nullptr || res2 == nullptr)
  {
    free(str);
    free(res1);
    free(res2);
    std::cerr << "Error during conversion\n";
    return 1;
  }

  std::cout << "1. " << "res1" << '\n';
  std::cout << "2. " << "res2" << '\n';
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
  char *str = static_cast< char * >(malloc(capacity * sizeof(char)));
  if (str == nullptr)
  {
    return nullptr;
  }
  while (in)
  {
    shirokov::expand(&str, s, capacity);
    if (str == nullptr)
    {
      return nullptr;
    }
    in >> str[s];
    if (in.eof())
    {
      break;
    }
    s += 1;
  }
  if (in.bad() || s == 0)
  {
    return nullptr;
  }
  str[s] = '\0';
  if (is_skipws)
  {
    in >> std::skipws;
  }
  return str;
}

void shirokov::SHR_SYM(const char *str, size_t s, char *res)
{
  (void) str;
  (void) s;
  (void) res;
  return;
}

void shirokov::UNI_TWO(const char *str1, size_t s1, const char *str2, size_t s2, char *res)
{
  (void) str1;
  (void) s1;
  (void) str2;
  (void) s2;
  (void) res;
  return;
}

char *shirokov::uniq(const char *str, size_t s, size_t &rsize)
{
  (void) str;
  (void) s;
  (void) rsize;
  return nullptr;
}

void shirokov::expand(char **str, size_t size, size_t &capacity)
{
  char *temp_str = nullptr;
  if (size == capacity)
  {
    capacity *= 2;
    temp_str = static_cast< char * >(malloc(capacity));
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
  }
}
