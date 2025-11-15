#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstring>

namespace pozdnyakov {

  const int MAX_ELEMENTS = 10000;
  const int MAX_ROWS = 100;
  const int MAX_COLS = 100;

  struct Matrix {
    int** data;
    int rows;
    int cols;
  };

  Matrix* create_matrix(int rows, int cols);
  void free_matrix(Matrix* matrix);
  Matrix* read_matrix_from_file(const char* filename, bool use_fixed_size);
  void write_matrix_to_file(const char* filename, const Matrix* matrix);

  void process_task_18(const Matrix* input, Matrix* output);
  void process_task_8(const Matrix* input, Matrix* output);

  bool is_valid_arguments(int argc, char* argv[]);
  void print_error(const char* message);
  int count_non_zero_diagonals(const Matrix* matrix);

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

  void free_matrix(Matrix* matrix) {
    if (matrix == nullptr) return;

    if (matrix->data != nullptr) {
      for (int i = 0; i < matrix->rows; i++) {
        if (matrix->data[i] != nullptr) {
          std::free(matrix->data[i]);
        }
      }
      std::free(matrix->data);
    }
    std::free(matrix);
  }
}

