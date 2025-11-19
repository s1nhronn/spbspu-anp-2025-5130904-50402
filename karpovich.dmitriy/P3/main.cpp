#include <iostream>
#include <fstream>
#include <cstdlib>

namespace karpovich
{
  const size_t MAX = 10000;

  std::istream& inputFunc(std::istream& input, int* arr, size_t& rows, size_t& cols)
  {
    if (!(input >> rows >> cols)) {
      return input;
    }
    if (rows * cols > MAX) {
      input.setstate(std::ios::failbit);
      return input;
    }
    for (size_t i = 0; i < rows * cols; ++i) {
      if (!(input >> arr[i])) {
        return input;
      }
    }
    return input;
  }

  void outputFunc(std::ostream& output, size_t res1, int* res2, size_t rows, size_t cols)
  {
    output << res1 << '\n';
    output << rows << ' ' << cols;
    for (size_t i = 0; i < rows * cols; ++i) {
      output << ' ' << res2[i];
    }
  }

  size_t locMin(const int* arrdyn, size_t rows, size_t cols)
  {
    if (!arrdyn || rows < 3 || cols < 3) {
      return 0;
    }
    size_t minimum = 0;
    for (size_t i = 1; i < rows - 1; ++i) {
      for (size_t j = 1; j < cols - 1; ++j) {
        size_t k = i * cols + j;
        int now = arrdyn[k];
        bool yeslocMin = (now < arrdyn[k - 1]) && (now < arrdyn[k + 1]);
        yeslocMin = yeslocMin && (now < arrdyn[k - cols]) && (now < arrdyn[k + cols]);
        yeslocMin = yeslocMin && (now < arrdyn[k - 1 + cols]);
        yeslocMin = yeslocMin && (now < arrdyn[k + 1 + cols]);
        yeslocMin = yeslocMin && (now < arrdyn[k + 1 - cols]);
        yeslocMin = yeslocMin && (now < arrdyn[k - 1 - cols]);
        if (yeslocMin) {
          minimum++;
        }
      }
    }
    return minimum;
  }

  void lftTopClk(int* arrdyn, size_t rows, size_t cols)
  {
    if (!arrdyn) {
      return;
    }
    size_t total = rows * cols;
    if (total == 0) {
      return;
    }
    size_t top = 0, bottom = rows - 1;
    size_t left = 0, right = cols - 1;
    int current_value = 1;
    while (top <= bottom && left <= right) {
      for (size_t j = left; j <= right; ++j) {
        arrdyn[top * cols + j] -= current_value++;
      }
      top++;
      for (size_t i = top; i <= bottom; ++i) {
        arrdyn[i * cols + right] -= current_value++;
      }
      right--;
      if (top <= bottom) {
        for (size_t j = right + 1; j > left; --j) {
          arrdyn[bottom * cols + j - 1] -= current_value++;
        }
        bottom--;
      }
      if (left <= right) {
        for (size_t i = bottom + 1; i > top; --i) {
          arrdyn[(i - 1) * cols + left] -= current_value++;
        }
        left++;
      }
    }
  }
}

int main(int argc, char ** argv)
{
  namespace karp = karpovich;
  if (argc != 4) {
    std::cerr << (argc < 4 ? "Not enough arguments\n" : "Too many arguments\n");
    return 1;
  }

  char* endptr = nullptr;
  long num = std::strtol(argv[1], &endptr, 10);
  if (endptr == argv[1] || *endptr != '\0') {
    std::cerr << "First parameter is not a number\n";
    return 1;
  }
  if (num != 1 && num != 2) {
    std::cerr << "First parameter is out of range\n";
    return 1;
  }

  std::ifstream input(argv[2]);
  if (!input.is_open()) {
    std::cerr << "Failed to open input file\n";
    return 2;
  }

  std::ofstream output(argv[3]);
  if (!output.is_open()) {
    std::cerr << "Failed to open output file\n";
    return 2;
  }

  size_t rows = 0;
  size_t cols = 0;
  int* active_arr = nullptr;
  int arr_static[karp::MAX];
  bool is_dynamic = false;

  if (num == 1) {
    active_arr = arr_static;
  } else {
    try {
      active_arr = new int[karp::MAX];
      is_dynamic = true;
    } catch (const std::bad_alloc&) {
      std::cerr << "Memory allocation failed\n";
      return 2;
    }
  }

  karp::inputFunc(input, active_arr, rows, cols);
  if (!input) {
    std::cerr << "Failed to read input data\n";
    if (is_dynamic) {
      delete[] active_arr;
    }
    return 2;
  }

  size_t res1 = karp::locMin(active_arr, rows, cols);
  karp::lftTopClk(active_arr, rows, cols);
  karp::outputFunc(output, res1, active_arr, rows, cols);

  if (is_dynamic) {
    delete[] active_arr;
  }
  return 0;
}
