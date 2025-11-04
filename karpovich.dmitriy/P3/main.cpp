#include <iostream>
#include <fstream>

int* inputFunc(std::istream& input, size_t& rows, size_t& cols);
void outputFunc(std::ostream& output, size_t res1, size_t res2);
size_t localmin(int* arrdyn, size_t rows, size_t cols);

int main(int argc, char ** argv) {
  if (argc > 4) {
    std::cerr << "Too many arguments\n";
    return 1;
  } else if (argc < 4) {
    std::cerr << "Not enough arguments\n";
    return 1;
  }
  if (argv[1][0] == '\0' || argv[1][1] != '\0') {
    std::cerr << "First parameter is not a number\n";
    return 1;
  }
  char c = argv[1][0];
  if (c == '1' || c == '2') {

  } else if (c >= '0' && c <= '9') {
    std::cerr << "First parameter is out of range\n";
    return 1;
  } else {
    std::cerr << "First parameter is not a number\n";
    return 1;
  }
  std::ifstream input(argv[2]);
  size_t rows = 0; size_t cols = 0;
  int* arrdyn = inputFunc(input, rows, cols);
  input.close();
  std::ofstream output(argv[3]);
  size_t res = localmin(arrdyn, rows, cols);
  outputFunc(output, res, 0);
  output.close();
}

int* inputFunc(std::istream& input, size_t& rows, size_t& cols) {
  input >> rows >> cols;
  int* arr = new int[rows * cols];
  for (size_t i = 0; i < rows * cols; ++i) {
    input >> arr[i];
  }
  return arr;
}

void outputFunc(std::ostream& output, size_t res1, size_t res2) {
  output << res1 << '\n';
  output << res2 << '\n';
}

size_t localmin(int* arrdyn, size_t rows, size_t cols) {
  size_t minimum = 0;
  if (rows < 3 || cols < 3) {
    return 0;
  }
  for (size_t i = 1; i < rows - 1; ++i) {
    for (size_t j = 1; j < cols - 1; ++j) {
      size_t k = i * cols + j;
      int now = arrdyn[k];
      bool yeslocalmin = (now < arrdyn[k - 1]) && (now < arrdyn[k + 1]);
      yeslocalmin = yeslocalmin && (now < arrdyn[k - cols]) && (now < arrdyn[k + cols]);
      yeslocalmin = yeslocalmin && (now < arrdyn[k - 1 + cols]);
      yeslocalmin = yeslocalmin && (now < arrdyn[k + 1 + cols]);
      yeslocalmin = yeslocalmin && (now < arrdyn[k + 1 - cols]);
      yeslocalmin = yeslocalmin && (now < arrdyn[k - 1 - cols]);
      if (yeslocalmin) {
        minimum += 1;
      }
    }
  }
  return minimum;
}