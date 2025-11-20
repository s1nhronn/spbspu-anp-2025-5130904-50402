#include <fstream>
#include <iostream>
#include <stdexcept>
#include <cstring>
#include <cstdlib>

namespace shirokov
{
  std::istream &input(std::istream &in, int *m, size_t lng);
  std::ostream &outputMatrix(std::ostream &out, const int *matrix, size_t m, size_t n);
  int *copy(const int *a, size_t k);
  void spiral(int *matrix, size_t m, size_t n);
  bool isTriangularMatrix(int *matrix, size_t m, size_t n);
  size_t transformIndexes(size_t i, size_t j, size_t n);
  void cutMatrix(int *matrix, size_t m, size_t n);
  const size_t MATRIX_SIZE = 10000;
}

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
  for (size_t i = 0; i < std::strlen(argv[1]); ++i)
  {
    if (!std::isdigit(static_cast< unsigned char >(argv[1][i])))
    {
      std::cerr << "First parameter is not a number\n";
      return 1;
    }
  }
  int num = 0;
  try
  {
    num = std::stoi(argv[1]);
  }
  catch (const std::out_of_range &e)
  {
    std::cerr << "First parameter is out of range\n";
    return 1;
  }
  if (num != 1 && num != 2)
  {
    std::cerr << "First parameter is out of range\n";
    return 1;
  }

  size_t lng = 0;
  size_t m, n;
  std::ifstream in(argv[2]);
  in >> m >> n;
  if (in.fail())
  {
    std::cerr << "Couldn't read the size of matrix" << '\n';
    return 2;
  }
  lng = m * n;

  int *matrix = nullptr;
  int a[shirokov::MATRIX_SIZE] = {};
  if (num == 1)
  {
    matrix = a;
  }
  else
  {
    matrix = new int[lng];
  }
  if (shirokov::input(in, matrix, lng).fail())
  {
    std::cerr << "Couldn't read the matrix" << '\n';
    if (num == 2)
    {
      delete[] matrix;
    }
    return 2;
  };
  std::ofstream out(argv[3]);
  if (!out.is_open())
  {
    std::cerr << "Couldn't open the output file\n";
    delete[] matrix;
    return 2;
  }
  int *res1 = shirokov::copy(matrix, m * n);
  shirokov::spiral(res1, m, n);
  bool res2 = shirokov::isTriangularMatrix(matrix, m, n);
  out << "Решение варианта 1:\n";
  shirokov::outputMatrix(out, res1, m, n) << '\n';
  out << "Решение варианта 2:\n" << (res2 ? "true" : "false");
  delete[] res1;
  if (num == 2)
  {
    delete[] matrix;
  }
}

std::istream &shirokov::input(std::istream &in, int *m, size_t lng)
{
  in.seekg(3);
  for (size_t i = 0; i < lng; i++)
  {
    in >> m[i];
    if (in.fail())
    {
      return in;
    }
  }
  return in;
}

std::ostream &shirokov::outputMatrix(std::ostream &out, const int *matrix, size_t m, size_t n)
{
  out << m << ' ' << n;
  if (m != 0 && n != 0)
  {
    out << ' ';
  }
  for (size_t i = 0; i < m; i++)
  {
    for (size_t j = 0; j < n; j++)
    {
      if (i == m - 1 && j == n - 1)
      {
        out << matrix[i * n + j];
        break;
      }
      out << matrix[i * n + j] << ' ';
    }
  }
  return out;
}

int *shirokov::copy(const int *a, size_t k)
{
  int *b = new int[k];
  for (size_t i = 0; i < k; ++i)
  {
    b[i] = a[i];
  }
  return b;
}

size_t shirokov::transformIndexes(size_t i, size_t j, size_t n)
{
  return i * n + j;
}

void shirokov::spiral(int *matrix, size_t m, size_t n)
{
  if (m == 0 || n == 0)
  {
    return;
  }
  size_t ptr = matrix[transformIndexes(m - 1, 0, n)];
  size_t leftBorder = 0;
  size_t rightBorder = n - 1;
  size_t upperBorder = 0;
  size_t lowerBorder = m - 1;

  size_t deductible = 1;
  while (leftBorder < n || upperBorder < m || rightBorder > 0 || lowerBorder > 0)
  {
    for (size_t i = lowerBorder; i + 1 >= upperBorder + 1; i--)
    {
      ptr = transformIndexes(i, leftBorder, n);
      matrix[ptr] -= deductible++;
    }
    if (leftBorder < n)
    {
      leftBorder++;
    }

    for (size_t j = leftBorder; j <= rightBorder; j++)
    {
      ptr = transformIndexes(upperBorder, j, n);
      matrix[ptr] -= deductible++;
    }
    if (upperBorder < m)
    {
      upperBorder++;
    }

    for (size_t i = upperBorder; i <= lowerBorder; i++)
    {
      ptr = transformIndexes(i, rightBorder, n);
      matrix[ptr] -= deductible++;
    }
    if (rightBorder > 0)
    {
      rightBorder--;
    }

    for (size_t j = rightBorder; j + 1 >= leftBorder + 1; j--)
    {
      ptr = transformIndexes(lowerBorder, j, n);
      matrix[ptr] -= deductible++;
    }
    if (lowerBorder > 0)
    {
      lowerBorder--;
    }
  }
}

void shirokov::cutMatrix(int *matrix, size_t m, size_t n)
{
  if (m == n)
  {
    return;
  }
  size_t minn = std::min(m, n);
  int *temp = new int[minn * minn];
  for (size_t i = 0; i < minn; ++i)
  {
    for (size_t j = 0; j < minn; ++j)
    {
      temp[transformIndexes(i, j, minn)] = matrix[transformIndexes(i, j, n)];
    }
  }
  delete[] matrix;
  matrix = temp;
}

bool shirokov::isTriangularMatrix(int *matrix, size_t m, size_t n)
{
  if (m == 0 || n == 0)
  {
    return false;
  }
  shirokov::cutMatrix(matrix, m, n);
  bool flag = true;
  for (size_t i = 0; i < m - 1; ++i)
  {
    for (size_t j = i + 1; j < n; ++j)
    {
      if (matrix[shirokov::transformIndexes(i, j, n)] != 0)
      {
        flag = false;
        break;
      }
    }
  }
  return flag;
}
