#include <iostream>
#include <fstream>
#include <cstream>
#include <vector>
#include <limits>
#include <string>
#include <algorithm>

void fll_inc_wav(std::vector<int> data, char* argv[]);
void max_sum_mdg(std::vector<int> data, char* argv[]);
bool checkonTypeData(int number);

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
          muf::fll_inc_wav(data, argv);
          muf::max_sum_mdg(data, argv);
	}
	catch (...)
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
namespace muhamadiarov
{
  void fll_inc_wav(std::vector<int> data, char* argv[])
  {
    int n = data[0], k = data[1];
    n = std::max(n, k);
    k = std::min(n, k);
    size_t countElement = data[1] * data[0];
    medium_n = n%2?(n/2+1):(n/2);
    medium_k = k%2?(k/2+1):(k/2);
    if (argv[1] == 1)
    {
      int array[countElement];
      for (size_t i = 2; i < countElement; ++i)
      {
        array[i - 2] = data[i];
      }
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
          else if (k1 > medium_k)
	  {
	    k1 = medium_k%2?(k1-(k1-medium_k)*2):(medium_k-(k1-medium_k+1));
	  }	  	
	  p = std::min(k1, n1);
	  array[i*j] += p;
	}
      }
    std::cout << n << " " << k << " ";
    for (size_t i = 0; i < countElement;++i)
    {
      std::cout << array[i] << ' ';
    }
    std::cout << "\n";
    }
    else
    {
      int* array = static_cast<int>malloc(countElement * sizeof(int));
      if (array == nullptr)
      {
        throw;
      }
      int* ptr = array;
      size_t n = 1, k = 1;
      for (size_t i = 0; i < countElement; ++i)
      {
	size_t n1 = n, k1 = k;

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
      for (size_t i = 0; i < countElement; ++i)
      {
        std::cout << array[i] << " ";
      }
      std::cout << "\n";
      free(array); 
    }



  }
}
