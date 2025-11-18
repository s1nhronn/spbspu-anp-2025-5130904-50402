#include <iostream>
#include <fstream>
namespace sogdanov
{
  std::istream & readMatrix(std::ifstream & input, int * mtx, size_t rows, size_t cols)
  {
    for (size_t i = 0; i < rows * cols ; i++) {
      if (!(input >> mtx[i])) {
        return input;
      }
    }
    return input;
  }
  int cntSdlPnt(const int * mtx, size_t rows, size_t cols)
  {
    if (rows == 0 || cols == 0) {
      return 0;
    }
    int * rowMin = static_cast< int* >(malloc(rows * sizeof(int)));
    if (rowMin == nullptr) {
      std::cerr << "Memory allocation failed\n";
      return 2;
    }
    for (size_t i = 0; i < rows; ++i) {
      int minValue = mtx[i * cols];
      for (size_t j = 1; j < cols; ++j) {
        if (mtx[i * cols + j] < minValue) {
          minValue = mtx[i * cols +j];
        }
      }
      rowMin[i] = minValue;
    }
    size_t count = 0;
    for (size_t i = 0; i < cols; ++i) {
      int maxVal = mtx[i];
      for (size_t j = 1; j < rows; ++j) {
        if (mtx[j * cols + i] > maxVal) {
          maxVal = mtx[j * cols + i];
        }
      }
      for (size_t j = 0; j < rows; ++j) {
        if (mtx[j * cols + i] == maxVal && mtx[j * cols + i] == rowMin[j]) {
          count++;
        }
      }
    }
    free(rowMin);
    return count;
  }
  int maxSumSdg(int * a, size_t rows, size_t cols)
  {
    if (rows == 0 || cols == 0) {
      return 0;
    }
    size_t n = rows < cols ? rows : cols;
    long long maxSum = 0;
    for (size_t i = 1; i < n; ++i) {
      long long sum = 0;
      for (size_t j = 0; j < n - i; ++j) {
        sum += a[j * cols + j + i];
      }
      if (sum > maxSum) {
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
  const size_t SIZE = 10000;
  static int static_mtx[SIZE] = {};
  int * createMatrix(int num, size_t rows, size_t cols)
  {
    if (num  == 1) {
      return static_mtx;
    } else if (num == 2) {
      return reinterpret_cast< int* >(malloc(rows * cols * sizeof(int)));
    }
    return nullptr;
  }
  void rm (char num, int * mtx)
  {
    if (num == 2 && mtx != nullptr) {
      free(mtx);
    }
  }
}

int main(int argc, char ** argv)
{
  if (argc < 4) {
    std::cerr << "Not enough arguments\n";
    return 1;
  }
  if (argc > 4) {
    std::cerr << "Too many arguments\n";
    return 1;
  }
  int num;
  try {
    num = std::stoi(argv[1]);
    if (num != 1 && num != 2) {
      std::cerr << "First argument is out of range\n";
    }
  } catch ( const std::invalid_argument & e) {
    std::cerr << "First argument is not a number\n";
    return 1;
  }
  std::ifstream input(argv[2]);
  if (!input) {
    std::cerr << "Cannot open input file\n";
    return 2;
  }
  size_t rows = 0;
  size_t cols = 0;
  input >> rows >> cols;
  if (rows > 10000 || cols > 10000 || rows * cols > 10000) {
    std::cerr << "Matrix sizes are too large\n";
    input.close();
    return 2;
  }
  if (input.fail()) {
    std::cerr << "Incorrect Matrix Sizes\n";
    input.close();
    return 2;
  }
  int * mtx = sogdanov::createMatrix(num, rows, cols);
  if (mtx == nullptr) {
    std::cerr << "Memory allocation failed\n";
    input.close();
    return 2;
  }
  int res1 = 0;
  int res2 = 0;
  sogdanov::readMatrix(input, mtx, rows, cols);
  if (input.fail()) {
    std::cerr << "Input error\n";
    sogdanov::rm(num, mtx);
    input.close();
    return 2;
  }
  int extra;
  if (input >> extra) {
    std::cerr <<"Too many elements in input file\n";
    sogdanov::rm(num, mtx);
    input.close();
    return 2;
  }
  res1 = sogdanov::maxSumSdg(mtx, rows, cols);
  res2 = sogdanov::cntSdlPnt(mtx, rows, cols);
  sogdanov::rm(num, mtx);
  input.close();
  std::ofstream output(argv[3]);
  if (!output) {
    std::cerr << "Cannot open output file\n";
  }
  output << res1 << ' ' << res2 << "\n";
}
