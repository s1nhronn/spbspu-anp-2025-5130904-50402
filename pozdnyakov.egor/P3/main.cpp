#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstring>
#include <algorithm>

namespace pozdnyakov {

  const size_t MAX_ELEMENTS = 10000;
  const size_t MAX_ROWS = 100;
  const size_t MAX_COLS = 100;

  int* createMatrix(size_t rows, size_t cols)
  {
    if (rows == 0 || cols == 0)
    {
      return nullptr;
    }
    return static_cast<int*>(std::malloc(rows * cols * sizeof(int)));
  }

  void freeMatrix(int* matrix)
  {
    if (matrix != nullptr)
    {
      std::free(matrix);
    }
  }

  bool readMatrix(std::istream& input, int* matrix, size_t rows, size_t cols)
  {
    for (size_t i = 0; i < rows; i++)
    {
      for (size_t j = 0; j < cols; j++)
      {
        if (!(input >> matrix[i * cols + j]))
        {
          return false;
        }
      }
    }
    return true;
  }

  void writeResults(std::ostream& output, int result18, int result8)
  {
    output << result18 << " " << result8;
  }

  int processTask18(const int* matrix, size_t rows, size_t cols)
  {
    int count = 0;

    for (size_t startCol = 0; startCol < cols; startCol++)
    {
      bool hasZero = false;
      bool diagonalExists = false;
      size_t i = 0;
      size_t j = startCol;

      while (i < rows && j < cols)
      {
        diagonalExists = true;
        if (matrix[i * cols + j] == 0)
        {
          hasZero = true;
          break;
        }
        i++;
        j++;
      }

      if (diagonalExists && !hasZero)
      {
        count++;
      }
    }

    for (size_t startRow = 1; startRow < rows; startRow++)
    {
      bool hasZero = false;
      bool diagonalExists = false;
      size_t i = startRow;
      size_t j = 0;

      while (i < rows && j < cols)
      {
        diagonalExists = true;
        if (matrix[i * cols + j] == 0)
        {
          hasZero = true;
          break;
        }
        i++;
        j++;
      }

      if (diagonalExists && !hasZero)
      {
        count++;
      }
    }

    return count;
  }

  bool processTask8(int* matrix, size_t rows, size_t cols, int& result)
  {
    if (rows == 0 || cols == 0)
    {
      result = 0;
      return true;
    }

    int* tempMatrix = static_cast<int*>(
      std::malloc(rows * cols * sizeof(int)));
    if (tempMatrix == nullptr)
    {
      return false;
    }

    for (size_t i = 0; i < rows * cols; i++)
    {
      tempMatrix[i] = matrix[i];
    }

    size_t layers = (std::min(rows, cols) + 1) / 2;

    for (size_t layer = 0; layer < layers; layer++)
    {
      int increment = layer + 1;

      for (size_t i = layer; i < rows - layer; i++)
      {
        for (size_t j = layer; j < cols - layer; j++)
        {
          bool isBorder = i == layer || i == rows - layer - 1 ||
            j == layer || j == cols - layer - 1;
          if (isBorder)
          {
            tempMatrix[i * cols + j] += increment;
          }
        }
      }
    }

    int sum = 0;
    for (size_t i = 0; i < rows * cols; i++)
    {
      sum += tempMatrix[i];
    }

    result = sum;
    std::free(tempMatrix);
    return true;
  }
}

int main()
{
  using namespace pozdnyakov;

  int taskNum;
  std::string inputFile, outputFile;

  std::cin >> taskNum >> inputFile >> outputFile;

  if (taskNum != 1 && taskNum != 2)
  {
    std::cerr << "First parameter is out of range\n";
    return 1;
  }

  std::ifstream inputStream(inputFile);
  if (!inputStream.is_open())
  {
    std::cerr << "Cannot open input file\n";
    return 2;
  }

  size_t rows = 0;
  size_t cols = 0;

  if (!(inputStream >> rows >> cols))
  {
    std::cerr << "File is empty\n";
    return 2;
  }

  int result18 = 0;
  int result8 = 0;

  if (rows == 0 || cols == 0)
  {
    std::ofstream outputStream(outputFile);
    if (outputStream.is_open())
    {
      writeResults(outputStream, result18, result8);
    }
    std::cout << result18 << " " << result8 << '\n';
    return 0;
  }

  bool exceedsLimits = false;

  if (rows > 0 && cols > MAX_ELEMENTS / rows) 
  {
    exceedsLimits = true;
  }

  if (!exceedsLimits && (rows > MAX_ROWS || cols > MAX_COLS)) {
    exceedsLimits = true;
  }

  if (taskNum == 1 && exceedsLimits) 
  {
    std::cerr << "Matrix size exceeds limits\n";
    return 2;
  }

  int* matrix = createMatrix(rows, cols);
  if (matrix == nullptr)
  {
    std::cerr << "Memory allocation failed\n";
    return 2;
  }

  if (!readMatrix(inputStream, matrix, rows, cols))
  {
    std::cerr << "Invalid matrix data\n";
    freeMatrix(matrix);
    return 2;
  }

  result18 = processTask18(matrix, rows, cols);

  bool task8Success = processTask8(matrix, rows, cols, result8);
  if (!task8Success)
  {
    std::cerr << "Memory allocation failed during task processing\n";
    freeMatrix(matrix);
    return 3;
  }

  std::ofstream outputStream(outputFile);
  if (outputStream.is_open())
  {
    writeResults(outputStream, result18, result8);
  }

  std::cout << result18 << " " << result8 << '\n';

  freeMatrix(matrix);

  return 0;
}
