#include <iostream>
#include <fstream>
#include <cstdlib>
#include <limits>
namespace islamov
{
  int colsdiffnumbers(const int* arr, size_t rows, size_t cols);
  int zeroChecker(const int* arr, size_t rows, size_t cols);
  std::istream& matrixReader(std::istream& in, int* arr, size_t totalElements);
}
int main(int argc, char** argv)
{
  if (argc != 4)
  {
    std::cerr << "Error: Incorrect arguments\n";
    return 1;
  }
  char* endptr = nullptr;
  long mode = std::strtol(argv[1], std::addressof(endptr), 10);
  if (endptr == argv[1] || *endptr != '\0' || mode < 1 || mode > 2)
  {
    std::cerr << "Error: first parameter is not a valid number (must be 1 or 2)\n";
    return 1;
  }
  const char* inputName = argv[2];
  const char* outputName = argv[3];
  std::ifstream fin(inputName, std::ios::binary);
  if (!fin)
  {
    std::cerr << "Error: cannot open input file: " << inputName << "\n";
    return 2;
  }
  size_t rows = 0;
  size_t cols = 0;
  if (!(fin >> rows >> cols))
  {
    std::cerr << "Error: input file content is not a valid matrix\n";
    return 2;
  }
  if (rows != 0 && cols > std::numeric_limits < size_t >::max() / rows)
  {
    std::cerr << "Error: matrix too large\n";
    return 2;
  }
  size_t totalElements = rows * cols;
  int res1 = 0;
  int res2 = 0;
  if (mode == 1)
  {
    const size_t max_size = 10000;
    if (totalElements > max_size)
    {
      std::cerr << "Error: matrix too large\n";
      return 1;
    }
    int stackArr[max_size];
    if (!islamov::matrixReader(fin, stackArr, totalElements))
    {
      std::cerr << "Error: input file content is not a valid matrix\n";
      return 2;
    }
    fin >> std::ws;
    if (!fin.eof())
    {
      std::cerr << "Error: input file content is not a valid matrix\n";
      return 2;
    }
    res1 = islamov::colsdiffnumbers(stackArr, rows, cols);
    res2 = islamov::zeroChecker(stackArr, rows, cols);
    std::ofstream fout(outputName, std::ios::binary);
    if (!fout)
    {
      std::cerr << "Error: cannot open output file: " << outputName << "\n";
      return 2;
    }
    fout << res1 << '\n' << res2 << '\n';
    return 0;
  }
  else
  {
    int* dynArr = new int[totalElements];
    if (!islamov::matrixReader(fin, dynArr, totalElements))
    {
      delete[] dynArr;
      std::cerr << "Error: input file content is not a valid matrix\n";
      return 2;
    }
    fin >> std::ws;
    if (!fin.eof())
    {
      delete[] dynArr;
      std::cerr << "Error: input file content is not a valid matrix\n";
      return 2;
    }
    res1 = islamov::colsdiffnumbers(dynArr, rows, cols);
    res2 = islamov::zeroChecker(dynArr, rows, cols);
    std::ofstream out(outputName, std::ios::binary);
    if (!out)
    {
      delete[] dynArr;
      std::cerr << "Error: cannot open output file: " << outputName << "\n";
      return 2;
    }
    out << res1 << '\n' << res2 << '\n';
    delete[] dynArr;
    return 0;
  }
}
int islamov::colsdiffnumbers(const int* arr, size_t rows, size_t cols)
{
  int count = 0;
  for (size_t j = 0; j < cols; ++j)
  {
    bool equal = false;
    for (size_t i = 0; i + 1 < rows; ++i)
    {
      if (arr[i * cols + j] == arr[(i + 1) * cols + j])
      {
        equal = true;
        break;
      }
    }
    if (!equal)
    {
      ++count;
    }
  }
  return count;
}
int islamov::zeroChecker(const int* arr, size_t rows, size_t cols)
{
  if (rows == 0 || cols == 0)
  {
    return 0;
  }
  int count = 0;
  size_t totalDiagonals = rows + cols - 1;
  for (size_t diagIndex = 0; diagIndex < totalDiagonals; ++diagIndex)
  {
    bool zeroFound = false;
    size_t startRow = 0;
    size_t startCol = 0;
    if (diagIndex < rows)
    {
      startRow = rows - 1 - diagIndex;
      startCol = 0;
    }
    else
    {
      startRow = 0;
      startCol = diagIndex - rows + 1;
    }
    size_t i = startRow;
    size_t j = startCol;
    while (i < rows && j < cols)
    {
      if (arr[i * cols + j] == 0)
      {
        zeroFound = true;
        break;
      }
      ++i;
      ++j;
    }
    if (!zeroFound)
    {
      ++count;
    }
  }
  return count;
}
std::istream& islamov::matrixReader(std::istream& in, int* arr, size_t totalElements)
{
  for (size_t i = 0; i < totalElements; ++i)
  {
    if (!(in >> arr[i]))
    {
      return in;
    }
  }
  return in;
}
