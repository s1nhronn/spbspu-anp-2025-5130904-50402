#include <fstream>
#include <iostream>
#include <cstdlib>

namespace samarin {
  bool checkMax(int * a, int i, int j, int n);
  bool isLowerTriangular(const int * a, int size, int n);
  size_t localMax(int * a, size_t n, size_t m);
  void printMatrix(int * a, int m, int n, char * file);
}

int main(int argc, char ** argv)
{
  if (argc != 4) {
    return 1;
  }

  char memory_type = argv[1][0];
  if ((memory_type != '1' && memory_type != '2') || argv[1][1] != '\0') {
    std::cerr << "Unexpected first parameter. \n";
    return 1;
  }

  std::ifstream input(argv[2]);
  if (!input) {
    std::cerr << "Cannot open input file \n";
    return 2;
  }

  size_t m = 0, n = 0;
  input >> m >> n;

  if (input.fail() || m <= 0 || n <= 0) {
    std::cerr << "Invalid matrix dimensions \n";
    return 2;
  }

  const size_t ARRAY_SIZE = 10000;
  int* arr = nullptr;
  int static_array[ARRAY_SIZE] = {};

  if (memory_type == '2') {
    arr = reinterpret_cast<int*>(malloc(sizeof(int) * m * n));
    if (arr == nullptr) {
      std::cerr << "Memory allocation failed \n";
      return 2;
    }
  } else {
    arr = static_array;
  }

  for (int i = 0; i < m * n; ++i) {
    input >> arr[i];
    if (input.fail()) {
      std::cerr << "Invalid matrix element \n";
      if (memory_type == '2') {
        free(arr);
      }
      return 2;
    }
  }
  input.close();

  size_t counter = samarin::localMax(arr, n, m);

  int size = std::min(m, n);
  bool is_lower_left = samarin::isLowerTriangular(arr, size, n);

  std::ofstream output(argv[3]);
  if (!output) {
    std::cerr << "Cannot open output file \n";
    if (memory_type == '2') {
      free(arr);
    }
    return 2;
  }

  output << "Локальных максимумов: " << counter << "\n";

  if (is_lower_left) {
    output << "Матрица нижняя треугольная\n";
  } else {
    output << "Матрица не нижняя треугольная\n";
  }

  output.close();
  char * file = argv[3];

  if (memory_type == '2') {

    free(arr);
  }

  return 0;
}

bool samarin::checkMax(int * a, int i, int j, int n)
{
  int * upper_left_section = a + j-1 + ((i-1)*n);
  int * current = a + j + (i*n);
  std::cout << current[0] << "\n" << upper_left_section[0];
  for (size_t di = 0; di <= 2; ++di) {
    for (size_t dj = 0; dj <= 2; ++dj) {
      if (di == 1 && dj == 1) {
        continue;
      }

      if (upper_left_section[dj + di*n] >= current[0]) {
        return false;
      }
    }
  }
  return true;
}

bool samarin::isLowerTriangular(const int* a, int size, int n)
{
  for (int i = 0; i < size; ++i) {
    for (int j = i + 1; j < size; ++j) {
      if (a[j + i * n] != 0) {
        return false;
      }
    }
  }
  return true;
}

size_t samarin::localMax(int * a, size_t n, size_t m)
{
  std::cout << " вызвана функция \n";
  size_t counter = 0;
  for (size_t i = 0; i < m; ++i) {
    for (size_t j = 0; j < n; ++j) {
      if (i != 0 && j !=0 && i != m-1 && j != n-1) {
        std::cout << a[j + i * n] << "\n";
        if (samarin::checkMax(a, i, j, n)) {
          counter++;
        }
      }
    }
  }
  return counter;
}

void samarin::printMatrix(int * a, int m, int n, char * file) {
  std::ofstream output(file);
  for (int i = 0; i < m; ++i) {
    for (int j = 0; j < n; ++j) {
      output << a[j + i * n] << " ";
    }
    output << "\n";
  }
  output.close();
}
