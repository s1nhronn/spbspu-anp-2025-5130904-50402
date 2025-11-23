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
}

int main() {

  // Считываем строку
  size_t str_lenght = 0;
  size_t & str_lenght_link = str_lenght;
  char * str = afanasev::getline(std::cin, str_lenght_link);

  // Проверка на случай пустой строки
  if (str == 0) {
    std::cerr << "Null string" << '\n';
    return 1;
  }
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
