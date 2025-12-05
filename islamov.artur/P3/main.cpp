#include <iostream>
#include <fstream>
#include <cstdlib>
#include <limits>
#include <cstring>
namespace islamov
{
  int colsdiffnumbers(const int* arr, size_t rows, size_t cols);
  int zeroChecker(const int* arr, size_t rows, size_t cols);
  bool intArg(const char* s, int& out);
  bool matrixReader(std::istream& in, int* arr, size_t totalElements);
}
int main(int argc, char** argv)
{
  if (argc != 4)
  {
    std::cerr << "Error: Incorrect arguments\n";
    return 1;
  }
  int m = 0;
  if (!islamov::intArg(argv[1], m))
  {
    std::cerr << "Error: first parameter is not a number\n";
    return 1;
  }
  if (m != 1 && m != 2)
  {
    std::cerr << "Error: first parameter is out of range\n";
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
  size_t rows = 0, cols = 0;
  if (!(fin >> rows >> cols))
  {
    std::cerr << "Error: input file content is not a valid matrix\n";
    return 2;
  }
  if (rows != 0 && cols > std::numeric_limits <size_t>::max() / rows)
  {
    std::cerr << "Error: matrix too large\n";
    return 2;
  }
  size_t totalElements = rows * cols;
  int res1 = 0, res2 = 0;
  if (m == 1)
  {
    const size_t max_size = 10000;
    if (totalElements > max_size)
    {
      std::cerr << "Error: matrix too large\n";
      return 1;
    }
    int stackArr[max_size];
    for (size_t i = 0; i < totalElements; ++i)
    {
      int val;
      if (!(fin >> val))
      {
        std::cerr << "Error: input file content is not a valid matrix\n";
        return 2;
      }
      stackArr[i] = val;
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
    for (size_t i = 0; i < totalElements; ++i)
    {
      int val;
      if (!(fin >> val))
      {
        delete[] dynArr;
        std::cerr << "Error: input file content is not a valid matrix\n";
        return 2;
      }
      dynArr[i] = val;
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
    size_t startRow = 0, startCol = 0;
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
bool islamov::intArg(const char* s, int& out)
{
  char* endptr = nullptr;
  long val = std::strtol(s, std::addressof(endptr), 10);
  if (endptr == s || *endptr != '\0')
  {
    return false;
  }
  if (val < std::numeric_limits <int>::min() || val > std::numeric_limits <int>::max())
  {
    return false;
  }
  out = static_cast <int> (val);
  return true;
}
bool islamov::matrixReader(std::istream& in, int* arr, size_t totalElements)
{
  for (size_t i = 0; i < totalElements; ++i)
  {
    int val;
    if (!(in >> val))
    {
      return false;
    }
    arr[i] = val;
  }
  int dummy;
  if (in >> dummy)
  {
    return false;
  }
  return true;
}
