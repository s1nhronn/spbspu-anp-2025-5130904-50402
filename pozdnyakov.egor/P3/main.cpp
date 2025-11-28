#include <iostream>
#include <fstream>
#include <cstdlib>

const size_t MAX_ELEMENTS = 10000;
const size_t MAX_ROWS = 100;
const size_t MAX_COLS = 100;

namespace pozdnyakov {

  int** allocateMatrix(size_t rows, size_t cols)
  {
    int** data = static_cast <int**> (std::malloc(rows * sizeof(int*)));
    if (data == nullptr)
    {
      return nullptr;
    }

    for (size_t i = 0; i < rows; i++)
    {
      data[i] = static_cast <int*>(std::malloc(cols * sizeof(int)));
      if (data[i] == nullptr)
      {
        for (size_t j = 0; j < i; j++)
        {
          std::free(data[j]);
        }
        std::free(data);
        return nullptr;
      }
    }

    return data;
  }

  void freeMatrix(int** data, size_t rows)
  {
    if (data == nullptr)
    {
      return;
    }

    for (size_t i = 0; i < rows; i++)
    {
      std::free(data[i]);
    }

    std::free(data);
  }

  std::istream& readDimensions(std::istream& in, size_t& rows, size_t& cols)
  {
    long r = 0;
    long c = 0;

    if (!(in >> r))
    {
      return in;
    }

    if (!(in >> c))
    {
      return in;
    }

    if (r <= 0 || c <= 0)
    {
      in.setstate(std::ios::failbit);
      return in;
    }

    rows = static_cast <size_t> (r);
    cols = static_cast <size_t> (c);

    return in;
  }

  std::istream& readMatrix(std::istream& in, int** data, size_t rows, size_t cols)
  {
    for (size_t i = 0; i < rows; i++)
    {
      for (size_t j = 0; j < cols; j++)
      {
        if (!(in >> data[i][j]))
        {
          return in;
        }
      }
    }

    return in;
  }

  int processTask18(int** data, size_t rows, size_t cols)
  {
    int count = 0;

    size_t maxDiag = rows + cols - 2;

    for (size_t k = 0; k <= maxDiag; k++)
    {
      bool exists = false;
      bool hasZero = false;

      for (size_t i = 0; i < rows; i++)
      {
        size_t j = (k >= i) ? (k - i) : MAX_COLS;

        if (j < cols)
        {
          exists = true;
          if (data[i][j] == 0)
          {
            hasZero = true;
            break;
          }
        }
      }

      if (exists && !hasZero)
      {
        count++;
      }
    }

    return count;
  }

  void processTask8(int** data, size_t rows, size_t cols)
  {
    size_t layers = rows < cols ? rows : cols;
    layers = (layers + 1) / 2;

    for (size_t layer = 0; layer < layers; layer++)
    {
      int inc = static_cast <int>(layer + 1);
      size_t top = layer;
      size_t bottom = rows - layer - 1;
      size_t left = layer;
      size_t right = cols - layer - 1;

      for (size_t r = layer; r < rows - layer; r++)
      {
        for (size_t c = layer; c < cols - layer; c++)
        {
          bool border = false;

          if (r == top || r == bottom || c == left || c == right)
          {
            border = true;
          }

          if (border)
          {
            data[r][c] += inc;
          }
        }
      }
    }
  }

  std::ostream& writeResults(std::ostream& out, int r18, int r8)
  {
    out << r18 << ' ' << r8;
    return out;
  }

  bool validateArgs(int argc, char* argv[])
  {
    if (argc != 4)
    {
      if (argc < 4)
      {
        std::cerr << "Not enough arguments\n";
      }
      else
      {
        std::cerr << "Too many arguments\n";
      }
      return false;
    }

    char* endptr = nullptr;
    long num = std::strtol(argv[1], &endptr, 10);

    if (endptr == argv[1] || *endptr != '\0')
    {
      std::cerr << "First parameter is not a number\n";
      return false;
    }

    if (num != 1 && num != 2)
    {
      std::cerr << "First parameter is out of range\n";
      return false;
    }

    return true;
  }

}

int main(int argc, char* argv[])
{
  using namespace pozdnyakov;

  if (!validateArgs(argc, argv))
  {
    return 1;
  }

  long taskType = std::strtol(argv[1], nullptr, 10);
  const char* inputFile = argv[2];
  const char* outputFile = argv[3];

  std::ifstream in(inputFile);
  if (!in.is_open())
  {
    std::cerr << "Cannot open input file\n";
    return 2;
  }

  size_t rows = 0;
  size_t cols = 0;

  if (!readDimensions(in, rows, cols))
  {
    std::cerr << "Invalid matrix dimensions\n";
    return 2;
  }

  if (taskType == 1 && rows * cols > MAX_ELEMENTS)
  {
    std::cerr << "Matrix size exceeds limits\n";
    return 2;
  }

  int** matrix = allocateMatrix(rows, cols);
  if (matrix == nullptr)
  {
    std::cerr << "Memory allocation failed\n";
    return 2;
  }

  if (!readMatrix(in, matrix, rows, cols))
  {
    std::cerr << "Invalid matrix data\n";
    freeMatrix(matrix, rows);
    return 2;
  }

  int result18 = processTask18(matrix, rows, cols);
  processTask8(matrix, rows, cols);

  int result8 = 0;
  for (size_t i = 0; i < rows; i++)
  {
    for (size_t j = 0; j < cols; j++)
    {
      result8 += matrix[i][j];
    }
  }

  std::ofstream out(outputFile);
  if (out.is_open())
  {
    writeResults(out, result18, result8);
  }

  std::cout << result18 << ' ' << result8 << '\n';

  freeMatrix(matrix, rows);
  return 0;
}
