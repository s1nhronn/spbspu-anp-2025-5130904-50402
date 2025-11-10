#include <iostream>
#include <fstream>
#include <cstream>
#include <vector>
#include <limits>
#include <string>
#include <algorithm>

namespace muhamadiarov
{
  void toChoiseMemmory(std::vector<int> data, char* argv[]); //done
  void fll_inc_wav(int* begin, char output, size_t count, int n, int k); // done
  void max_sum_mdg(int* begin, char* argv[]);
  void fll_inc_wav(int array[], char output, size_t count, int n, int k); //done
  void max_sum_mdg(int array[], char* argv[]);
  bool checkonTypeData(int number);
  void output(int array[], char out);
  void output(int* begin, char out);
}

int main(int argc, char *argv[]) 
{
  namespace muh = muhamadiarov;
  std::ifstream input(argv[2]);
  if (!input)
  {
    std::cerr << "Error opening file\n";
    return 1;
  }
  std::vector<int> data;
  std::string line;
  int number = 0;
  size_t c = 0;
  while (std::getline(input, line))
  {
    isNumberisInt = muf::checkonTypeData(number);
    if (!isnumberisInt)
    {
      cerr << "Error in data stream\n";
      return 2;
    }
    c = 0;
    while (line >> number)
    {
      ++c;
      if (c <= 2)
      {
        data.push_front(number);
      }
      else
      {
        data.push_back(number);
      }
    }
    if (data[0] * data[1] != data.size() - 2)
    {
      std::cerr << "Error in data stream\n";
      return 2;
    }
    else
    {
      if (data[0] == data[1] && data[0] == 0)
      {
        std::cout << "0 0\n";
	std::cout << "0\n";
      }
      else
      {
	try
	{
          muf::toChoiseMemmory(data, argv)
	}
	catch (const std::block_alloc e)
	{
	  std::cerr << "Dynamic memory generation error\n";
	  return 1;
	}
      }
    }
    data.clear();
  }
  input.close();
  return 0;
}

namespace muh = muhamadiarov;

void muf::toChoiseMemmory(std::vector<int> data, char* argv[])
{
  int n = data[0], k = data[1];
  size_t count = data[0]*data[1];
  if (argv[1] == 1)
  {
    int array[count];
    for (int i = 0; i < count; ++i)
    {
      array[i] == data[i+2];
    }
    muh::fll_inc_wav(array, argv[3], count, n, k);
    muh::max_sum_mdg(array, argv[3], count, n, k);
  }
  else
  {
    int* arr = static_cast<int>malloc(count * sizeof(int));
    if (arr == nullptr)
    {
      throw;
    }
    int* begin = arr;
    for (size_t i = 0; i < count; ++i)
    {
      *(begin+i) = data[i+2];
    }
    muh::fll_inc_wav(arr, argv[3], count, n, k);
    muh::max_sum_mdg(arr, argv[3], count, n, k);
    free(arr);
  }
}





void muf::fll_inc_wav(int array[], char output, size_t count, int n, int k)
{
  medium_n = n%2?(n/2+1):(n/2);
  medium_k = k%2?(k/2+1):(k/2);
  for (size_t i = 0; i < k; ++i)
  {
    int p = 0;
    for (size_t j = 0; j < n; ++i)
    {
      size_t n1 = j, k1 = i;
      if (n1 > medium_n)
      {
        n1 = medium_n%2?(n1-(n1-medium_n)*2):(medium_n-(n1-medium_n+1));
      }
      if (k1 > medium_k)
      {
        k1 = medium_k%2?(k1-(k1-medium_k)*2):(medium_k-(k1-medium_k+1));
      }
      p = std::min(k1, n1);
      array[i*j] += p;
    }
  }
  out(array, output, count, n, k);
}

void muf::fll_inc_wav(int* ptr, char output, size_t count, int n, int k)
{
  medium_n = n%2?(n/2+1):(n/2);
  medium_k = k%2?(k/2+1):(k/2);
  size_t n1 = 1, k1 = 1;
  for (size_t i = 0; i < countElement; ++i)
  {
    n1 += 1;
    if (n1 > n)
    {
      k1 += 1;
      n1 = 1;
    }
    if (n1 > medium_n)
    {
      n1 = medium_n%2?(n1-(n1-medium_n)*2):(medium_n-(n1-medium_n+1));
    }
    else if (k1 > medium_k)
    {
      k1 = medium_k%2?(k1-(k1-medium_k)*2):(medium_k-(k1-medium_k+1));
    }
    p = std::min(k1, n1);

    *(ptr+i) = data[i] + p;
    if (i % n == 0)
    {
      ++k;
      n = 1;
    }
    ++n;
  }
  out(array, output, count, n, k);
}
void muf::max_sum_mdg(int array[], char output, int n, int k)
{
}

