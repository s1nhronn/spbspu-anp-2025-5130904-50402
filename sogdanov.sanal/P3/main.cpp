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
  int cnt_sdl_pnt(const int * mtx, int rows, int cols)
  {
    if (rows == 0 || cols == 0) {
      return 0;
    }
    int * rowMin = (int*)malloc(rows * sizeof(int));
    for (int i = 0; i < rows; ++i) {
      int minValue = mtx[i * cols];
      for (int j = 1; j < cols; ++j) {
        if (mtx[i * cols + j] < minValue) {
          minValue = mtx[i * cols +j];
        }
      }
      rowMin[i] = minValue;
    }
    int * colMax = (int*)malloc(cols * sizeof(int));
    for (int i = 0; i < cols; ++i) {
      int maxValue = mtx[i];
      for (int j = 1; j < rows; ++j) {
        if (mtx[j * cols + i] > maxVal) {
          maxVal = mtx[j * cols + i];
        }
      }
      colMax[i] = maxVal;
    }
    int count = 0;
    for (int i = 0; i < rows; ++i) {
      for (int j = 0; j < cols; ++j) {
        int value = mtx[i * cols + j];
        if ( value == rowMin[i] && value == colMax[j]) {
          count++;
        }
      }
    }
    free(rowMin);
    free(colsMax);
    return count;
  }
  size_t max_sum_sgd(int * a, int rows, int cols)
  {
    if (rows == 0 || cols == 0) {
      return 0;
    }
    int n = rows < cols ? rows : cols;
    long long maxSum = 0;
    for (int i = 1; i < n; ++i) {
      long long sum = 0;
      for (int j = 0; j < n - i; ++j) {
        sum += a[j * cols + j + i];
      }
      if (!hasDiag || sum > maxSum) {
        maxSum = sum;
      }
    }
    for (size_t i = 1; i < n; i++) {
      long long sum = 0;
      for (size_t j = 0; j < n - i; j++) {
        sum += a[cols * (j + i) + j];
      }
      if (sum > maxSum) {
        maxSum = sum;
      }
    }
    return maxSum;
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
  std::ifstream input(argv[2]);
  if (!input) {
    std::cerr << "Cannot open input file\n";
    input.close();
    return 2;
  int rows = 0;
  int cols = 0;
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
