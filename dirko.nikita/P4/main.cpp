#include <iostream>
#include <iomanip>
#include <cctype>

namespace dirko
{
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
  std::istream &getSize(std::istream &in, size_t &size)
  {
    bool isSkipWp = in.flags() & std::ios::skipws;
    if (isSkipWp)
    {
      in >> std::noskipws;
    }
    std::streampos pos = in.tellg();
    char ch = 0;
    while (in >> ch && ch != '\n')
    {
      ++size;
    }
    in.seekg(pos);
    if (isSkipWp)
    {
      in >> std::skipws;
    }
    return in;
  }
  void getLine(std::istream &in, char *str, const size_t size)
  {
    bool isSkipWp = in.flags() & std::ios::skipws;
    if (isSkipWp)
    {
      in >> std::noskipws;
    }
    for (size_t i = 0; i < size; ++i)
    {
      in >> str[i];
    }
    if (isSkipWp)
    {
      in >> std::skipws;
    }
  }
  size_t doDifLat(const char *str, const size_t size)
  {
    size_t count = 0;
    char seen[26] = {};
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
  char *doUppLow(const char *source, char *distention, const size_t size)
  {
    for (size_t i = 0; i < size; ++i)
    {
      distention[i] = std::tolower(source[i]);
    }
    return distention;
  }
}
int main()
{
  char *str = nullptr;
  size_t size = 0;
  dirko::getSize(std::cin, size);
  if (std::cin.fail())
  {
    std::cerr << "Cant read\n";
    return 1;
  }
  str = reinterpret_cast< char * >(malloc(sizeof(char) * (size + 1)));
  if (str == nullptr)
  {
    std::cerr << "Cant alloc\n";
    return 1;
  }
  str[size] = '\0';
  dirko::getLine(std::cin, str, size);
  size_t result1 = dirko::doDifLat(str, size);
  char *result2 = reinterpret_cast< char * >(malloc(sizeof(char) * size));
  if (result2 == nullptr)
  {
    free(str);
    std::cerr << "Cant alloc\n";
    return 1;
  }
  dirko::doUppLow(str, result2, size);
  std::cout << result1 << '\n';
  std::cout << result2;
  free(str);
  free(result2);
}
