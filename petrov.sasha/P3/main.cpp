#include <iostream>
#include <fstream>
namespace petrov
{
  void rm(int** mtx, size_t rows)
  {
    for (size_t i = 0; i < rows; i++){
      delete[] a[i];
    }
    delete[] a;
  }

  void stat(std::ifstream& out, int** a, size_t rows, size_t cols)
  {
    
  }

  void dyn(std::ifstream& out, size_t rows, size_t cols)
  {
    int** a = nullptr;
     size_t qnt_numb = 0;
    try {
      a = new int*[rows];
      for (size_t i = 0; i < rows; ++i)
      {
        a[i] = new int[cols];
      }
    } catch (const std::bad_alloc& e) {
      rm(a, rows);
      throw;
    }
    for (size_t i = 0; i < rows; ++i)
    {
      for (size_t j = 0; j < cols; ++j)
      {
        qnt_numb++;
        out >> a[i][j];
      }
    }
    if (qnt_numb != rows*cols)
    {
      throw std::logic_error("Too many/few arguments for array\n");
    }
  }

  int  LFT_BOT_CNT(int** a, size_t r, size_t c)
  {
    size_t counter = 0;
    size_t up = 0, down = --r, left = 0, right = --c;
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
    return a;
  }
}

int main(int argc, char const** argv)
{
  if (argc < 4)
  {
    std::cerr << "Not enough arguments\n";
  } else if ( argc > 4)
  {
    std::cerr << "Too many arguments\n";
  }
  std::ifstream input(argv[2]);
  int cols = 0, rows = 0;
  try{
    input >> rows >> cols;
  } catch (...) {
    std::cerr << "Invalid matrix data\n";
    return 2;
  }
  std::ofstream output(argv[3]);
  if (!(input && output))
  {
    std::cerr << "Error in file\n";
    return 2;
  }
  if (argv[2] == '1')
  {
    const int max_size_arr = 10000;
    long long arr[max_size_arr];
    
  } else if ( argv[2] == '2')
  {
    
    petrov::rm(a, rows);
  } else
  {
    int error_variant = 0;
    try {
      error_variant = std::stoi(argv[1]);
    } catch(const std::invalid_argument& e) {
      std::cerr << "First parameter is not a number\n";
      return 1;
    }
    std::cerr << "First parameter is out of range\n";
    return 1;
  }
  return 0;
}
