#include <iostream>
#include <cctype>
#include <cstring>

namespace afanasev {
  // Возвращает указатель на массив из char
  char * getline(std::istream & input, size_t & size)
  {
    bool isSkipWp = input.flags() & std::ios::skipws;
    if (isSkipWp)
    {
      input >> std::noskipws;
    }

    char * str = nullptr;
    char * tmp = nullptr;
    char n = 0;
    while (input >> n && n != '\n')
    {
      tmp = new char[size + 1];
      if (tmp == nullptr || input.fail())
      {
        delete[] str;
        throw;
      }
      for (size_t i = 0; i < size; ++i)
      {
        tmp[i] = str[i];
      }
      delete[] str;
      str = tmp;
      str[size] = n;
      size++;
    }

    tmp = new char[size + 1];
    if (tmp == nullptr)
    {
      delete[] str;
      throw;
    }
    for (size_t i = 0; i < size; ++i)
    {
      tmp[i] = str[i];
    }
    delete[] str;
    str = tmp;
    str[size] = '\0';
    size++;

    if (isSkipWp)
    {
      input >> std::skipws;
    }

    return str;
  }

  // Удаление букв из переданной строки
  void deletingLetters(const char * str, const char * let, char * out, size_t str_l, size_t & out1_l)
  {
    size_t i = 0;

    while (str[i] != '\0' && out1_l < str_l - 1)
    {
      if (!strchr(let, str[i]))
      {
        out[out1_l] = str[i];
        out1_l++;
      }
      i++;
    }
    out[out1_l] = '\0';
  }

  // Удаляет из переданной строки все гласные
  void deleteVowels(const char * str, char * output, size_t size, size_t & output1)
  {
    const char * vowels = "aeiouyAEIOUY";
    deletingLetters(str, vowels, output, size, output1);
  }
}

int main()
{
  // Считываем строку
  size_t str_lenght = 0;
  size_t & str_lenght_link = str_lenght;
  char * str = nullptr;
  try
  {
    str = afanasev::getline(std::cin, str_lenght_link);
  }
  catch (...)
  {
    std::cerr << "Incorrect input or get memory failed" << '\n';
    return 1;
  }

  // Удаление гласных
  size_t output1_lenght = 0;
  size_t & output1_lenght_link = output1_lenght;
  char * output1 = nullptr;
  output1 = new char[str_lenght];
  if (output1 == nullptr)
  {
    delete[] str;
    std::cerr << "Get memory failed" << '\n';
    return 1;
  }
  afanasev::deleteVowels(str, output1, str_lenght, output1_lenght_link);

  for (size_t i = 0; i < output1_lenght_link; i++)
  {
    std::cout << output1[i];
  }
  std::cout << '\n';
  delete[] output1;


  // Удаление заданных букв
  size_t output2_lenght = 0;
  size_t & output2_lenght_link = output2_lenght;
  const char * let = "abcd";
  char * output2 = nullptr;
  output2 = new char[str_lenght];
  if (output2 == nullptr)
  {
    delete[] str;
    std::cerr << "Get memory failed" << '\n';
    return 1;
  }
  afanasev::deletingLetters(str, let, output2, str_lenght, output2_lenght_link);

  for (size_t i = 0; i < output2_lenght_link; i++)
  {
    std::cout << output2[i];
  }
  std::cout << '\n';
  delete[] output2;

  return 0;
}










/*
#include <iostream>
#include <iomanip>

namespace afanasev
{
  size_t getline(std::istream & in, char * data, size_t size)
  {
    bool is_skipws = in.flags() & std::ios_base::skipws;
    if (is_skipws)
    {
      in >> std::noskipws;
    }
    size_t i = 0;
    for (; in && i < size; i++)
    {
      in >> data[i];
    }
    data[i] = 0;
    if (is_skipws)
    {
      in >> std::skipws;
    }
    in >> std::skipws;
    return i;
  }
}

int main()
{
  char str[] = "!!!!!";
  size_t str_size = 5;

  char del_str[] = "abc";


  size_t k = afanasev::getline(std::cin, str, str_size);

  str[k] = 0;

  std::cout << str << "\n";

  
  //только пробелы
  std::cin >> std::noskipws;

  for (size_t i = 0; i < str_size; i++)
  {
    std::cin >> str[i];
  }
  

}
*/
