#include <iostream>
#include <iomanip>
#include <cstdlib>

namespace saldaev
{
  const size_t block_size = 10;
  
  size_t getline(std::istream &in, char *&data, const size_t block_size)
  {
    in >> std::noskipws;
    data = static_cast<char *>(malloc(block_size + 1 * sizeof(char)));
    if (data == nullptr)
    {
      return 0;
    }

    size_t crnt_msize = block_size;
    size_t crnt_size = 0;
    char crnt_char = ' ';
    while (in >> crnt_char && crnt_char != '\r' && crnt_char != '\n')
    {
      crnt_size++;
      if (crnt_size > crnt_msize)
      {
        char *tmp = static_cast<char *>(malloc(crnt_size + block_size + 1 * sizeof(char)));
        if (tmp == nullptr)
        {
          return 0;
        }
        crnt_msize += block_size;
        for (size_t i = 0; i < crnt_size; ++i)
        {
          tmp[i] = data[i];
        }
        free(data);
        data = tmp;
      }
      data[crnt_size - 1] = crnt_char;
    }
    if (crnt_char == '\r' || crnt_char == '\n' || in.eof())
    {
      data[crnt_size] = '\0';
      return crnt_size + 1;
    }
    return 0;
  }
}

int main()
{
  char *a = nullptr;
  size_t k = saldaev::getline(std::cin, a, saldaev::block_size);
  for (size_t i = 0; i < k; ++i)
  {
    std::cout << a[i];
  }
  free(a);
}
