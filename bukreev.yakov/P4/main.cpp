#include <iostream>
#include <cstdlib>
#include <cstring>

namespace bukreev
{
  char* inputString();
  void deleteString(const char* str);

  char* growString(const char* oldStr, size_t* capacity);
}

int main()
{
  char* str = nullptr;

  try
  {
    str = bukreev::inputString();
  }
  catch(const std::bad_alloc& e)
  {
    std::cerr << "Not enough memory.\n";
    return 1;
  }

  bukreev::deleteString(str);
}

char* bukreev::inputString()
{
  const size_t initialSize = 4;

  size_t capacity = initialSize;

  char* buffer = reinterpret_cast<char*>(malloc(initialSize * sizeof(char)));
  if (!buffer)
  {
    throw std::bad_alloc();
  }

  std::cin >> std::noskipws;

  size_t i = 0;
  while (true)
  {
    if (i >= capacity)
    {
      buffer = growString(buffer, &capacity);
    }

    std::cin >> buffer[i];
    if (buffer[i] == '\n')
    {
      i++;
      if (i >= capacity)
      {
        buffer = growString(buffer, &capacity);
      }

      buffer[i] = 0;
      break;
    }

    i++;
  }

  return buffer;
}

void bukreev::deleteString(const char* str)
{
  free(const_cast<char*>(str));
}

char* bukreev::growString(const char* oldStr, size_t* capacity)
{
  const double growRatio = 1.5;

  size_t oldCapacity = *capacity;
  size_t newCapacity = oldCapacity * growRatio;

  *capacity = newCapacity;

  char* newStr = reinterpret_cast<char*>(malloc(newCapacity * sizeof(char)));
  if (!newStr)
  {
    deleteString(oldStr);
    throw std::bad_alloc();
  }

  std::strncpy(newStr, oldStr, oldCapacity);

  deleteString(oldStr);

  return newStr;
}