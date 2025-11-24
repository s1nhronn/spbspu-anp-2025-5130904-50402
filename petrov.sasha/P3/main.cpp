#include <iostream>
#include <fstream>
#include <cstdlib>
#include <memory>

namespace petrov
{
  void lftBotCnt(std::ofstream& out, int* a, size_t r, size_t c);
  void fllIncWav(std::ofstream& out, int* a, size_t rows, size_t cols);
  void rm(int* mtx) {
    if (!mtx) {
      return;
    }
    delete[] mtx;
  }

  std::ifstream& readMTX(std::ifstream& in, int* a, size_t rows, size_t cols)
  {
    for (size_t i = 0; i < rows; ++i) {
      for (size_t j = 0; j < cols; ++j) {
        if (!(in >> a[i*cols+j])) {
          throw std::runtime_error("Failed to read matrix element");
        }
      }
    }
    char temp = ' ';
    if (in >> temp) {
      throw std::runtime_error("Too many arguments for array");
    }
    in.clear();
    return in;
  }

  bool stat(std::ifstream& in, std::ofstream& out, size_t rows, size_t cols)
  {
    if (rows == 0 || cols == 0) {
      return true;
    }
    if (rows * cols > 10000) {
      std::cerr << "Matrix too big for static buffer\n";
      return false;
    }
    int arr[10000] = {0};
    try {
      readMTX(in, arr, rows, cols);
    } catch (const std::exception& e) {
      std::cerr << e.what() << "\n";
      return false;
    }
    lftBotCnt(out, arr, rows, cols);
    return true;
  }

  bool dyn(std::ifstream& in, std::ofstream& out, size_t rows, size_t cols)
  {
    if (rows == 0 || cols == 0) {
      return true;
    }
    int* arr = nullptr;
    try {
      arr = new int[rows*cols];
    } catch (const std::bad_alloc& e) {
      rm(arr);
      std::cerr << "Memory allocation failed\n";
      return false;
    }
    try {
      readMTX(in, arr, rows, cols);
    } catch(const std::exception& e) {
      rm(arr);
      std::cerr << e.what() << "\n";
      return false;
    }
    fllIncWav(out, arr, rows, cols);
    rm(arr);
    return true;
  }

  void lftBotCnt(std::ofstream& out, int* a, size_t r, size_t c)
  {
    if (r == 0 || c == 0 || !a) {
      return;
    }
    size_t up = 0, down = r - 1, left = 0, right = c - 1;
    int counter = 1;
    while (up <= down && left <= right) {
      for (size_t j = left; j <= right; ++j) {
        a[down*c+j] += counter++;
      }
      for (size_t i = down - 1; i >= up && i < r; --i) {
        a[i*c+right] += counter++;
      }
      if (up < down) {
        for (size_t j = right - 1; j >= left && j < c; --j) {
          a[up*c+j] += counter++;
        }
      }
      if (left < right) {
        for (size_t i = up + 1; i < down; ++i) {
          a[i*c+left] += counter++;
        }
      }
      up++;
      down--;
      left++;
      right--;
    }
    for (size_t i = 0; i < r; ++i) {
      for (size_t j = 0; j < c; ++j) {
        out << a[i*c+j] << ' ';
      }
    }
  }

  void fllIncWav(std::ofstream& out, int* a, size_t rows, size_t cols)
  {
    size_t min_data = (rows < cols) ? rows : cols;
    size_t borders = (min_data + 1) / 2;
    for (size_t border = 0; border < borders; ++border) {
      int counter = border + 1;
      for (size_t j = border; j < cols - border; ++j) {
        a[border*cols+j]+=counter;
      }
      for (size_t i = border + 1; i < rows - border; ++i) {
        a[i*cols+(cols-1-border)]+=counter;
      }
      if (border < rows - 1 - border) {
        for (size_t j = cols - 1 - border; j-- > border; ) {
          a[(rows-1-border)*cols+j]+=counter;
        }
      }
      if (border < cols - 1 - border) {
        for (size_t i = rows - 1 - border; i-- > border + 1; ) {
          a[i*cols+border]+=counter;
        }
      }
    }
    for (size_t i = 0; i < rows; ++i) {
      for (size_t j = 0; j < cols; ++j) {
        out << a[i*cols+j] << ' ';
      }
    }
  }
}

int main(int argc, char ** argv)
{
  if (argc != 4) {
    std::cerr << (argc < 4 ? "Not enough arguments\n" : "Too many arguments\n");
    return 1;
  }
  char* endptr = nullptr;
  long temp = std::strtol(argv[1], std::addressof(endptr), 10);
  if (argv[1] == endptr) {
    std::cerr << "First parameter is not a number\n";
    return 1;
  }
  if (*endptr != '\0') {
    std::cerr << "First parameter contains invalid symbols\n";
    return 1;
  }
  if (temp != 1 && temp != 2) {
    std::cerr << "First parameter is out of range\n";
    return 1;
  }
  std::ifstream input(argv[2]);
  std::ofstream output(argv[3]);
  if (!input.is_open() || !output.is_open()) {
    std::cerr << "Cannot open file\n";
    return 2;
  }
  int rows = 0, cols = 0;
  if (!(input >> rows >> cols)) {
    std::cerr << "Invalid matrix data\n";
    return 2;
  }
  output << rows << " " << cols << " ";
  bool success = true;
  if (temp == 1) {
    success = petrov::stat(input, output, rows, cols);
  } else {
    success = petrov::dyn(input, output, rows, cols);
  }
  return success ? 0 : 2;
}

