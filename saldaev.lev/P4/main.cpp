#include <iostream>
#include <iomanip>
#include <cstdlib>

namespace saldaev
{
  const size_t block_size = 10;

  size_t getLine(std::istream &in, char *&data, const size_t block_size)
  {
    in >> std::noskipws;
    data = static_cast< char * >(malloc(block_size + 1 * sizeof(char)));
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
        char *tmp = static_cast< char * >(malloc(crnt_size + block_size + 1 * sizeof(char)));
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

  size_t createCompactString(char *arr, size_t length, char *&new_arr)
  {
    char previous = ' ';
    char curent = ' ';
    size_t leters = 0;
    size_t spaces = 0;
    for (size_t i = 0; i < length - 1; ++i)
    {
      curent = arr[i];
      if (curent != ' ')
      {
        leters++;
      }
      else if(previous != ' ')
      {
        spaces++;
      }
      previous = curent;
    }
    if (leters && curent == ' ')
    {
      spaces--;
    }
    new_arr = static_cast< char * >(malloc((leters + spaces + 1) * sizeof(char)));
    if (new_arr == nullptr)
    {
      return 0;
    }
    return (leters + spaces + 1);
  }

  size_t spcRmv(char *arr, size_t length, char *&new_arr)
  {
    size_t new_length = createCompactString(arr, length, new_arr);
    if (new_length == 0)
    {
      return 0;
    }
    char prev_char = ' ';
    char crnt_char = ' ';
    size_t i = 0;
    size_t crnt_digit = 0;
    while (crnt_digit < new_length - 1)
    {
      crnt_char = arr[i];
      if (crnt_char != ' ' || prev_char != ' ')
      {
        new_arr[crnt_digit] = crnt_char;
        crnt_digit++;
      }
      prev_char = crnt_char;
      i++;
    }
    new_arr[crnt_digit] = '\0';
    return new_length;
  }
}

int main()
{
  char *a = nullptr;
  size_t k = saldaev::getLine(std::cin, a, saldaev::block_size);
  char *b = nullptr;
  k = saldaev::spcRmv(a, k, b);
  for (size_t i = 0; i < k - 1; ++i)
  {
    std::cout << b[i] << '\n';
  }
  free(a);
  free(b);
}
