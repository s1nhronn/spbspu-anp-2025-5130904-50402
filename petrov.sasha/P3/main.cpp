#include <iostream>
#include <fstream>
namespace petrov
{
  void rm(int** mtx, size_t rows)
  {
    for (size_t i = 0; i < rows, i++){
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
    if (qnt_numb != rows*cols))
    {
      throw std::lenght_error("Too many/few arguments for array\n");
  }

  size_t LFT_BOT_CNT(int** a, size_t r, size_t c)
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

int main(int argc, char const* argv[])
{

}

