#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <cstring>
namespace chernikov
{
    bool is_down_triangle_matrix (const int * a, int rows, int cols);
    size_t local_max_quantity(const int* a, int rows, int cols);
}

int main (int argc, char ** argv)
{
  char** end = argv + argc;
  for (char** i = argv; i < end; ++i)
  {
    std::cout << *i << "\n";
  }
  // checking the number of parameters
  if (argc < 4 || argc > 4)
  {
    std::cerr << "Mismatch in the number of parameters\n";
    return 1;
  }

  std::ifstream input(argv[2]);
  if (!input.is_open())
  {
    std::cerr << "Failed to read file\n";
    return 1;
  }
  if (input.peek() == std::ifstream::traits_type::eof())
  {
    std::cerr << "Empty input file" << std::endl;  // magic!
    input.close();
    return 2;
    }
  int rows, cols;
  input >> rows >> cols;

  bool isDynamic = false;
  int* a = nullptr;
  const int MAX_SIZE = 10000;
  int nums[MAX_SIZE] = {};
  if (std::string(argv[1]) == "1")
  {
    memset(nums, 0, sizeof(nums));
    a = nums;
    isDynamic = false;
  }
  else if (std::string(argv[1]) == "2")
  {
    a = static_cast<int*>(malloc(sizeof(int) * (rows * cols)));
    isDynamic = true;
    if (a == nullptr)
    {
      std::cerr << "Memory allocation failed\n";
      return 2;
    }
  }
  else
  {
    std::cerr << "Parameter 2 is set incorrectly\n";
    return 2;
  }
  memset(a, 0, sizeof(int) * rows * cols);
  // reading file_2: filling the matrix
  int col = 0;
  for (int i = 0; i < (rows * cols); ++i)
  {
    if (!(input >> a[i]))
    {
      std::cerr << "Failed to count element\n";
      if (isDynamic && a != nullptr)
      {
        free(a);
      }
      return 2;
    }
    ++col;

  }
  if (col != (rows * cols))
  {
    std::cerr << "Not enough data";
    if (isDynamic && a != nullptr)
    {
      free(a);
      return 2;
    }
    else
    {
      return 2;
    }
  }
  input.close();

  //LWR-TRI-MTX
  bool LWR_TRI_MTX = chernikov::is_down_triangle_matrix (a, rows, cols);
  std::ofstream output(argv[3]);
  output << "LWR_TRI_MTX = " << LWR_TRI_MTX << "\n";

  //MAX
  size_t CNT_LOC_MAX = chernikov::local_max_quantity (a, rows, cols);
  output << "CNT_LOC_MAX = " << CNT_LOC_MAX << "\n";

  output.close();

  if (isDynamic == true && a != nullptr)
  {
    free(a);
    a = nullptr;
  }
  return 0;
}

bool chernikov::is_down_triangle_matrix(const int* a, int rows, int cols)
{
  if (rows != cols)
  {
    return false;
  }
  for (int i = 0; i < rows; ++i)
  {
    for (int j = i + 1; j < cols; ++j)
    {
      int index = i * cols + j;
      if (a[index] != 0)
      {
        return false;
      }
    }
  }
  return true;
}

size_t chernikov::local_max_quantity(const int* a, int rows, int cols)
{
  if (rows < 3 || cols < 3)
  {
    return 0;
  }
  size_t count = 0;
  for (int i = 1; i < (rows - 1); ++i)
  {
    for (int j = 1; j < (cols - 1); ++j)
    {
      bool t = a[j + i * cols];
      bool l1 = t > a[(j - 1) + (i - 1) * cols];
      bool l2 = t > a[j + (i - 1) * cols];
      bool l3 = t > a[(j + 1) + (i - 1) * cols];
      bool l4 = t > a[(j - 1) + i * cols];
      bool l5 = t > a[(j + 1) + i * cols];
      bool l6 = t > a[(j - 1) + (i + 1) * cols];
      bool l7 = t > a[j + (i + 1) * cols];
      bool l8 = t > a[(j + 1) + (i + 1) * cols];
      if (l1 + l2 + l3 + l4 + l5 + l6 + l7 + l8 == 8)
      {
        count++;
      }
    }
  }
  return count;
}
