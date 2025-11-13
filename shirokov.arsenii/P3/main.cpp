#include <fstream>
#include <iostream>
#include <stdexcept>
#include <cstring>
#include <limits>

size_t lengthInput(char *file);
void input(std::istream &in, int *m, size_t lng);
std::ostream &output(std::ostream &out, const int *m, size_t a, size_t b);
bool isDigit(char *str);
int strToInt(char *str);
int myPow(int a, int b);

int main(int argc, char **argv)
{
  if (argc < 4)
  {
    std::cerr << "Not enough arguments\n";
    return 1;
  }
  if (argc > 4)
  {
    std::cerr << "Too many arguments\n";
    return 1;
  }
  if (!isDigit(argv[1]))
  {
    std::cerr << "First parameter is not a number\n";
    return 1;
  }
  int num = 0;
  try
  {
    num = strToInt(argv[1]);
  } catch (const std::overflow_error &e)
  {
    std::cerr << e.what() << '\n';
    return 1;
  }
  if (num != 1 && num != 2)
  {
    std::cerr << "First parameter is out of range\n";
    return 1;
  }

  size_t lng = 0;
  try
  {
    lng = lengthInput(argv[2]);
  } catch (const std::logic_error &e)
  {
    std::cerr << e.what() << '\n';
    return 2;
  }
  int a[10000] = {};
  int *b = new int[lng];
  std::ifstream in(argv[2]);
  size_t m, n;
  in >> m >> n;

  int *massive = nullptr;
  try
  {
    if (num == 1)
    {
      input(in, a, lng);
      massive = a;
      delete[] b;
    }
    else
    {
      input(in, b, lng);
      massive = b;
    }
  } catch (const std::logic_error &e)
  {
    std::cerr << e.what() << '\n';
    if (num == 2)
    {
      delete[] b;
    }
    return 2;
  }
  std::ofstream out(argv[3]);
  output(out, massive, m, n) << '\n';
  if (num == 2)
  {
    delete[] massive;
  }
}

size_t lengthInput(char *file)
{
  std::ifstream in(file);
  size_t a, b;
  in >> a >> b;
  if (in.fail())
  {
    throw std::logic_error("Couldn't read the size of massive");
  }
  return a * b;
}

void input(std::istream &in, int *m, size_t lng)
{
  for (size_t i = 0; i < lng; i++)
  {
    in >> m[i];
    if (in.fail())
    {
      throw std::logic_error("Couldn't read the massive");
    }
  }
}

bool isDigit(char *str)
{
  size_t len = std::strlen(str);
  for (size_t i = 0; i < len; i++)
  {
    if (!('0' <= str[i] && str[i] <= '9'))
    {
      return false;
    }
  }
  return true;
}

int strToInt(char *str)
{
  int res = 0;
  int iLimit = std::numeric_limits<int>::max();
  size_t len = std::strlen(str);

  for (size_t i = 0; i < len; i++)
  {
    int temp = 0;
    temp = myPow(10, len - i - 1);
    if ((str[i] - '0') > iLimit / temp)
    {
      throw std::overflow_error("First parameter is out of range");
    }
    res += (str[i] - '0') * temp;
  }
  return res;
}

int myPow(int a, int b)
{
  if (a == 0 || a == 1)
  {
    return a;
  }
  int res = 1;
  for (int i = 0; i < b; i++)
  {
    if (res > std::numeric_limits<int>::max() / a)
    {
      throw std::overflow_error("First parameter is out of range");
    }
    res *= a;
  }
  return res;
}

std::ostream &output(std::ostream &out, const int *m, size_t a, size_t b)
{
  for (size_t i = 0; i < a; i++)
  {
    for (size_t j = 0; j < b; j++)
    {
      out << m[i * b + j] << ' ';
    }
  }
  return out;
}
