#include <iostream>
#include <fstream>
namespace chernikov
{
    void output (const int * a, size_t c, size_t r);
    bool is_down_triangle_matrix (const int * a, int rows, int cols);
}

int main (int argc, char ** argv)
{
  char** end = argv + argc;
  for (char** i = argv; i < end; ++i)
  {
    std::cout << *i << "\n";
  }
  // checking the number of parameters
  if (argc < 4)
  {
    std::cerr << "Mismatch in the number of parameters\n";
    return 1;
  {

  // reading file_1: memory allocation
    std::ifstream input(argv[2]);
  if (!input.is_open())
  {
    std::cerr << "Failed to read file\n";
    return 2;
  }
  int rows, cols;
  if (!(input >> rows >> cols))
  {
    std::cerr << "Failed to read matrix dimensions\n";
    return 2;
  }
  if (rows == 0 && cols == 0) {
    std::cerr << "Empty matrix\n";
    return 2;
  }
  if (rows < 0 || cols < 0) {
    std::cerr << "Invalid matrix dimensions\n";
    return 2;
  }

  // memory allocation
  if (argv[1] == "1")
  {
    int a[10000] = {};
  }
  else if (argv[1] == "2")
  {
      int* nums = reinterpret_cast<int*>(malloc(sizeof(int) * (rows * cols)));
      if (nums == nullptr)
      {
        std::cerr << "Memory allocation failed\n";
        return 2;
      }
  }
  else
  {
    std::cerr << "parameter 2 is set incorrectly";
    return 2;
  }

  // reading file_2: filling the matrix
  for (size_t i = 0; i < (rows * cols); ++i)
  {
    input >> a[i];

  }
  input.close();

  //LWR-TRI-MTX
  namespace cher = chernikov;
  bool LWR_TRI_MTX = is_down_triangle_matrix (a, rows, cols);
  std::ofstream output(argv[3]);
  output << "LWR_TRI_MTX = " << LWR_TRI_MTX << "\n";

  //MAX
  size_t CNT_LOC_MAX = local_max_quantity (a, rows, cols);
  output << "CNT_LOC_MAX = " << CNT_LOC_MAX << "\n";

  std::ofstream output(argv[3]);
  output(output, ... ) << "\n"
  if (std::ofstream.fail())
  {
    return 1;
  }
  //output << a;
}

void output (std::ostream & out, const int * a, size_t c, size_t r)
{
  return out << ... ;
}

bool is_down_triangle_matrix(const int* a, int rows, int cols)
{
  if (rows == cols)
  {
    if (a[0] == 0)
    {
      int k = 0;
      for (size_t i = 0; i < (rows - 1); ++i)
      {
        int line = rows * i;
        for (size_t j = 0; j < (cols - k); ++j)
        {
          if (a[j + line] != 0)
          {
              return false;
          }
        }
        k++;
      }
      return true;
    }
    if (a[cols - 1] == 0)
    {
      int k = 0;
      for (size_t i = 0; i < (rows - 1); ++i)
      {
        int line = rows * i;
        for (size_t j = (cols); j > k; --j)
        {
          if (a[j - line] != 0)
          {
            return false;
          }
        }
        k++;
      }
      return true;
    }
    else
    {
      return false;
    }
  }
  else
  {
      return false;
  }
}

size_t local_max_quantity(const int* a, int rows, int cols)
{
  if (rows < 3 || cols < 3)
  {
    return 0;
  }
  size_t count = 0;
  for (size_t i = 1; i < (rows - 1); ++i)
  {
    for (size_t j = 1; j < (cols - 1); ++j)
    {
      t = a[j + i * cols];
      l1 = t > a[(j - 1) + (i - 1) * cols];
      l2 = t > a[j + (i - 1) * cols];
      l3 = t > a[(j + 1) + (i - 1) * cols];
      l4 = t > a[(j - 1) + i * cols];
      l5 = t > a[(j + 1) + i * cols];
      l6 = t > a[(j - 1) + (i + 1) * cols];
      l7 = t > a[j + (i + 1) * cols];
      l1 = t > a[(j + 1) + (i + 1) * cols];
      if (l1 + l2 + l3 + l4 + l5 + l6 + l7 + l8 == 8)
      {
        count++;
      }
    }
  }
  return count;
}
