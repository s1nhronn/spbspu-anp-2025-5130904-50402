#include <iostream>
#include <cstdlib>
#include <cstring>

namespace bukreev
{
  const size_t initialSize = 4;

  char* inputString();
  void deleteString(char* str);

  char* growString(char** oldStr, size_t& capacity);

  char* excsnd(const char* first, const char* second, char* resStr);
  char* latrmv(const char* str, char* resStr);
}

int main()
{
  char* str = nullptr;

  str = bukreev::inputString();
  if (!str)
  {
    std::cerr << "Not enough memory for string input.\n";
    return 1;
  }

  if (std::strlen(str) == 0)
  {
    bukreev::deleteString(str);
    std::cerr << "Error: no input.\n";
    return 2;
  }

  char* res1 = nullptr, *res2 = nullptr;
  res1 = reinterpret_cast< char* >(malloc((std::strlen(str) + 1) * sizeof(char)));
  if (!res1)
  {
    std::cerr << "Not enough memory for EXC_SND.\n";
    bukreev::deleteString(str);
    return 1;
  }

  res2 = reinterpret_cast< char* >(malloc((std::strlen(str) + 1) * sizeof(char)));
  if (!res2)
  {
    std::cerr << "Not enough memory for LAT_RMV.\n";
    bukreev::deleteString(res1);
    bukreev::deleteString(str);
    return 1;
  }

  const char* stringToExclude = "abc";

  res1 = bukreev::excsnd(str, stringToExclude, res1);
  res2 = bukreev::latrmv(str, res2);

  bukreev::deleteString(str);

  std::cout << res1 << '\n';
  std::cout << res2 << '\n';

  bukreev::deleteString(res1);
  bukreev::deleteString(res2);
}

char* bukreev::inputString()
{
  size_t capacity = initialSize;

  char* buffer = reinterpret_cast< char* >(malloc(initialSize * sizeof(char)));
  if (!buffer)
  {
    return nullptr;
  }

  std::cin >> std::noskipws;

  size_t i = 0;
  bool run = true;
  while (run)
  {
    if (i >= capacity)
    {
      buffer = growString(&buffer, capacity);
      if (!buffer)
      {
        return nullptr;
      }
    }

    std::cin >> buffer[i];
    if (std::cin.eof())
    {
      buffer[i] = 0;
      break;
    }

    if (buffer[i] == '\n')
    {
      buffer[i] = 0;
      run = false;
    }

    i++;
  }

  std::cin >> std::skipws;

  return buffer;
}

void bukreev::deleteString(char* str)
{
  free(str);
}

char* bukreev::growString(char** oldStr, size_t& capacity)
{
  const double growRatio = 1.5;

  size_t oldCapacity = capacity;
  size_t newCapacity = oldCapacity * growRatio;

  char* newStr = reinterpret_cast< char* >(malloc(newCapacity * sizeof(char)));
  if (!newStr)
  {
    deleteString(*oldStr);
    return nullptr;
  }

  capacity = newCapacity;
  std::strncpy(newStr, *oldStr, oldCapacity);

  deleteString(*oldStr);
  *oldStr = newStr;

  return newStr;
}

char* bukreev::excsnd(const char* first, const char* second, char* resStr)
{
  size_t resIndex = 0;

  for (size_t i = 0; first[i] != 0; i++)
  {
    char c = first[i];
    bool exclude = false;

    for (size_t j = 0; second[j] != 0; j++)
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

  for (size_t i = 0; str[i] != 0; i++)
  {
    if (!std::isalpha(str[i]))
    {
      resStr[resIndex] = str[i];
      resIndex++;
    }
  }

  resStr[resIndex] = 0;

  return resStr;
}
