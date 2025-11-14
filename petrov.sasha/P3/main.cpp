#include <iostream>
#include <fstream>

namespace petrov
{
  void LFT_BOT_CNT(int** a, size_t r, size_t c);
  void FLL_INC_WAV(int** a, size_t rows, size_t cols);
  void rm(int** mtx, size_t rows);

  void rm(int** mtx, size_t rows)
  {
    if (!mtx) return;
    for (size_t i = 0; i < rows; i++){
      delete[] mtx[i];
    }
    delete[] mtx;
  }

  void stat(std::ifstream& in, std::ofstream& out, size_t rows, size_t cols)
  {
    const size_t max_size_arr = 10000;
    if (rows * cols > max_size_arr) {
      std::cerr << "Too large for array\n";
      return;
    }
    if (rows == 0 || cols == 0) {
      return;
    }
    int arr[100][100] = {0};
    for(size_t i = 0; i < rows; ++i)
    {
      for(size_t j = 0; j < cols; ++j)
      {
        if (!(in >> arr[i][j]))
        {
          std::cerr << "Invalid matrix data\n";
          return;
        }
      }
    }
    int* arr_ptr[100];
    for (size_t i = 0; i < rows; ++i)
    {
      arr_ptr[i] = arr[i];
    }
    LFT_BOT_CNT(arr_ptr, rows, cols);
    for (size_t i = 0; i < rows; i++) {
      for (size_t j = 0; j < cols; j++) {
        out << " " << arr[i][j];
      }
    }
  }

  void dyn(std::ifstream& in, std::ofstream& out, size_t rows, size_t cols)
  {
    if (rows == 0 || cols == 0) {
      return;
    }
    int** a = nullptr;
    size_t qnt_numb = 0;
    try {
      a = new int*[rows];
      for (size_t i = 0; i < rows; ++i) {
        a[i] = new int[cols]();
      }
    } catch (...) {
      rm(a, rows);
      std::cerr << "Memory allocation failed\n";
      return;
    }
    for (size_t i = 0; i < rows; ++i)
    {
      for (size_t j = 0; j < cols; ++j)
      {
        if (!(in >> a[i][j]))
        {
          rm(a, rows);
          std::cerr << "Invalid matrix numbers\n";
          return;
        }
        qnt_numb++;
      }
    }
    int temp;
    if (in >> temp)
    {
      rm(a, rows);
      std::cerr << "Too many arguments for array\n";
      return;
    }
    FLL_INC_WAV(a, rows, cols);
    for (size_t i = 0; i < rows; i++) {
      for (size_t j = 0; j < cols; j++) {
        out << " " << a[i][j];
      }
    }
    rm(a, rows);
  }

  void LFT_BOT_CNT(int** a, size_t r, size_t c)
  {
    if (r == 0 || c == 0)
    {
      return;
    }
    size_t counter = 1;
    size_t up = 0, down = r-1, left = 0, right = c-1;
    while (up <= down && left <= right)
    {
      if (down >= r || left >= c)
      {
        break;
      }
      for (size_t i = left; i < right && i < c; ++i)
      {
        if (down < r) {
          counter++;
          a[down][i] += counter;
        }
      }
      if (down == 0) break;
      down--;
      if (left <= right && right < c) {
        for (size_t i = down; i >= up && i < r; --i)
        {
          if (right < c) {
            counter++;
            a[i][right] += counter;
          }
          if (i == 0) break;
        }
        right--;
      }
      if (up <= down && up < r) {
        for (size_t i = right; i >= left && i < c; --i)
        {
          if (up < r) {
            counter++;
            a[up][i] += counter;
          }
          if (i == 0) break;
        }
        up++;
      }
      if (left < c) {
        for (size_t i = up; i <= down && i < r; ++i)
        {
          if (left < c) {
            counter++;
            a[i][left] += counter;
          }
        }
        left++;
      }
    }
  }

  void FLL_INC_WAV(int** a, size_t rows, size_t cols)
  {
    if (rows == 0 || cols == 0)
    {
      return;
    }
    size_t min_data = (rows < cols) ? rows : cols;
    size_t borders = (min_data + 1) / 2;
    for (size_t border =  0; border < borders; ++border)
    {
      int counter = border + 1;
      for (size_t j = border; j < cols - border; ++j)
      {
        a[border][j] += counter;
      }
      for (size_t i = border + 1; i < rows - border; ++i)
      {
        a[i][cols - 1 - border] += counter;
      }
      if (border < rows - 1 - border)
      {
        for (size_t j = cols - 2 - border; j >= border; j--)
        {
          a[rows - 1 - border][j] += counter;
          if (j == 0) {
            break;
          }
        }
      }
      if (border < cols - 1 - border)
      {
        for (size_t i = rows - 2 - border; i > border; i--)
        {
          a[i][border] += counter;
          if (i == 0) {
            break;
          }
        }
      }
    }
  }
}

int main(int argc, char const** argv)
{
  if (argc != 4) {
    std::cerr << (argc < 4 ? "Not enough arguments\n" : "Too many arguments\n");
    return 1;
  }
  int mode = 0;
  try {
    mode = std::stoi(argv[1]);
  }
  catch (...) {
    std::cerr << "First parameter is not a number\n";
    return 1;
  }
  if (mode != 1 && mode != 2) {
    std::cerr << "First parameter is out of range\n";
    return 1;
  }
  std::ifstream input(argv[2]);
  if (!input.is_open()) {
    std::cerr << "Cannot open input file\n";
    return 2;
  }
  int rows = 0, cols = 0;
  if (!(input >> rows >> cols)) {
    std::cerr << "Invalid matrix data\n";
    return 2;
  }
  std::ofstream output(argv[3]);
  if (!output.is_open()) {
    std::cerr << "Cannot open output file\n";
    return 2;
  }
  output << rows << " " << cols;
  bool errors = false;
  if (mode == 1) {
    petrov::stat(input, output, rows, cols);
    if (input.fail() && !input.eof()) {
      errors = true;
    }
  } else {
    petrov::dyn(input, output, rows, cols);
    if (input.fail() && !input.eof()) {
      errors = true;
    }
  }
  input.close();
  if (errors) {
    return 2;
  }
  return 0;
}
