#include <cstddef>
#include <exception>
#include <fstream>
#include <iostream>
#include <limits>
#include <new>
#include <stdexcept>
#include <string>

namespace novikov {
  void remove(int ** mtx, size_t r)
  {
    for (size_t i = 0; i < r; ++i) {
      delete[] mtx[i];
    }
    delete[] mtx;
  }

  bool isDigit(const char * str)
  {
    if (str == nullptr) {
      return false;
    }
    for (size_t i = 0; str[i] != '\0'; ++i) {
      if (!(str[i] >= '0' && str[i] <= '9')) {
        return false;
      }
    }
    return true;
  }

  int minSum(int ** mtx, size_t r, size_t c)
  {
    int sum;
    int min = std::numeric_limits< int >::max();
    if (r + c < 2) {
      return 0;
    }
    for (size_t k = 0; k <= r + c - 2; ++k) {
      sum = 0;
      for (size_t i = 0; i < r; ++i) {
        if (k - i < c) {
          sum += mtx[i][k - i];
        }
      }
      min = (sum < min) ? sum : min;
    }
    return min;
  }

  void addPeripheral(int ** mtx, size_t r, size_t c)
  {
    size_t center_row = (r % 2) ? r + 1 : r;
    for (size_t current_row = 0; current_row < center_row; ++current_row) {
      for (size_t i = current_row; i < r - current_row; ++i) {
        for (size_t j = current_row; j < c - current_row; ++j) {
          ++mtx[i][j];
        }
      }
    }
  }

  const size_t max_length = 10000;
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

  if (!novikov::isDigit(argv[1])) {
    std::cerr << "First parameter is not a number\n";
    return 1;
  }

  if (argv[1][0] != '1' && argv[1][0] != '2') {
    std::cerr << "First parameter is out of range\n";
    return 1;
  }

  std::ifstream input(argv[2]);
  std::ofstream output(argv[3]);

  if (!input.is_open()) {
    std::cerr << "Failed to open input file\n";
    return 2;
  }
  if (!output.is_open()) {
    std::cerr << "Failed to open output file\n";
    return 2;
  }

  size_t rows, cols;
  input >> rows >> cols;
  if (input.eof()) {
    std::cerr << "Not enough data\n";
    return 2;
  }
  if (input.fail()) {
    std::cerr << "Invalid input\n";
    return 2;
  }

  try {
    if (argv[1][0] == '1') {
      if (rows * cols > novikov::max_length) {
        std::cerr << "Matrix is too large\n";
        return 2;
      }

      size_t count = 0;
      int static_mtx[rows][cols];
      int * mtx[rows];

      for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < cols; ++j) {
          input >> static_mtx[i][j];
          if (input.eof()) {
            std::cerr << "Wrong matrix format\n";
            return 2;
          }
          if (input.fail()) {
            std::cerr << "Invalid input\n";
            return 2;
          }
          ++count;
        }
      }

      for (size_t i = 0; i < rows; ++i) {
        mtx[i] = static_mtx[i];
      }

      int min = novikov::minSum(mtx, rows, cols);
      novikov::addPeripheral(mtx, rows, cols);

      output << min << " " << rows << " " << cols;
      for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < cols; ++j) {
          output << " " << mtx[i][j];
        }
      }
    } else if (argv[1][0] == '2') {
      int ** mtx = new int * [rows];

      for (size_t i = 0; i < rows; ++i) {
        try {
          mtx[i] = new int[cols];
        } catch (std::bad_alloc &) {
          novikov::remove(mtx, i);
          throw;
        }
      }

      size_t count = 0;

      for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < cols; ++j) {
          input >> mtx[i][j];
          if (input.eof()) {
            std::cerr << "Wrong matrix format\n";
            novikov::remove(mtx, rows);
            return 2;
          }
          if (input.fail()) {
            std::cerr << "Invalid input\n";
            return 2;
          }
          ++count;
        }
      }

      int min = novikov::minSum(mtx, rows, cols);
      novikov::addPeripheral(mtx, rows, cols);

      output << min << " " << rows << " " << cols;
      for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < cols; ++j) {
          output << " " << mtx[i][j];
        }
      }
      novikov::remove(mtx, rows);
    }
  } catch (std::bad_alloc &) {
    std::cerr << "Memory can not be allocated\n";
    return 2;
  }
}
