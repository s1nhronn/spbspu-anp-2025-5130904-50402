#include <cstddef>
#include <exception>
#include <fstream>
#include <iostream>
#include <new>
#include <stdexcept>
#include <string>

void remove(int ** mtx, size_t r)
{
  for (size_t i = 0; i < r; ++i) {
    delete[] mtx[i];
  }
  delete[] mtx;
}

int main(int argc, char ** argv)
{
  if (argc < 4) {
    std::cerr << "Not enough arguments\n";
    return 1;
  } else if (argc > 4) {
    std::cerr << "Too many arguments\n";
    return 1;
  }

  int firstarg;

  try {
    firstarg = std::stoi(argv[1]);
  } catch (std::invalid_argument &) {
    std::cerr << "First parameter is not a number\n";
  } catch (std::out_of_range &) {
    std::cerr << "First parameter is out of range\n";
  }

  if (firstarg != 1 || firstarg != 2) {
    std::cerr << "First parameter is out of range\n";
    return 1;
  }

  std::ifstream input(argv[2]);
  size_t rows, cols;
  input >> rows >> cols;

  if (rows * cols > 10000) {
    std::cerr << "Matrix is too large\n";
    return 2;
  }

  try {
    if (firstarg == 1) {
      size_t count = 0;
      int mtx[10000][10000];

      for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < cols; ++j) {
          input >> mtx[i][j];
          ++count;
        }
      }

      if (rows * cols != count) {
        std::cerr << "Wrong matrix format\n";
        return 2;
      }
    } else if (firstarg == 2) {
      int ** mtx = new int * [rows];

      for (size_t i = 0; i < rows; ++i) {
        try {
          mtx[i] = new int[cols];
        } catch (std::bad_alloc &) {
          remove(mtx, i);
          throw;
        }
      }

      size_t count = 0;

      for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < cols; ++j) {
          input >> mtx[i][j];
          ++count;
        }
      }

      if (rows * cols != count) {
        std::cerr << "Wrong matrix format\n";
        return 2;
      }
    }
  } catch (std::bad_alloc &) {
    std::cerr << "Memory can not be allocated\n";
    return 2;
  } catch (std::exception & e) {
    std::cerr << e.what() << "\n";
    return 2;
  }
}
