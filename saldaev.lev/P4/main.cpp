#include <iostream>
#include <iomanip>
#include <cstdlib>

namespace saldaev
{
  const size_t block_size = 10;
  size_t getLine(std::istream &in, char *&data, const size_t block_size)
  {
    data = reinterpret_cast< char * >(malloc(block_size * sizeof(char)));
    if (data == nullptr)
    {
      return 0;
    }
    bool skipws_on = in.flags() & std::ios_base::skipws;
    if (skipws_on)
    {
      in >> std::noskipws;
    }

    size_t capacity = block_size;
    size_t size = 0;
    char crnt_char = ' ';
    while (in >> crnt_char && crnt_char != '\r' && crnt_char != '\n')
    {
      size++;
      if (size > capacity)
      {
        char *tmp = reinterpret_cast< char * >(malloc((capacity + block_size) * sizeof(char)));
        if (tmp == nullptr)
        {
          free(data);
          if (skipws_on)
          {
            in >> std::skipws;
          }
          return 0;
        }
        capacity += block_size;
        for (size_t i = 0; i < size - 1; ++i)
        {
          tmp[i] = data[i];
        }
        free(data);
        data = tmp;
      }
      data[size - 1] = crnt_char;
    }
    if (skipws_on)
    {
      in >> std::skipws;
    }
    if (crnt_char == '\r' || crnt_char == '\n' || in.eof())
    {
      return size;
    }
    free(data);
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
    new_array = reinterpret_cast< char * >(malloc((leters + spaces) * sizeof(char)));
    if (new_array == nullptr)
    {
      return 0;
    }
    return (leters + spaces);
  }

  size_t createCompactArray2(const char *data, const size_t length, char *&new_array)
  {
    size_t new_length = length;
    for (size_t i = 0; i < length; ++i)
    {
      if (std::isalpha(data[i]))
      {
        new_length--;
      }
    }
    new_array = reinterpret_cast< char * >(malloc(new_length * sizeof(char)));
    if (new_array == nullptr)
    {
      return 0;
    }
    return new_length;
  }

  size_t spcRmv(const char *arr, size_t length, char *&new_arr)
  {
    size_t new_length = createCompactArray1(arr, length, new_arr);
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
  size_t latRmv(char *arr, size_t length, char *&new_arr)
  {
    size_t new_length = createCompactArray2(arr, length, new_arr);
    if (new_length == 0)
    {
      return 0;
    }
    size_t crnt_digit = 0;
    char crnt_char = ' ';
    size_t i = 0;
    while (crnt_digit < new_length)
    {
      crnt_char = arr[i];
      if (!isalpha(crnt_char))
      {
        new_arr[crnt_digit] = crnt_char;
        crnt_digit++;
      }
      i++;
    }
    return new_length;
  }
}

int main()
{
  char *line = nullptr;
  size_t k = saldaev::getLine(std::cin, line, saldaev::block_size);
  if (k == 0)
  {
    std::cerr << "Could not read the string\n";
    free(line);
    return 1;
  }

  char *new_line = nullptr;
  size_t nk = saldaev::spcRmv(line, k, new_line);
  if (nk == 0)
  {
    std::cerr << "Could not convert the string\n";
    free(line);
    return 1;
  }
  for (size_t i = 0; i < nk; ++i)
  {
    std::cout << new_line[i];
  }
  std::cout << "\n";
  free(new_line);

  new_line = nullptr;
  nk = saldaev::latRmv(line, k, new_line);
  if (nk == 0)
  {
    std::cerr << "Could not convert the string\n";
    free(line);
    return 1;
  }
  for (size_t i = 0; i < nk; ++i)
  {
    std::cout << new_line[i];
  }
  std::cout << "\n";
  free(line);
  free(new_line);
}

