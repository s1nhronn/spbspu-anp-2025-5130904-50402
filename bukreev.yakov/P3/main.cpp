#include <iostream>
#include <string>
#include <fstream>
#include <limits>

namespace bukreev
{
  int mode = 0;

  int* inputMatrix(std::istream& in, int* stackMatrix, size_t* rows, size_t* cols);
  void deleteMatrix(const int* matrix);

  size_t cntSdlPnt(const int* matrix, size_t rows, size_t cols);
}

int main(int argc, char* argv[])
{
  if (argc < 4)
  {
    std::cerr << "Not enough arguments.\n";
    return 1;
  }

  if (argc > 4)
  {
    std::cerr << "Too many arguments.\n";
    return 1;
  }

  int arg1 = 0;
  try
  {
    arg1 = std::stoi(argv[1]);
  }
  catch(const std::invalid_argument& e)
  {
    std::cerr << "First parameter is not a number.\n";
    return 1;
  }
  catch(const std::out_of_range& e)
  {
    std::cerr << "First parameter is out of range.\n";
    return 1;
  }

  if (arg1 != 1 && arg1 != 2)
  {
    std::cerr << "First parameter is out of range.\n";
    return 1;
  }

  bukreev::mode = arg1;

  int* matrix = nullptr;
  size_t rows = 0, cols = 0;
  std::ifstream input(argv[2]);
  if (arg1 == 1)
  {
    const size_t MTX_MAX_SIZE = 10000;
    int stackMatrix[MTX_MAX_SIZE] = {};
    matrix = stackMatrix;
  }

  try
  {
    matrix = bukreev::inputMatrix(input, matrix, &rows, &cols);
  }
  catch(const std::invalid_argument& e)
  {
    std::cerr << "Content of the input file is invalid: ";
    std::cerr << e.what() << ".\n";
    return 2;
  }

  size_t res = 0;
  try
  {
    res = bukreev::cntSdlPnt(matrix, rows, cols);
  }
  catch(const std::bad_alloc& e)
  {
    bukreev::deleteMatrix(matrix);
    return 3;
  }

  std::cout << res << '\n';

  bukreev::deleteMatrix(matrix);

  return 0;
}

int* bukreev::inputMatrix(std::istream& in, int* stackMatrix, size_t* rows, size_t* cols)
{
  int* matrix = nullptr;
  
  size_t n = 0, m = 0;
  in >> n >> m;

  if (in.fail())
  {
    throw std::invalid_argument("No width or height of matrix");
  }

  if (mode == 1)
  {
    matrix = stackMatrix;
  }
  else
  {
    matrix = new int[n * m];
  }

  for (size_t i = 0; i < n * m; i++)
  {
    in >> matrix[i];
  }

  if (in.fail())
  {
    throw std::invalid_argument("Not enough elements of matrix");
  }

  *rows = n;
  *cols = m;

  return matrix;
}

void bukreev::deleteMatrix(const int* matrix)
{
  if (mode == 2)
  {
    delete[] matrix;
  }
}

size_t bukreev::cntSdlPnt(const int* matrix, size_t rows, size_t cols)
{
  size_t res = 0;

  size_t* colsMaximums = new size_t[cols];

  for (size_t i = 0; i < cols; i++)
  {
    int maxElem = std::numeric_limits<int>::min();
    size_t maxIndex = 0;

    for (size_t j = 0; j < rows; j++)
    {
      int elem = matrix[j * cols + i];
      if (elem > maxElem)
      {
        maxElem = elem;
        maxIndex = j;
      }
    }

    colsMaximums[i] = maxIndex;
  }

  for (size_t i = 0; i < rows; i++)
  {
    int minElem = std::numeric_limits<int>::max();
    size_t minIndex = 0;

    for (size_t j = 0; j < cols; j++)
    {
      int elem = matrix[i * cols + j];
      if (elem < minElem)
      {
        minElem = elem;
        minIndex = j;
      }
    }

    if (colsMaximums[minIndex] == i)
    {
      res++;
    }
  }

  delete[] colsMaximums;

  return res;
}
