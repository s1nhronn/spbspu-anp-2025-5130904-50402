#include <iostream>
#include <fstream>
#include <cstdlib>
#include <memory>

namespace pozdnyakov
{
  const size_t MAX_ELEMENTS = 10000;
  const size_t MAX_ROWS = 100;
  const size_t MAX_COLS = 100;

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

    if (r < 0 || c < 0)
    {
      in.setstate(std::ios::failbit);
      return in;
    }

    rows = static_cast <size_t>(r);
    cols = static_cast <size_t>(c);

    return in;
  }

  std::istream& readMatrix(std::istream& in,
    int** data,
    size_t rows,
    size_t cols)
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

  int countDiagonalsWithoutZero(int** data, size_t rows, size_t cols)
  {
    if (rows == 0 || cols == 0)
    {
      return 0;
    }

    int count = 0;
    size_t maxDiag = rows + cols - 2;

    for (size_t k = 0; k <= maxDiag; k++)
    {
      bool exists = false;
      bool hasZero = false;

      for (size_t i = 0; i < rows; i++)
      {
        size_t j =
          (k >= i)
          ? (k - i)
          : MAX_COLS;

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

  void transformMatrixLayers(int** data, size_t rows, size_t cols)
  {
    if (rows == 0 || cols == 0)
    {
      return;
    }

    size_t layers = (rows < cols ? rows : cols);
    layers = (layers + 1) / 2;

    for (size_t layer = 0; layer < layers; layer++)
    {
      int inc = static_cast <int>(layer + 1);

      for (size_t r = layer; r < rows - layer; r++)
      {
        for (size_t c = layer; c < cols - layer; c++)
        {
          data[r][c] += inc;
        }
      }
    }
  }

  std::ostream& writeMatrixResults(std::ostream& out,
    int diagCount,
    int** data,
    size_t rows,
    size_t cols)
  {
    out << diagCount << '\n';

    out << rows << ' ' << cols << '\n';
    for (size_t i = 0; i < rows; i++)
    {
      for (size_t j = 0; j < cols; j++)
      {
        out << data[i][j];
        if (j + 1 < cols)
        {
          out << ' ';
        }
      }
      out << '\n';
    }

    return out;
  }

  bool validateArgs(const char* s)
  {
    char* endptr = nullptr;

    long num = std::strtol(s, std::addressof(endptr), 10);
    if (endptr == s || *endptr != '\0')
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

  if (argc != 4)
  {
    std::cerr << "Invalid number of arguments\n";
    return 1;
  }

  if (!validateArgs(argv[1]))
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

  if (rows == 0 || cols == 0)
  {
    std::ofstream out(outputFile);
    if (!out.is_open())
    {
      std::cerr << "Cannot open output file\n";
      return 3;
    }

    out << 0 << '\n';
    out << 0 << ' ' << 0 << '\n';

    return 0;
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

  int diagCount = countDiagonalsWithoutZero(matrix, rows, cols);
  transformMatrixLayers(matrix, rows, cols);

  std::ofstream out(outputFile);
  if (!out.is_open())
  {
    std::cerr << "Cannot open output file\n";
    freeMatrix(matrix, rows);
    return 3;
  }

  writeMatrixResults(out, diagCount, matrix, rows, cols);

  freeMatrix(matrix, rows);
  return 0;
}
