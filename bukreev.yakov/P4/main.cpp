#include <iostream>
#include <cstdlib>
#include <cstring>

namespace bukreev
{
  constexpr size_t initialSize = 4;

  std::istream& inputString(std::istream& in, char** str);

  char* growString(char** oldStr, size_t& capacity);

  char* excsnd(const char* first, const char* second, char* resStr);
  char* latrmv(const char* str, char* resStr);
}

int main()
{
  char* str = nullptr;

  bukreev::inputString(std::cin, &str);
  if (!str)
  {
    std::cerr << "Not enough memory for string input.\n";
    return 1;
  }

  char* res1 = nullptr, *res2 = nullptr;
  size_t allocSize = (std::strlen(str) + 1) * sizeof(char);

  res1 = reinterpret_cast< char* >(malloc(allocSize));
  res1[allocSize - 1] = '\0';
  if (!res1)
  {
    std::cerr << "Not enough memory for EXC_SND.\n";
    free(str);
    return 1;
  }

  res2 = reinterpret_cast< char* >(malloc(allocSize));
  res2[allocSize - 1] = '\0';
  if (!res2)
  {
    std::cerr << "Not enough memory for LAT_RMV.\n";
    free(str);
    free(res1);
    return 1;
  }

  const char* stringToExclude = "abc";

  res1 = bukreev::excsnd(str, stringToExclude, res1);
  res2 = bukreev::latrmv(str, res2);

  free(str);

  std::cout << res1 << '\n';
  std::cout << res2 << '\n';

  free(res1);
  free(res2);
}

std::istream& bukreev::inputString(std::istream& in, char** str)
{
  size_t capacity = initialSize;
  *str = nullptr;

  char* buffer = reinterpret_cast< char* >(malloc(initialSize * sizeof(char)));
  if (!buffer)
  {
    return in;
  }

  in >> std::noskipws;

  size_t i = 0;
  while (in)
  {
    if (i >= capacity)
    {
      buffer = growString(&buffer, capacity);
      if (!buffer)
      {
        return in;
      }
    }

    buffer[i] = '\0';
    in >> buffer[i];
    if (buffer[i] == '\n')
    {
      buffer[i] = '\0';
      break;
    }

    i++;
  }
  if (!in)
  {
    if (in.eof())
    {
      buffer[i - 1] = '\0';
    }
    else
    {
      free(buffer);
      return in;
    }
  }
  if (std::strlen(buffer) == 0)
  {
    free(buffer);
    return in;
  }

  in >> std::skipws;
  *str = buffer;
  return in;
}

char* bukreev::growString(char** oldStr, size_t& capacity)
{
  const double growRatio = 1.5;

  size_t oldCapacity = capacity;
  size_t newCapacity = oldCapacity * growRatio;

  char* newStr = reinterpret_cast< char* >(malloc(newCapacity * sizeof(char)));
  if (!newStr)
  {
    free(*oldStr);
    return nullptr;
  }

  capacity = newCapacity;
  std::strncpy(newStr, *oldStr, oldCapacity);

  free(*oldStr);
  *oldStr = newStr;

  return newStr;
}

char* bukreev::excsnd(const char* first, const char* second, char* resStr)
{
  size_t resIndex = 0;

  for (size_t i = 0; first[i] != '\0'; i++)
  {
    char c = first[i];
    bool exclude = false;

    for (size_t j = 0; second[j] != '\0'; j++)
    {
      if (second[j] == c)
      {
        exclude = true;
        break;
      }
    }

    if (!exclude)
    {
      resStr[resIndex] = c;
      resIndex++;
    }
  }

  resStr[resIndex] = 0;

  return resStr;
}

char* bukreev::latrmv(const char* str, char* resStr)
{
  size_t resIndex = 0;

  for (size_t i = 0; str[i] != '\0'; i++)
  {
    if (!std::isalpha(str[i]))
    {
      resStr[resIndex] = str[i];
      resIndex++;
    }
  }

  resStr[resIndex] = '\0';

  return resStr;
}
