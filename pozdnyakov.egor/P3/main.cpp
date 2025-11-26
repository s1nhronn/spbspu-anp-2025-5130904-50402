#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstring>

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

  int processTask8(const int* matrix, size_t rows, size_t cols)
  {
    size_t total = rows * cols;
    if (total == 0)
    {
      return 0;
    }

    int* elements = static_cast<int*>(std::malloc(total * sizeof(int)));

    if (elements == nullptr)
    {
      return -1;
    }

    for (size_t i = 0; i < total; i++)
    {
      elements[i] = matrix[i];
    }

    for (size_t i = 0; i < total - 1; i++)
    {
      for (size_t j = 0; j < total - i - 1; j++)
      {
        if (elements[j] > elements[j + 1])
        {
          int temp = elements[j];
          elements[j] = elements[j + 1];
          elements[j + 1] = temp;
        }
      }
    }

    int sum = 0;
    for (size_t i = 0; i < total; i++)
    {
      sum += elements[i];
    }

    std::free(elements);
    return sum;
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
    std::cerr << "First parameter is out of range" << std::endl;
    return 1;
  }

  std::ifstream inputStream(inputFile);
  if (!inputStream.is_open())
  {
    std::cerr << "Cannot open input file" << std::endl;
    return 2;
  }

  size_t rows = 0;
  size_t cols = 0;

  if (!(inputStream >> rows >> cols))
  {
    std::cerr << "File is empty" << std::endl;
    return 2;
  }

  if (rows == 0 || cols == 0)
  {
    std::ofstream outputStream(outputFile);
    if (outputStream.is_open())
    {
      writeResults(outputStream, 0, 0);
    }
    std::cout << "0 0" << std::endl;
    return 0;
  }

  if (taskNum == 1 && (rows * cols > MAX_ELEMENTS || rows > MAX_ROWS || cols > MAX_COLS))
  {
    std::cerr << "Matrix size exceeds limits" << std::endl;
    return 2;
  }

  int* matrix = createMatrix(rows, cols);
  if (matrix == nullptr)
  {
    std::cerr << "Memory allocation failed" << std::endl;
    return 2;
  }

  if (!readMatrix(inputStream, matrix, rows, cols))
  {
    std::cerr << "Invalid matrix data" << std::endl;
    freeMatrix(matrix);
    return 2;
  }

  int result18 = processTask18(matrix, rows, cols);
  int result8 = processTask8(matrix, rows, cols);

  std::ofstream outputStream(outputFile);
  if (outputStream.is_open())
  {
    writeResults(outputStream, result18, result8);
  }

  std::cout << result18 << " " << result8 << std::endl;

  freeMatrix(matrix);

  return 0;
}
