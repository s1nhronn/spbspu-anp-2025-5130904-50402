#include <iostream>
#include <fstream>

int* input_func(std::istream& input, size_t& rows, size_t& cols);

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
  std::ofstream output(argv[3]);
}

int* input_func(std::istream& input, size_t& rows, size_t& cols) {
  input >> rows >> cols;
  int* arr = new int[rows * cols];
  for (size_t i = 0; i < rows * cols; ++i) {
    input >> arr[i];
  }
  return arr;
}