#include <cmath>
#include <cstdlib>
#include <cstring>
#include <ios>
#include <iostream>
#include <cstddef>
#include <istream>

namespace shirokov
{
  constexpr size_t LATIN_ALPHABET_LENGTH = 26;
  constexpr int CASE_DELTA = 32;
  constexpr char LITERAL[] = "def ";
  char *uniq(char *res, const char *str, size_t &rsize);
  void expand(char **str, size_t size, size_t &capacity);
  void expand(char ***str, size_t size, size_t &capacity);
  char **getline(std::istream &in, size_t &size, bool (*isDelimiter)(char symbol));
  char *otherLatinLetters(const char *str, char *res, char *buffer);
  char *combineLines(const char *str1, size_t s1, const char *str2, size_t s2, char *res);
  double getCoefficient(size_t capacity);
  bool isSpace(char symbol);
}

void printMassive(const char *const *massive, size_t s, const char *str)
{
  std::cout << "Массив:\n";
  for (size_t i = 0; i < s; ++i)
  {
    std::cout << massive[i] << '\n';
  }
  std::cout << "Строка:\n";
  std::cout << str << "\n\n";
}

int main()
{
  size_t s = 0;
  char **massive = shirokov::getline(std::cin, s, shirokov::isSpace); // FIXME: Leak_DefinitelyLost

  if (massive == nullptr || s == 0)
  {
    std::cerr << "Couldn't read the line\n";
    return 1;
  }

  for (size_t i = 0; i < s; ++i)
  {
    size_t length = 0;
    for (; massive[i][length] != '\0'; ++length) // FIXME: InvalidRead
    {
    }
    char *res1 = reinterpret_cast< char * >(malloc((shirokov::LATIN_ALPHABET_LENGTH + 1) * sizeof(char)));
    char *res2 = reinterpret_cast< char * >(malloc((std::strlen(shirokov::LITERAL) + length + 1) * sizeof(char)));
    if (res1 == nullptr || res2 == nullptr)
    {
      for (size_t j = 0; j < s; ++j)
      {
        free(massive[j]);
      }
      free(massive);
      free(res1);
      free(res2);
      std::cerr << "Memory allocation error\n";
      return 1;
    }
    char *buffer = reinterpret_cast< char * >(malloc(sizeof(char) * (length + 1)));
    if (buffer == nullptr)
    {
      for (size_t j = 0; j < s; ++j)
      {
        free(massive[j]);
      }
      free(massive);
      free(res1);
      free(res2);
      std::cerr << "Memory allocation error\n";
      return 1;
    }
    res1[shirokov::LATIN_ALPHABET_LENGTH] = '\0';
    res2[std::strlen(shirokov::LITERAL) + length] = '\0';
    buffer[length] = '\0';
    res1 = shirokov::otherLatinLetters(massive[i], res1, buffer);
    res2 = shirokov::combineLines(massive[i], length, shirokov::LITERAL, std::strlen(shirokov::LITERAL), res2);

    std::cout << "String: " << massive[i] << '\n'; // FIXME: InvalidRead
    std::cout << "\t1. " << res1 << '\n';
    std::cout << "\t2. " << res2 << '\n';
    free(res1);
    free(res2);
    free(buffer);
  }
  for (size_t i = 0; i < s; ++i)
  {
    free(massive[i]);
  }
  free(massive);
}

char **shirokov::getline(std::istream &in, size_t &size, bool (*isDelimiter)(char symbol))
{
  bool is_skipws = in.flags() & std::ios_base::skipws;
  if (is_skipws)
  {
    in >> std::noskipws;
  }
  char **massive = reinterpret_cast< char ** >(malloc(sizeof(char *)));
  size_t capacity = 1;
  size = 0;
  char *str = reinterpret_cast< char * >(malloc(sizeof(char)));
  size_t cap = 1;
  size_t s = 0;
  if (massive == nullptr || str == nullptr)
  {
    for (size_t i = 0; i < size; ++i)
    {
      free(massive[i]);
    }
    free(massive);
    free(str);
    if (is_skipws)
    {
      in >> std::skipws;
    }
    return nullptr;
  }
  while (in)
  {
    // std::cout << "=== ИТЕРАЦИЯ ===\n";
    // std::cout << "До расширения\n";
    // printMassive(massive, size, str);
    if (size == capacity)
    {
      expand(&massive, size, capacity);
    }
    if (s == cap)
    {
      expand(&str, s, cap);
    }
    // std::cout << "После расширения и до ввода\n";
    // printMassive(massive, size, str);
    if (massive == nullptr || str == nullptr)
    {
      for (size_t i = 0; i < size; ++i)
      {
        free(massive[i]);
      }
      free(massive);
      free(str);
      if (is_skipws)
      {
        in >> std::skipws;
      }
      return nullptr;
    }
    in >> str[s];
    if (!in || str[s] == '\0')
    {
      if (s > 0)
      {
        massive[size++] = str;
      }
      else
      {
        free(str);
      }
      break;
    }
    bool flag = isDelimiter(str[s]);
    if (flag)
    {
      if (s > 0)
      {
        str[s] = '\0';
        massive[size++] = str;
      }
      else
      {
        free(str);
      }
      str = reinterpret_cast< char * >(malloc(sizeof(char)));
      cap = 1;
      s = 0;
    }
    // std::cout << "После ввода\n";
    // printMassive(massive, size, str);
    if (!flag)
    {
      s++;
    }
  }
  if (is_skipws)
  {
    in >> std::skipws;
  }
  return massive;
}

char *shirokov::otherLatinLetters(const char *str, char *res, char *buffer)
{
  size_t rsize = 0;
  buffer = uniq(buffer, str, rsize);
  size_t pos = 0;
  for (char letter = 'a'; letter <= 'z'; ++letter)
  {
    bool in_str = false;
    for (size_t i = 0; i < rsize; ++i)
    {
      if (buffer[i] == letter)
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
  return res;
}

char *shirokov::combineLines(const char *str1, size_t s1, const char *str2, size_t s2, char *res)
{
  size_t minn = s1 < s2 ? s1 : s2;
  for (size_t i = 0; i < minn; ++i)
  {
    res[2 * i] = str1[i];
    res[2 * i + 1] = str2[i];
  }
  const char *maxString = s1 > s2 ? str1 : str2;
  for (size_t i = minn * 2; i < s1 + s2; ++i)
  {
    res[i] = maxString[i - minn];
  }
  return res;
}

char *shirokov::uniq(char *res, const char *str, size_t &rsize)
{
  rsize = 0;
  for (size_t i = 0; str[i] != '\0'; ++i) // FIXME: InvalidRead
  {
    bool in_res = false;
    char temp = str[i];
    if ('A' <= temp && temp <= 'Z')
    {
      temp += CASE_DELTA;
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
      res[rsize++] = temp;
    }
  }
  return res;
}

void shirokov::expand(char **str, size_t size, size_t &capacity)
{
  double coefficient = getCoefficient(capacity);
  size_t newCapacity = static_cast< size_t >(capacity * coefficient);
  char *tempString = reinterpret_cast< char * >(malloc(newCapacity * sizeof(char)));
  if (tempString == nullptr)
  {
    free(*str);
    *str = nullptr;
    return;
  }
  for (size_t i = 0; i < size; ++i)
  {
    tempString[i] = (*str)[i];
  }
  free(*str);
  *str = tempString;
  capacity = newCapacity;
}

double shirokov::getCoefficient(size_t capacity)
{
  if (capacity < 10)
  {
    return 2;
  }
  if (capacity < 100)
  {
    return 1.5;
  }
  return 1.1 + 1 / std::pow(capacity + 1, 0.2);
}

void shirokov::expand(char ***str, size_t size, size_t &capacity)
{
  double coefficient = getCoefficient(capacity);
  size_t newCapacity = static_cast< size_t >(capacity * coefficient);
  char **tempMassive = reinterpret_cast< char ** >(malloc(newCapacity * sizeof(char *)));
  if (tempMassive == nullptr)
  {
    for (size_t i = 0; i < size; ++i)
    {
      free((*str)[i]);
    }
    free(*str);
    *str = nullptr;
    return;
  }
  for (size_t i = 0; i < size; ++i)
  {
    size_t len = std::strlen((*str)[i]);
    char *tempString = static_cast< char * >(malloc(len + 1));
    size_t cap = 1;
    size_t j = 0;
    for (; (*str)[i][j] != '\0'; ++j) // FIXME: InvalidRead
    {
      tempString[j] = (*str)[i][j];
    }
    tempString[j] = '\0'; // FIXME: InvalidWrite
    free((*str)[i]);
    tempMassive[i] = tempString;
  }
  free(*str);
  *str = tempMassive;
  capacity = newCapacity;
}

bool shirokov::isSpace(char symbol)
{
  if (symbol == ' ' || symbol == '\t' || symbol == '\n')
  {
    return true;
  }
  return false;
}
