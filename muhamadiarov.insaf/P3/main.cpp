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
  void fll_inc_wav(int* ptr, char output, size_t count, int n, int k); // done
  void out(int* ptr,char output, size_t count, int n, int k, int* res1, long long res2); //done
  long long muf::toFindMaxRight(int* ptr, int order); //done
  long long muh::toFindMaxinLeft(int* ptr, int order); //done
  long long muf::max_sum_mdg(int* ptr, char output, int order); //done
}

bool isOutfileOpened = true;

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
    isNumberisInt = muh::checkonTypeData(number);
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
  if (!isOutfileOpened)
  {
    std::cerr << "Error openning file\n";
    return 1; 
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
    int* begin = array;
    long long resultFirstTask = 0ll;
    order = std::min(n, k);
    int* resultSecondTask[order];
    resultFirstTask = muh::fll_inc_wav(begin, argv[3], count, n, k);
    resultSecondTask = muh::max_sum_mdg(begin, argv[3], count, order);
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
    long long resultFirstTask = 0ll;
    if (n != k)
    {
      order = std::min(n, k);
      int* resultSecondTask[] = static_cast<int>malloc(order * sizeof(int));
      begin = resultSecondTask;
      if (resultSecondTask == nullptr)
      {
        free(arr);
        throw;
      }
      for (size_t i = 1; i <= order; ++1)
      {
        *(begin + i*i) = arr[i*i];
      }
    }
    resultFirstTask = muh::fll_inc_wav(begin, argv[3], count, n, k);
    resultSecondTask = muh::max_sum_mdg(begin, argv[3], count, order);
    free(arr);
    free(resultFirstTask);
  }
  muf::out(begin, count, n, k, resultFirstTask, resultSecondTask);
}

void muf::fll_inc_wav(int* ptr, char output, size_t count, int n, int k)
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
      *(ptr + i*j) += p;
    }
  }
  muf::out(ptr, output, count, n, k);
}


long long muf::max_sum_mdg(int* ptr, char output, int order)
{
  long long max_result = 0ll;
  long long par_branch_right = muh::toFindMaxinRight(ptr, order);
  long long par_branch_left = muh::toFindMaxinLeft(ptr, order);
  max_result = std::max(par_branch_right, par_branch_left);
  return max_result;
}

long long muh::toFindMaxinLeft(int* ptr, int order)
{
  long long max_r = 0ll;
  long long result = 0ll;
  int n = order, k = order;
  while (n > 0 && k > 0)
  {
    order -= 1;
    for (int i = n, int j = 1; j <= k && i > 0; --i, ++j)
    {
      result += *(ptr + i*j);
    }
    max_r = std::max(result, max_r);
    result = 0;
  }
  return max_r;
}

long long muf::toFindMaxRight(int* ptr, int order)
{
  long long max_r = 0ll;
  long long result = 0ll;
  int n = order, k = order;
  int k1 = 2;
  while (k >= k1)
  {
    k1 += 1;
    for (int i = n, int j = 2; j <= k1 && i > 1; --i, ++j)
    {
      result += *(ptr + i*j);
    }
    max_r = std::max(result, max_r);
    result = 0;
  }
  return max_r;
}

void out(int* ptr,char output, size_t count, int n, int k, int* res1, long long res2)
{
  std::ofstream outfile(output);
  if (!outfile)
  {
    isOutfileOpened = false;
  }
  else
  {
    for (size_t j = 0; j < 2; ++j)
    {
      outfile << n << " " << k << " ";
      for (size_t i = 0; i < count; ++i)
      {
        outfile << *(ptr + i) << " ";
      }
      outfile << "//Expect output (return code 0): ";
      if (j == 0)
      {
        for (size_t i; i < n*n; ++i)
        {
          output << *(res1 + i) << " ";
        }
        outfile << "\n";
      }
      else
      {
        output << res2 << "\n";
      }
    }
    outfile.close();
  }
}
