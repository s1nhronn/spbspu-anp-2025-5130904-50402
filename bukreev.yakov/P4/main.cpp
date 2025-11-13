#include <iostream>
#include <cstdlib>

namespace bukreev
{
  char* inputString();
  void deleteString(const char* str);
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
    std::cerr << "No memory" << '\n';
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
      //grow
    }

    std::cin >> buffer[i];
    if (buffer[i] == '\n')
    {
      break;
      i++;
      if (i >= capacity)
      {
        //grow
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