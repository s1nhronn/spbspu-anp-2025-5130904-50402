#include <iostream>
#include <iomanip>
#include <cstdlib>

namespace saldaev
{
  size_t getLine(std::istream &in, char *&data, const size_t block_size)
  {
    bool skipws_on = in.flags() & std::ios_base::skipws;
    if (skipws_on)
    {
      in >> std::noskipws;
    }
    data = static_cast< char * >(malloc(block_size * sizeof(char)));
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
        char *tmp = static_cast< char * >(malloc((crnt_msize + block_size) * sizeof(char)));
        if (tmp == nullptr)
        {
          return 0;
        }
        crnt_msize += block_size;
        for (size_t i = 0; i < crnt_size - 1; ++i)
        {
          tmp[i] = data[i];
        }
        free(data);
        data = tmp;
      }
      data[crnt_size - 1] = crnt_char;
    }
    if (skipws_on)
    {
      in >> std::skipws;
    }
    if (crnt_char == '\r' || crnt_char == '\n' || in.eof())
    {
      return crnt_size;
    }
    return 0;
  }

  size_t createCompactArray1(const char *data, const size_t length, char *&new_array)
  {
    char prev = ' ';
    char crnt = ' ';
    size_t leters = 0;
    size_t spaces = 0;
    for (size_t i = 0; i < length; ++i)
    {
      crnt = data[i];
      if (crnt != ' ')
      {
        leters++;
      }
      else if (prev != ' ' && crnt == ' ')
      {
        spaces++;
      }
      prev = crnt;
    }
    if (leters && crnt == ' ')
    {
      spaces--;
    }
    new_array = static_cast< char * >(malloc((leters + spaces) * sizeof(char)));
    if (new_array == nullptr)
    {
      return 0;
    }
    return (leters + spaces);
  }

  size_t spcRmv(char *arr, size_t length, char *&new_arr)
  {
    size_t new_length = createCompactArray(arr, length, new_arr);
    if (new_length == 0)
    {
      return 0;
    }
    size_t crnt_digit = 0;
    char crnt_char = ' ';
    char prev_char = ' ';
    size_t i = 0;
    while (crnt_digit < new_length)
    {
      crnt_char = arr[i];
      if (crnt_char != ' ' || prev_char != ' ')
      {
        new_arr[crnt_digit] = crnt_char;
        crnt_digit++;
      }
      i++;
      prev_char = crnt_char;
    }
    return new_length;
  }
}

int main()
{
  char *a = nullptr;
  size_t k = saldaev::getLine(std::cin, a, 10);
  if (k == 0)
  {
    std::cerr << "Could not read the string\n";
    return 1;
  }
  char *b = nullptr;
  k = saldaev::spcRmv(a, k, b);
  if (k == 0)
  {
    std::cerr << "Could not convert the string\n";
    return 1;
  }
  for (size_t i = 0; i < k; ++i)
  {
    std::cout << b[i];
  }
  std::cout << "\n";
  free(a);
  free(b);
}
