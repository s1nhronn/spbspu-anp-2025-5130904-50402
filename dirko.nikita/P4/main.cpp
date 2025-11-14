#include <iostream>
#include <iomanip>
#include <cctype>
#include <algorithm>

namespace dirko
{
  char *myRealloc(char *mem, size_t oldSize, size_t newSize)
  {
    char *temp = reinterpret_cast<char *>(malloc(newSize));
    if (temp == nullptr)
    {
      free(mem);
      return nullptr;
    }
    for (size_t i = 0; i < oldSize; ++i)
    {
      temp[i] = mem[i];
    }
    for (size_t i = oldSize; i < newSize; ++i)
    {
      temp[i] = 0;
    }
    free(mem);
    return temp;
  }
  char *getLine(std::istream &in, size_t &size)
  {
    bool isSkipWp = in.flags() & std::ios::skipws;
    char *str = nullptr;
    char ch = 0;
    if (isSkipWp)
    {
      in >> std::noskipws;
    }
    while (in >> ch && ch != '\n')
    {
      str = myRealloc(str, size, size + 1);
      if (str == nullptr)
      {
        throw std::bad_alloc();
      }
      str[size] = ch;
      ++size;
    }
    if (in.fail())
    {
      free(str);
      throw std::logic_error("Cant read");
    }
    if (isSkipWp)
    {
      in >> std::skipws;
    }
    return str;
  }
  size_t DIF_LAT(const char *str, size_t size)
  {
    size_t count = 0;
    char seen[26] = {};
    for (size_t i = 0; i < size; ++i)
    {
      if (std::isalpha(str[i]))
      {
        if (std::find(seen, seen + count, str[i]) == seen + count)
        {
          seen[count] = str[i];
          ++count;
        }
      }
    }
    return count;
  }
  char *UPP_LOW(const char *source, char *distention, const size_t size)
  {
    for (size_t i = 0; i < size; ++i)
    {
      distention[i] = std::tolower(source[i]);
    }
    return distention;
  }
  std::ostream &output(std::ostream &out, const size_t result1, const char *result2)
  {
    out << result1 << '\n';
    return out << result2;
  }
}
int main()
{
  char *str = nullptr;
  size_t size = 0;
  try
  {
    str = dirko::getLine(std::cin, size);
  }
  catch (const std::bad_alloc &e)
  {
    std::cerr << "Cant alloc\n";
    return 1;
  }
  catch (const std::logic_error &e)
  {
    std::cerr << e.what() << "\n";
    return 1;
  }
  char *result2 = reinterpret_cast<char *>(malloc(sizeof(char) * size));
  if (result2 == nullptr)
  {
    free(str);
    std::cerr << "Cant alloc\n";
    return 1;
  }
  dirko::UPP_LOW(str, result2, size);
  size_t result1 = dirko::DIF_LAT(result2, size);
  dirko::output(std::cout, result1, result2) << '\n';
  free(str);
  free(result2);
}
