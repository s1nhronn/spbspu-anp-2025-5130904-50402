#include <iostream>
#include <string>
#include <fstream>

namespace bukreev
{
  int mode = 0;

  size_t rows = 0, cols = 0;

  int* inputMatrix(std::istream& in, int* stackMatrix);
  void deleteMatrix(const int* matrix);
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
  std::ifstream input(argv[2]);
  if (arg1 == 1)
  {
    const size_t MTX_MAX_SIZE = 10000;
    int stackMatrix[MTX_MAX_SIZE] = {};
    matrix = stackMatrix;
  }

  try
  {
    matrix = bukreev::inputMatrix(input, matrix);
  }
  catch(const std::invalid_argument& e)
  {
    std::cerr << "Content of the input file is invalid: ";
    std::cerr << e.what() << ".\n";
    return 2;
  }

  bukreev::deleteMatrix(matrix);

  return 0;
}

int* bukreev::inputMatrix(std::istream& in, int* stackMatrix)
{
  int* matrix = nullptr;

  in >> rows >> cols;

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
    matrix = new int[rows * cols];
  }

  for (size_t i = 0; i < rows * cols; i++)
  {
    in >> matrix[i];
  }

  if (in.fail())
  {
    throw std::invalid_argument("Not enough elements of matrix");
  }

  return matrix;
}

void bukreev::deleteMatrix(const int* matrix)
{
  if (mode == 2)
  {
    delete[] matrix;
  }
}
