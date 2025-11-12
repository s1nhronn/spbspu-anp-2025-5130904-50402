#include <iostream>
#include <fstream>
/*
Принимаю три значения num input output
Вход - двумерный целочисленный массив, первые два - строки столбцы, потом эл-ты
output - выход, куда надо вывести массив с результатом
*/
namespace petrov
{
  void rm(int** a, size_t rows)
  {
  
  }
  size_t LFT_BOT_CNT(size_t** a, size_t r, size_t c)
  {
    size_t counter = 0;
    size_t up = 0, down = --r, left = 0, right = --c;
    while(up <= down && left <= right)
    {
      for(size_t i = left; i < right; ++i)
      {
        counter++;
        a[down][i]+=counter;
      }
      down--;
      if(left<=right){
        for(size_t i = down; i >= up; --i)
        {
          counter++;
          a[i][right]+=counter;
        }
        right--;
      }
      if(up<=down)
      {
        for(size_t i = right; i>=left; --i)
        {
          counter++;
          a[up][i]+=counter;
        }
        up++;
      }
      for(size_t i = up; i <= down; ++i)
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

