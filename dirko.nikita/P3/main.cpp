#include <iostream>
#include <fstream>

namespace dirko
{
  std::istream &staticInput(std::istream &in, int *arr, size_t r, size_t c);
  std::istream &dinamicInput(std::istream &in, int *arr, size_t r, size_t c);
  void var1(int *arr, int *res1, size_t r, size_t c);
  bool var2(int *arr, size_t r, size_t c);
  std::ostream &output(std::ostream &out, int *arr, size_t r, size_t c);
}

int main(int argc, char const **argv)
{
  int mode = 0;
  if (argc < 4)
  {
    std::cerr << "Not enough arguments\n";
    return 1;
  }
  if (argc > 4)
  {
    std::cerr << "Too many arguments\n";
    return 1;
  }
  try
  {
    mode = std::stoi(argv[1]);
  }
  catch (std::out_of_range &e)
  {
    std::cerr << "First parameter is not a number\n";
    return 1;
  }
  if (mode < 1 || mode > 2)
  {
    std::cerr << "First parameter is out of range\n";
    return 1;
  }
  std::ifstream fin(argv[2]);
  // std::ofstream fout(argv[3]);
  if (!fin.is_open())
  {
    std::cerr << "Cant open input file\n";
    return 2;
  }
  size_t rows = 0, cols = 0;
  fin >> rows >> cols;
  if (mode == 1)
  {
    int arr[1000]{}, res1[1000]{};
    bool res2 = false;
    dirko::staticInput(fin, arr, rows, cols);
    fin.close();
    dirko::var1(arr, res1, rows, cols);
    res2 = dirko::var2(arr, rows, cols);
    std::ofstream fout(argv[3]);
    dirko::output(fout, arr, rows, cols);
  }
  else
  {
    int *arr = nullptr;
    int *res1 = nullptr;
    bool res2 = false;
    dirko::dinamicInput(fin, arr, rows, cols);
    fin.close();
    dirko::var1(arr, res1, rows, cols);
    res2 = dirko::var2(arr, rows, cols);
    std::ofstream fout(argv[3]);
    dirko::output(fout, arr, rows, cols);
    delete[] arr;
    delete[] res1;
  }
}
