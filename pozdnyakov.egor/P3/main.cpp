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
  }

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

  Matrix* read_matrix_from_file(const char* filename, bool use_fixed_size) {
    std::ifstream file(filename);
    if (!file.is_open()) {
      print_error("Cannot open input file");
      return nullptr;
    }

    int rows, cols;
    if (!(file >> rows >> cols)) {
      print_error("Invalid matrix dimensions in file");
      file.close();
      return nullptr;
    }

    if (use_fixed_size && (rows * cols > MAX_ELEMENTS || rows > MAX_ROWS || cols > MAX_COLS)) {
      print_error("Matrix size exceeds fixed array limits");
      file.close();
      return nullptr;
    }

    Matrix* matrix = create_matrix(rows, cols);
    if (matrix == nullptr) {
      print_error("Memory allocation failed for matrix");
      file.close();
      return nullptr;
    }

    for (int i = 0; i < rows; i++) {
      for (int j = 0; j < cols; j++) {
        if (!(file >> matrix->data[i][j])) {
          print_error("Invalid matrix data in file");
          free_matrix(matrix);
          file.close();
          return nullptr;
        }
      }
    }

    file.close();
    return matrix;
  }

  void write_matrix_to_file(const char* filename, const Matrix* matrix) {
    std::ofstream file(filename);
    if (!file.is_open()) {
      print_error("Cannot open output file");
      return;
    }

    file << matrix->data[0][0];
    file.close();
  }

  int count_non_zero_diagonals(const Matrix* matrix) {
    int count = 0;
    int rows = matrix->rows;
    int cols = matrix->cols;

    for (int k = 1 - rows; k < cols; k++) {
      bool has_zero = false;
      bool diagonal_exists = false;

      for (int i = 0; i < rows; i++) {
        int j = i + k;
        if (j >= 0 && j < cols) {
          diagonal_exists = true;
          if (matrix->data[i][j] == 0) {
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
}

