#include <iostream>
#include <fstream>
namespace sogdanov
{
  int readMatrix(std::ifstream & input, int * mtxm int rows, int cols)
  {
    for (int i = 0; i < rows * cols ; i++) {
      input >> mtx[i];
      if (input.fail()) {
        std::cerr << "Input error\n";
        return 2;
      }
    }
    int extra;
    if (input >> extra) {
      std::cerr << "Too many elements in input file\n";
      return 2;
    }
    return 0;
  }
  size_t max_sum_sgd(int * a, size_t rows, size_t cols)
  {
    if (rows == 0 || cols == 0) {
      return 0;
    }
    long long maxSum = -1000000;
    size_t n = rows;
    for (size_t i = 1; i < n; i++) {
      long long sum = 0;
      for (size_t j = 0; j < n - i; j++) {
        sum += a[j * n + j + i];
      }
      if (sum > maxSum) {
        maxSum = sum;
      }
   }
   for (size_t i = 1; i < n; i++) {
      long long sum = 0;
      for (size_t j = 0; j < n - i; j++) {
        sum += a[(j + i) * n + j ];
      }
      if (sum > maxSum) {
        maxSum = sum;
      }
   }
   return maxSum;
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
  std::ifstream input(argv[2]);
  if (!input) {
    std::cerr << "Cannot open input file\n";
    input.close();
    return 2;
  size_t rows = 0;
  size_t cols = 0;
  input >> rows >> cols;
  if ( input.fail() || rows < 0 || cols < 0) {
    std::cerr << "Incorrect Matrix Sizes\n";
    input.close();
    return 2;
  }
  int * mtx = nullptr;
  if (*argv[1] == '1') {
    int mtx[10000] = {};
    if (!(inputCases(input, mtx, rows, cols) {
      std::cerr << "Cannot read input data\n";
      input.close();
      return 2;
  if (*argv[1] == '2') {
    int *mtx = (int *)malloc(rows * cols * sizeof(int));
    if (!mtx) {
      std::cerr << "Memory allocation failed\n";
      input.close();
      return 2;
    }
    for (size_t i = 0; i < rows * cols; ++i) {
      input >> mtx[i];
    }
    long long res = sogdanov::max_sum_sdg(mtx, rows, cols);
  }

  input.close();
