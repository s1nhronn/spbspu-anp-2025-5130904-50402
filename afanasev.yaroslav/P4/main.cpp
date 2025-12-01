#include <iostream>
#include <cctype>
#include <cstring>

namespace afanasev
{
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
      try
      {
        tmp = new char[size + 1];
      }
      catch(...)
      {
        delete[] str;
        if (isSkipWp)
        {
          input >> std::skipws;
        }
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

    tmp = nullptr;
    if (input.eof())
    {
      delete[] str;
      if (isSkipWp)
      {
        input >> std::skipws;
      }
      throw std::logic_error("incorrect input");
    }

    try
    {
      tmp = new char[size + 1];
    }
    catch(...)
    {
      delete[] str;
      if (isSkipWp)
      {
        input >> std::skipws;
      }
      throw;
    }

    for (size_t i = 0; i < size; ++i)
    {
      tmp[i] = str[i];
    }
    delete[] str;
    str = tmp;
    str[size] = '\0';

    if (isSkipWp)
    {
      input >> std::skipws;
    }

    return str;
  }

  void deletingLetters(const char * str, const char * let, char * out)
  {
    size_t i = 0;
    size_t out1_l = 0;

    while (str[i] != '\0')
    {
      if (!std::strchr(let, str[i]))
      {
        out[out1_l] = str[i];
        out1_l++;
      }
      i++;
    }
    out[out1_l] = '\0';
  }

  void deleteVowels(const char * str, char * output)
  {
    const char * vowels = "aeiouyAEIOUY";
    deletingLetters(str, vowels, output);
  }
}

int main()
{
  size_t str_lenght = 0;
  size_t & str_lenght_link = str_lenght;
  char * str = nullptr;
  try
  {
    str = afanasev::getline(std::cin, str_lenght_link);
  }
  catch (const std::bad_alloc&)
  {
    std::cerr << "Get memory failed" << '\n';
    return 1;
  }
  catch (const std::logic_error&)
  {
    std::cerr << "Incorrect input" << '\n';
    return 1;
  }
  catch (...)
  {
    std::cerr << "Undefinde error" << '\n';
    return 1;
  }

  char * output1 = nullptr;
  try
  {
    output1 = new char[str_lenght + 1];
    output1[0] = '\0';
  }
  catch(...)
  {
    delete[] str;
    std::cerr << "Get memory failed" << '\n';
    return 1;
  }

  const char * let = "abcd";
  char * output2 = nullptr;
  try
  {
    output2 = new char[str_lenght + 1];
    output2[0] = '\0';
  }
  catch(...)
  {
    delete[] str;
    delete[] output1;
    std::cerr << "Get memory failed" << '\n';
    return 1;
  }

  afanasev::deleteVowels(str, output1);
  afanasev::deletingLetters(str, let, output2);

  std::cout << output1 << '\n';
  delete[] output1;

  std::cout << output2 << '\n';
  delete[] output2;
  delete[] str;
  return 0;
}
