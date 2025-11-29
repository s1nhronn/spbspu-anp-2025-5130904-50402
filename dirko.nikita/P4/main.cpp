#include <iostream>
#include <iomanip>
#include <cctype>
#include <cstring>

namespace dirko
{
  const size_t alphaSize = 26;
  const char *find(const char *start, const char *end, char target)
  {
    for (const char *ch = start; ch < end; ++ch)
    {
      if (*ch == target)
      {
        return ch;
      }
    }
    return end;
  }
  void extendSize(char *&str, size_t size)
  {
    char *newStr = reinterpret_cast<char *>(malloc(size * 2 * sizeof(char)));
    if (newStr == nullptr)
    {
      free(str);
      str = nullptr;
      return;
    }
    std::strncpy(newStr, str, size);
    for (size_t i = size; i < size * 2; ++i)
    {
      newStr[i] = '\0';
    }
    free(str);
    str = newStr;
  }
  std::istream &getLine(std::istream &in, char *&str, size_t &size, size_t &copasity)
  {
    bool isSkipWp = in.flags() & std::ios::skipws;
    if (isSkipWp)
    {
      in >> std::noskipws;
    }
    str = reinterpret_cast<char *>(malloc(sizeof(char) * copasity));
    if (str == nullptr)
    {
      return in;
    }
    char ch = 0;
    while (in >> ch && ch != '\n')
    {
      if (size == copasity)
      {
        extendSize(str, size);
        copasity *= 2;
      }
      str[size++] = ch;
    }
    if (isSkipWp)
    {
      in >> std::skipws;
    }
    if (size == copasity)
    {
      extendSize(str, size);
      copasity *= 2;
    }
    ++size;
    return in;
  }
  size_t doDifLat(const char *str, size_t size)
  {
    size_t count = 0;
    char seen[alphaSize] = {};
    for (size_t i = 0; i < size; ++i)
    {
      if (std::isalpha(str[i]))
      {
        if (dirko::find(seen, seen + count, std::tolower(str[i])) == seen + count)
        {
          seen[count] = std::tolower(str[i]);
          ++count;
        }
      }
    }
    return count;
  }
  char *doUppLow(const char *source, char *distention, size_t size)
  {
    for (size_t i = 0; i < size; ++i)
    {
      distention[i] = (std::isalpha(source[i])) ? std::tolower(source[i]) : source[i];
    }
    return distention;
  }
}
int main()
{
  char *str = nullptr;
  size_t size = 0, copasity = 1;
  dirko::getLine(std::cin, str, size, copasity);
  if (str == nullptr)
  {
    std::cerr << "Cant alloc\n";
    return 1;
  }
  if (std::cin.fail())
  {
    free(str);
    std::cerr << "Cant read\n";
    return 1;
  }
  if (size == 1)
  {
    free(str);
    std::cerr << "Empty string\n";
    return 1;
  }
  size_t result1 = dirko::doDifLat(str, size);
  char *result2 = reinterpret_cast<char *>(malloc(sizeof(char) * size));
  if (result2 == nullptr)
  {
    free(str);
    std::cerr << "Cant alloc\n";
    return 1;
  }
  dirko::doUppLow(str, result2, size);
  std::cout << result1 << '\n';
  std::cout << result2 << '\n';
  free(str);
  free(result2);
}
