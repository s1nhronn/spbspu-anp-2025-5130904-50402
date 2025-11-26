#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstring>

namespace pozdnyakov {

  const int MAX_ELEMENTS = 10000;
  const int MAX_ROWS = 100;
  const int MAX_COLS = 100;

  // defining matrix structure
  struct Matrix {
    int** data;
    int rows;
    int cols;
  };

  // create matrix with using of malloc
  Matrix* create_matrix(int rows, int cols) {
    Matrix* matrix = (Matrix*)std::malloc(sizeof(Matrix));
    if (matrix == nullptr) return nullptr;

    matrix->rows = rows;
    matrix->cols = cols;
    matrix->data = (int**)std::malloc(rows * sizeof(int*));

    if (matrix->data == nullptr) {
      std::free(matrix);
      return nullptr;
    }

    for (int i = 0; i < rows; i++) {
      matrix->data[i] = (int*)std::malloc(cols * sizeof(int));
      if (matrix->data[i] == nullptr) {
        for (int j = 0; j < i; j++) {
          std::free(matrix->data[j]);
        }
        std::free(matrix->data);
        std::free(matrix);
        return nullptr;
      }
    }
    return matrix;
  }

  // free matrix memory
  void free_matrix(Matrix* matrix) {
    if (matrix == nullptr) return;
    if (matrix->data != nullptr) {
      for (int i = 0; i < matrix->rows; i++) {
        std::free(matrix->data[i]);
      }
      std::free(matrix->data);
    }
    std::free(matrix);
  }

  // reading file
  Matrix* read_matrix_from_file(const char* filename, bool use_fixed_size) {
    std::ifstream file(filename);
    if (!file.is_open()) {
      return nullptr;
    }

    int rows, cols;
    if (!(file >> rows >> cols)) {
      return nullptr;
    }

    if (use_fixed_size && (rows * cols > MAX_ELEMENTS)) {
      return nullptr;
    }

    Matrix* matrix = create_matrix(rows, cols);
    if (matrix == nullptr) {
      return nullptr;
    }

    for (int i = 0; i < rows; i++) {
      for (int j = 0; j < cols; j++) {
        if (!(file >> matrix->data[i][j])) {
          free_matrix(matrix);
          return nullptr;
        }
      }
    }
    return matrix;
  }

  // task 18
  int process_task_18(const Matrix* input) {
    int count = 0;
    int rows = input->rows;
    int cols = input->cols;

    for (int k = 1 - rows; k < cols; k++) {
      bool has_zero = false;
      bool diagonal_exists = false;

      for (int i = 0; i < rows; i++) {
        int j = i + k;
        if (j >= 0 && j < cols) {
          diagonal_exists = true;
          if (input->data[i][j] == 0) {
            has_zero = true;
            break;
          }
        }
      }

      if (diagonal_exists && !has_zero) {
        count++;
      }
    }

    return count;
  }

  // task 8
  int process_task_8(const Matrix* input) {
    int total = input->rows * input->cols;
    int* elements = (int*)std::malloc(total * sizeof(int));

    if (elements == nullptr) {
      return -1;
    }

    int index = 0;
    for (int i = 0; i < input->rows; i++) {
      for (int j = 0; j < input->cols; j++) {
        elements[index++] = input->data[i][j];
      }
    }

    for (int i = 0; i < total - 1; i++) {
      for (int j = 0; j < total - i - 1; j++) {
        if (elements[j] > elements[j + 1]) {
          int temp = elements[j];
          elements[j] = elements[j + 1];
          elements[j + 1] = temp;
        }
      }
    }

    int sum = 0;
    for (int i = 0; i < total; i++) {
      sum += elements[i];
    }

    std::free(elements);
    return sum;
  }

  // output
  void write_results_to_file(const char* filename, int result18, int result8) {
    std::ofstream file(filename);
    if (file.is_open()) {
      file << result18 << " " << result8;
    }
  }
}

int main() {
  using namespace pozdnyakov;

  int task_num;
  std::string input_file, output_file;

  // reading input
  std::cin >> task_num >> input_file >> output_file;

  // reading and processing matrix
  Matrix* input_matrix = read_matrix_from_file(input_file.c_str(), task_num == 1);
  if (input_matrix == nullptr) {
    return 2;
  }

  // doing task 18 and 8
  int result18 = process_task_18(input_matrix);
  int result8 = process_task_8(input_matrix);

  // writing output in file and in console
  write_results_to_file(output_file.c_str(), result18, result8);
  std::cout << result18 << " " << result8 << std::endl;

  // cleanup
  free_matrix(input_matrix);
  return 0;
}
