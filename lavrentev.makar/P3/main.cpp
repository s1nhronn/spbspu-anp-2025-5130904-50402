#include <algorithm>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <cstring>
#include <limits>

const size_t STATIC_SIZE = 10000;

namespace pThrFunc
{
  size_t cntLocMin(int* arr, size_t x, size_t y);
  size_t numColLsr(int* arr, size_t x, size_t y);
  int inputFile(std::istream& in, int* m, size_t lng);
}

int main(int argc, char **argv)
{
  if (argc < 4)
  {
    std::cerr << "Not enough arguments" << "\n";
    return 1;
  }
  if (argc > 4)
  {
    std::cerr << "Too many arguments" << "\n";
    return 1;
  }
  if (!isdigit(*argv[1]))
  {
    std::cerr << "First parameter is not a number" << "\n";
    return 1;
  }
  int num = 0;
  try
  {
    num = std::stoi(argv[1]);
  }
  catch (const std::overflow_error &e)
  {
    std::cerr << e.what() << '\n';
    return 1;
  }
  if (num != 1 && num != 2)
  {
    std::cerr << "First parameter is out of range" << "\n";
    return 1;
  }

  std::ifstream input(argv[2]);

  if (!input.is_open())
  {
    std::cerr << "Uncorrect file" << "\n";
    return 2;
  }

  size_t x, y;

  if (!(input >> x >> y))
  {
    std::cerr << "Uncorrect file" << "\n";
    return 2;
  }

  size_t total = x * y;

  int arr2[STATIC_SIZE] = {};
  int* arr = nullptr;

  int *matrix = nullptr;
  try
  {
    if (num == 1)
    {
      matrix = arr2;
    }
    else
    {
      int total_for_memory = static_cast<int>(x * y);
      arr = static_cast <int*> (malloc(total_for_memory * sizeof(int)));
      matrix = arr;
    }
    int k = pThrFunc::inputFile(input, matrix, total);
    if (k == 2)
    {
      std::cerr << "Couldn't read the matrix" << "\n";
      free(arr);
      return 2;
    }
  }
  catch (const std::logic_error &e)
  {
    std::cerr << e.what() << '\n';
    free(arr);
    return 2;
  }

  size_t ans2 = pThrFunc::cntLocMin(matrix, x, y);
  size_t ans11 = pThrFunc::numColLsr(matrix, x, y);

  std::ofstream output(argv[3]);

  output << "Answer for var_2: " << ans2 << "\n";
  output << "Answer for var_11: " << ans11 << "\n";

  free(arr);
}

size_t pThrFunc::cntLocMin(int* arr, size_t x, size_t y){

  size_t ans_2 = 0;
  size_t total = x * y;

  for (size_t i = y + 1; i < total - y; ++i)
  {
    if ((i % y != 0) && (i % y != y - 1))
    {
      bool b1 = (arr[i] < arr[i + 1]) && (arr[i] < arr[i - 1]);
      b1 = b1 && (arr[i] < arr[i + y]) && (arr[i] < arr[i - y]);
      b1 = b1 && (arr[i] < arr[i + y + 1]) && (arr[i] < arr[i - y - 1]);
      b1 = b1 && (arr[i] < arr[i + y - 1]) && (arr[i] < arr[i - y + 1]);
      if (b1)
      {
        ++ans_2;
      }
    }
  }

  return ans_2;
}

size_t pThrFunc::numColLsr(int* arr, size_t x, size_t y)
{
  int ans_11 = 0;
  size_t total = x * y;
  int max_length = 0;

  int mas[y][2];
  for (size_t i = 0; i < y; ++i)
  {
    mas[i][0] = -1;
    mas[i][1] = 0;
  }

  for (size_t i = 0; i < total; ++i)
  {
    size_t j = i % y;
    if (mas[j][0] == -1)
    {
      mas[j][0] = j + 1;
      mas[j][1] = 1;
    }
    else
    {
      if (arr[i] == arr[i - y])
      {
        ++mas[j][1];
      }
      else
      {
        if (mas[j][1] > max_length)
        {
          max_length = mas[j][1];
        }
        mas[j][1] = 1;
      }
    }
  }

  for (size_t i = 0; i < y; ++i)
  {
    if (max_length < mas[i][1])
    {
      ans_11 = mas[i][0];
      max_length = mas[i][1];
    }
  }

  return ans_11;
}

int pThrFunc::inputFile(std::istream& in, int* m, size_t lng)
{
  for (size_t i = 0; i < lng; i++)
  {
    in >> m[i];
    if (in.fail())
    {
      return 2;
    }
  }
  return 0;
}
