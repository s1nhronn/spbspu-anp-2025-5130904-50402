#include <iostream>
#include <fstream>
#include <cstdlib>

namespace pozdnyakov {

  const size_t MAX_ELEMENTS = 10000;
  const size_t MAX_ROWS = 100;
  const size_t MAX_COLS = 100;

  size_t myMin(size_t a, size_t b)
  {
    return (a < b ? a : b);
  }

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

  bool readMatrix(std::istream& in, int* m, size_t rows, size_t cols)
  {
    size_t total = rows;
    total *= cols;
    for (size_t i = 0; i < total; i++)
    {
      if (!(in >> m[i]))
      {
        return false;
      }
    }
    return true;
  }

  void writeResults(std::ostream& out, int r18, int r8)
  {
    out << r18 << " " << r8;
  }

  int countDiag(const int* m, size_t rows, size_t cols,
    size_t r, size_t c)
  {
    bool hasZero = false;
    bool exists = false;
    while (r < rows && c < cols)
    {
      exists = true;
      if (m[r * cols + c] == 0)
      {
        hasZero = true;
        break;
      }
      r++;
      c++;
    }
    return (exists && !hasZero) ? 1 : 0;
  }

  int processTask18(const int* m, size_t rows, size_t cols)
  {
    int count = 0;
    for (size_t c = 0; c < cols; c++)
    {
      count += countDiag(m, rows, cols, 0, c);
    }
    for (size_t r = 1; r < rows; r++)
    {
      count += countDiag(m, rows, cols, r, 0);
    }
    return count;
  }

  bool processTask8(int* m, size_t rows, size_t cols, int& result)
  {
    if (rows == 0 || cols == 0)
    {
      result = 0;
      return true;
    }

    size_t total = rows;
    total *= cols;

    int* tmp = static_cast<int*>(std::malloc(total * sizeof(int)));
    if (tmp == nullptr)
    {
      return false;
    }

    for (size_t i = 0; i < total; i++)
    {
      tmp[i] = m[i];
    }

    size_t layers = (myMin(rows, cols) + 1) / 2;
    for (size_t layer = 0; layer < layers; layer++)
    {
      int inc = layer + 1;
      size_t top = layer;
      size_t bottom = rows - layer - 1;
      size_t left = layer;
      size_t right = cols - layer - 1;

      for (size_t r = layer; r < rows - layer; r++)
      {
        for (size_t c = layer; c < cols - layer; c++)
        {
          bool border = (r == top || r == bottom ||
            c == left || c == right);
          if (border)
          {
            tmp[r * cols + c] += inc;
          }
        }
      }
    }

    int sum = 0;
    for (size_t i = 0; i < total; i++)
    {
      sum += tmp[i];
    }

    result = sum;
    std::free(tmp);
    return true;
  }
}

int main()
{
  using namespace pozdnyakov;

  int taskNum;
  std::string inFile;
  std::string outFile;

  std::cin >> taskNum >> inFile >> outFile;

  if (taskNum != 1 && taskNum != 2)
  {
    std::cerr << "First parameter is out of range\n";
    return 1;
  }

  std::ifstream in(inFile);
  if (!in.is_open())
  {
    std::cerr << "Cannot open input file\n";
    return 2;
  }

  size_t rows = 0;
  size_t cols = 0;

  if (!(in >> rows))
  {
    std::cerr << "File is empty\n";
    return 2;
  }
  if (!(in >> cols))
  {
    std::cerr << "File is empty\n";
    return 2;
  }

  int r18 = 0;
  int r8 = 0;

  if (rows == 0 || cols == 0)
  {
    std::ofstream out(outFile);
    if (out.is_open())
    {
      writeResults(out, r18, r8);
    }
    std::cout << r18 << " " << r8 << '\n';
    return 0;
  }

  bool exceeds = false;

  if (rows > 0 && cols > MAX_ELEMENTS / rows)
  {
    exceeds = true;
  }
  if (!exceeds && (rows > MAX_ROWS || cols > MAX_COLS))
  {
    exceeds = true;
  }

  if (taskNum == 1 && exceeds)
  {
    std::cerr << "Matrix size exceeds limits\n";
    return 2;
  }

  int* m = createMatrix(rows, cols);
  if (m == nullptr)
  {
    std::cerr << "Memory allocation failed\n";
    return 2;
  }

  if (!readMatrix(in, m, rows, cols))
  {
    std::cerr << "Invalid matrix data\n";
    freeMatrix(m);
    return 2;
  }

  r18 = processTask18(m, rows, cols);

  bool ok = processTask8(m, rows, cols, r8);
  if (!ok)
  {
    std::cerr << "Memory allocation failed while processing the task\n";
    freeMatrix(m);
    return 3;
  }

  std::ofstream out(outFile);
  if (out.is_open())
  {
    writeResults(out, r18, r8);
  }

  std::cout << r18 << " " << r8 << '\n';

  freeMatrix(m);

  return 0;
}
