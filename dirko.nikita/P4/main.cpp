#include <iostream>
#include <iomanip>
#include <cctype>

namespace dirko
{
  char *getLine(std::istream &in, size_t &size)
  {
    bool isSkipWp = in.flags() & std::ios::skipws;
    char *str = nullptr;
    char ch = 0;
    if (str == nullptr)
    {
      throw std::bad_alloc();
    }
    if (isSkipWp)
    {
      in >> std::noskipws;
    }
    while (in >> ch && ch != '\n')
    {
      char *temp = reinterpret_cast<char *>(realloc(str, size + 1));
      if (temp == nullptr)
      {
        free(str);
        throw std::bad_alloc();
      }
      str = temp;
      str[size++] = ch;
    }
    if (in.fail())
    {
      throw std::logic_error("Cant read");
    }
    if (isSkipWp)
    {
      in >> std::skipws;
    }
    return str;
  }
  size_t DIF_LAT(const char *str);
  char *UPP_LOW(const char *source, char *distention, size_t size)
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
  size_t result1 = dirko::DIF_LAT(str);
  char *result2 = nullptr;
  result2 = reinterpret_cast<char *>(malloc(sizeof(char) * size));
  dirko::UPP_LOW(str, result2, size);
  dirko::output(std::cout, result1, result2) << '\n';
  free(str);
  free(result2);
}
