#include <iostream>
#include <fstream>

namespace petrov
{
  void LFT_BOT_CNT(int** a, size_t r, size_t c);
  void FLL_INC_WAV(int** a, size_t rows, size_t cols);
  void rm(int** mtx, size_t rows);

  void rm(int** mtx, size_t rows)
  {
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
    int arr[100][100];
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
    LFT_BOT_CNT(arr_ptr,rows,cols);
    for (size_t i = 0; i < rows; i++) {
      for (size_t j = 0; j < cols; j++) {
        out << " " << arr[i][j];
      }
    }
    out << "\n";
  }

  void dyn(std::ifstream& in, std::ofstream& out, size_t rows, size_t cols)
  {
    int** a = nullptr;
    size_t qnt_numb = 0;
    a = new int*[rows];
    for (size_t i = 0; i < rows; ++i)
    {
      a[i] = new int[cols];
    }
    for (size_t i = 0; i < rows; ++i)
    {
      for (size_t j = 0; j < cols; ++j)
      {
        qnt_numb++;
        if (!(in >> a[i][j]))
        {
          rm(a,rows);
          std::cerr << "Invalid matrix numbers\n";
          return;
        }
      }
    }
    if (qnt_numb != rows*cols)
    {
      rm(a,rows);
      std::cerr << "Too many/few arguments for array\n";
      return;
    }
    FLL_INC_WAV(a, rows, cols);
    for (size_t i = 0; i < rows; i++) {
      for (size_t j = 0; j < cols; j++) {
        out << " " << a[i][j];
      }
    }
    out << "\n";
    rm(a,rows);
  }

  void LFT_BOT_CNT(int** a, size_t r, size_t c)
  {
    size_t counter = 0;
    size_t up = 0, down = r-1, left = 0, right = c-1;
    while (up <= down && left <= right)
    {
      for (size_t i = left; i < right; ++i)
      {
        counter++;
        a[down][i]+=counter;
      }
      down--;
      if (left<=right){
        for (size_t i = down; i >= up; --i)
        {
          counter++;
          a[i][right]+=counter;
        }
        right--;
      }
      if (up<=down)
      {
        for (size_t i = right; i>=left; --i)
        {
          counter++;
          a[up][i]+=counter;
        }
        up++;
      }
      for (size_t i = up; i <= down; ++i)
      {
        counter++;
        a[i][left]+=counter;
      }
      left++;
    }
  }

  void FLL_INC_WAV(int** a, size_t rows, size_t cols)
  {
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
  const char* variant = argv[1];
  if (variant[0] != '1' || variant[0] != '2')
  {
    std::cerr << "First parameter is not a number";
    return 1;
  }
  std::ifstream input(argv[2]);
  int cols = 0, rows = 0;
  if (!(input >> rows >> cols)) {
    std::cerr << "Invalid matrix data\n";
    return 2;
  }
  std::ofstream output(argv[3]);
  if (!input || !output) {
    std::cerr << "Error in reading file\n";
    return 2;
  }
  output << rows << " " << cols;
  if (variant[0] == '1') {
    petrov::stat(input, output, rows, cols);
  } else {
    petrov::dyn(input, output, rows, cols);
  }
  return 0;
}
