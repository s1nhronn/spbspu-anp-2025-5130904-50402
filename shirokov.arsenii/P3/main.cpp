#include <fstream>
#include <iostream>
#include <stdexcept>
#include <cstring>
#include <limits>

size_t lengthInput(char *file);
void input(std::istream &in, int *m, size_t lng);
void output(std::ostream &out, const int *res1, size_t m, size_t n, bool res2);
bool isDigit(char *str);
int strToInt(char *str);
int myPow(int a, int b);
int *copy(const int *a, size_t k);
int *spiral(int *matrix, size_t m, size_t n);
bool isTriangularMatrix(int *matrix, size_t m, size_t n);

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

  int *matrix = nullptr;
  try
  {
    if (num == 1)
    {
      input(in, a, lng);
      matrix = a;
      delete[] b;
    }
    else
    {
      input(in, b, lng);
      matrix = b;
    }
  } catch (const std::logic_error &e)
  {
    std::cerr << e.what() << '\n';
    delete[] b;
    return 2;
  }
  std::ofstream out(argv[3]);
  int *res1 = spiral(matrix, m, n);
  bool res2 = isTriangularMatrix(matrix, m, n);
  output(out, res1, m, n, res2);
  if (num == 2)
  {
    delete[] matrix;
    delete[] res1;
  }
}

size_t lengthInput(char *file)
{
  std::ifstream in(file);
  size_t a, b;
  in >> a >> b;
  if (in.fail())
  {
    throw std::logic_error("Couldn't read the size of matrix");
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
      throw std::logic_error("Couldn't read the matrix");
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

void output(std::ostream &out, const int *res1, size_t m, size_t n, bool res2)
{
  out << "Решение варианта 1:\n";
  for (size_t i = 0; i < m; i++)
  {
    for (size_t j = 0; j < n; j++)
    {
      out << res1[i * n + j] << ' ';
    }
  }
  out << "\nРешение варианта 2:\n" << res2;
}

int *copy(const int *a, size_t k)
{
  int *b = new int[k];
  for (size_t i = 0; i < k; ++i)
  {
    b[i] = a[i];
  }
  return b;
}
