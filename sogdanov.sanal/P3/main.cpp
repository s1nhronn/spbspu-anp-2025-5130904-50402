#include <iostream>
#include <fstream>
namespace sogdanov
{
  bool inputCases(std::ifstream input, int * mtx, size_t rows, size_t cols)
  {
    if (!(input >> rows >> cols)) {
      return false;
    }
    for (size_t i = 0, i < rows * cols; ++i) {
      if (!(input >> a[i])) {
        return false;
      }
    }
    return true;
  }
}
int main(int argc, char ** argv)
{
  int num = 0;
  if (argc < 4) {
    std::cerr << "Not enough arguments\n";
    return 1;
  } else if (argc > 4) {
    std::cerr << "Too many arguments\n";
    return 1;
  } else if (*argv[1] == '1') {
    num = 1;
  } else if (*argv[1] == '2') {
    num = 2;
  }
  std::cout << "num= " <<  num << " " << "argv[1]= " <<  *argv[1];

  std::ifstream input(argv[2]);
  if (!input) {
    std::cerr << "Cannot open input file\n";
    input.close();
    return 2;
  size_t rows = 0;
  size_t cols = 0;
  if (*argv[1] == '1') {
    int mtx[10000] = {};
    if (!(inputCases(input, mtx, rows, cols) {
      std::cerr << "Cannot read input data\n";
      input.close();
      return 2;
  if (num == 2) {
    int *mtx = (int *)malloc(rows * cols * sizeof(int));
  }

  input.close()
}
