#include <iostream>
#include <fstream>
#include <limits>
#include <algorithm>
#include <cstddef>
#include <cstdlib>

namespace muhamadiarov
{
  int maxInt();
  int minInt();
  int* fllIncWav(int* ptr, int rows, int colons);
  void outMatric(std::ofstream &output, int r, int c, int* res1);
  long long toFindMaxRight(int* ptr, int order);
  long long toFindMaxinLeft(int* ptr, int order);
  long long maxSumMdg(int* ptr, int order);
  bool checkSizeMatric(int r, int c);
  void inputMatric(int* ptr, int r, int c, std::istream &input);
}

int main(int argc, char* argv[])
{
  namespace muh = muhamadiarov;
  if (argc > 4)
  {
    std::cerr << "Too many arguments\n";
    return 1;
  }
  if (argc < 4)
  {
    std::cerr << "Not enough arguments\n";
    return 1;
  }
  int mode = 0;
  try
  {
    mode = std::stoi(argv[1]);
  }
  catch (std::out_of_range &e)
  {
    std::cerr << "First parameter  is not a number\n";
    return 1;
  }
  if (mode < 1 || mode > 2)
  {
    std::cerr << "First parameter is out of range\n";
    return 1;
  }
  std::ifstream input(argv[2]);
  if (!input)
  {
    std::cerr << "Error is openning file\n";
    return 2;
  }
  int rows, colons = 0;
  input >> rows >> colons;
  if (input.eof() || input.fail())
  {
    std::cerr << "Error is openning file\n";
    return 2;
  }
  bool isSizeWrong = muh::checkSizeMatric(rows, colons);
  if (input.eof() || input.fail())
  if (isSizeWrong)
  {
    std::cerr << "Wrong size of matric\n";
    return 2;
  }
  int* res1 = nullptr;
  long long int res2 = 0;
  if (rows == 0 && colons == 0)
  {
    std::ofstream output(argv[3], std::ios::app);
    output << 0 << ' ' << 0 << '\n';
    output << 0;
    return 0;
  }
  int arr[10000];
  int* ptr = nullptr;
  if (mode == 1)
  {
    ptr = arr;
    try
    {
      muh::inputMatric(ptr, rows, colons, input);
    }
    catch (const std::logic_error &e)
    {
      std::cerr << e.what() << '\n';
      return 2;
    }
  }
  else if (mode == 2)
  {
    ptr = reinterpret_cast< int* >(malloc(rows * colons * sizeof(int)));
    if (ptr == nullptr)
    {
      std::cerr << "Failed to allocate memory\n";
      return 1;
    }
    try
    {
      muh::inputMatric(ptr, rows, colons, input);
    }
    catch (const std::logic_error &e)
    {
      free(ptr);
      std::cerr << e.what() << '\n';
      return 1;
    }
  }
  input.close();
  int order = std::min(rows, colons);
  res2 = muh::maxSumMdg(ptr, order);
  res1 = muh::fllIncWav(ptr, rows, colons);
  std::ofstream output(argv[3], std::ios::app);
  if(!output)
  {
    std::cerr << "Error in opening file\n";
    if (mode == 2)
    {
      free(ptr);
    }
    return 2;
  }
  muh::outMatric(output, rows, colons, res1);
  output << '\n';
  output << res2;
  output.close();
  if (mode == 2)
  {
    free(ptr);
  }
  return 0;
}

int* muhamadiarov::fllIncWav(int* ptr, int rows, int colons)
{
  for (int j = 0; j < rows; ++j)
  {
    for (int i = 0; i < colons; ++i)
    {
      int increase = 0;
      int top = j;
      int bottom = rows - 1 - j;
      int left = i;
      int right = colons - 1 - i;
      increase = std::min(std::min(top, bottom), std::min(left, right)) + 1;
      ptr[j * colons + i] += increase;
    }
  }
  return ptr;
}

long long muhamadiarov::maxSumMdg(int* ptr, int order)
{
  namespace muh = muhamadiarov;
  long long max_result = 0;
  long long par_branch_right = muh::toFindMaxRight(ptr, order);
  long long par_branch_left = muh::toFindMaxinLeft(ptr, order);
  max_result = std::max(par_branch_right, par_branch_left);
  return max_result;
}

long long muhamadiarov::toFindMaxinLeft(int* ptr, int order)
{
  long long max_r = 0;
  long long result = 0;
  int diag = 0;
  while (diag < order)
  {
    for (int i = diag, j = 0; i >= 0 && j <= diag; --i, ++j)
    {
      result += ptr[j * order + i];
    }
    ++diag;
    max_r = std::max(result, max_r);
    result = 0;
  }
  return max_r;
}

long long muhamadiarov::toFindMaxRight(int* ptr, int order)
{
  long long int max_r = 0;
  long long int result = 0;
  int diag = order - 1;
  while (diag > 0)
  {
    for (int i = order - 1, j = diag; j < order && i >= diag; --i, ++j)
    {
      result += ptr[j * order + i];
    }
    --diag;
    max_r = std::max(result, max_r);
    result = 0;
  }
  return max_r;
}

void muhamadiarov::outMatric(std::ofstream &output, int r, int c, int* res1)
{
  for (int i = 0; i < r * c; ++i)
  {
    output << res1[i] << " ";
  }
}

int muhamadiarov::maxInt()
{
  using namespace std;
  return numeric_limits<int>::max();
}

int muhamadiarov::minInt()
{
  using namespace std;
  return numeric_limits<int>::min();
}

bool muhamadiarov::checkSizeMatric(int r, int c)
{
  namespace muh = muhamadiarov;
  bool c1 = (r != 0 && c == 0) || (r == 0 && c != 0);
  bool c2 = r > muh::maxInt() || c < muh::minInt() || c < 0 || r < 0;
  return c1 || c2;
}

void muhamadiarov::inputMatric(int* ptr, int r, int c, std::istream &input)
{
  namespace muh = muhamadiarov;
  for (int i = 0; i < r * c; ++i)
  {
    input >> ptr[i];
    if (ptr[i] > muh::maxInt() || ptr[i] < muh::minInt())
    {
      throw std::logic_error("The number is not int\n");
    }
    else if (input.eof())
    {
      throw std::logic_error("Not enough the numbers of elements\n");
    }
    else if (input.fail())
    {
      throw std::logic_error("Wrong working read\n");
    }
  }
}
