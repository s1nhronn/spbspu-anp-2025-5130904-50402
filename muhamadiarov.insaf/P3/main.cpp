#include <iostream>
#include <fstream>
#include <vector>
#include <limits>
#include <string>
#include <algorithm>
#include <typeinfo>
#include <cstddef>
#include <cstdlib>

namespace muhamadiarov
{
  struct matric_info
  {
    int* start;
    int rows;
    int colons;
  };

  int max_int(); 
  int min_int();
 
  int* fll_inc_wav(matric_info matrix); 

  void out(matric_info matrix, const char* output, int* res1, long long int res2); 

  long long toFindMaxRight(int* ptr, int order); 
  long long toFindMaxinLeft(int* ptr, int order); 
  long long max_sum_mdg(matric_info matrix, int order); 

  bool tocheckparam(int argc, char* argv[]); 
  void tocoutargv(int argc, char * argv[]);
}

bool isOutfileOpened = true;

int main(int argc, char *argv[]) 
{
  namespace muh = muhamadiarov;
  bool checkparam = muh::tocheckparam(argc, argv); //проверка параметров main
  if (!checkparam)
  {
    return 1;
  }
  std::ifstream input(argv[2]); // открытие файла
  if (!input) // открылся ли файл?
  {
    std::cerr << "Error is openning file\n";
    return 2;
  }
 
  if (input.eof())
  {
    std::cerr << "The file is empty\n";
    return 2;
  }
  size_t count = 0;
  int number = 0;
  while (input >> number)
  {
    ++count;
  }

  if (count == 0)
  {
    std::cerr << "The file is empty\n";
    return 2;
  }
  else if (count < 2)
  {
    std::cerr << "Not enough vaules\n";
    return 2;
  }

  input.clear();
  input.seekg(0);

  if (argv[1][0] == '1')
  {
    int arr[count];
    int* ptr = &arr[0];
  }
  else if (argv[1][0] == '2')
  {
    int* ptr = static_cast<int*>(malloc(count * sizeof(int)));
    if (ptr == nullptr)
    {
      std::cerr << "Failed to allocate memory\n";
      return 1;
    }
  }
  
  int number = 0;
  size_t k = 0;
  size_t k1 = 0;
  int r = 0, c = 0;
  while (input >> number)
  {
    bool ch1 =  typeid(number).name() != typeid(int).name();
    bool ch2 = ch1 || number < muh::min_int || number > muh::max_int;
    if (ch2) // проверка number
    {
      std::cerr << "Incorrect type for number\n";
      if (argv[1][0] == '2')
      {
        free(ptr);
      }
      return 2;	
    }


    if (k1 == 0)
    {
      r = number;
    }
    else if (k1 == 1)
    {
      c = number;
    }
    else if (input.peek() == '\n')
    {
      if (k1 - 1 != r * c)
      {
        std::cerr << "Wrong size matric\n";
	if (argv[1][0] == '2')
	{
	  free(ptr);
	}
	return 2;
      }
    }


    *(ptr + k) = number;
    ++k;
  }
  input.close();
  // c - count elements in file
  // r  - rows
  // c - colons

  int* result_1 = nullptr;
  long long int result_2 = 0;
  muh::matric_info matrix;
  for (size_t i = 0; i < c; ++i)
  {
    r = *(ptr + i);
    c = *(ptr + i + 1);
    if (i + 2 < c)
    {
      matrix{ptr + i + 2, r, c};
    }
    else if (r == 0 && c == 0)
    {
      matrix{ptr + i, 0, 0};
      muh::out(matrix, argv[3], result_1, result_2);
    } 
    result_1 = muh::fll_inc_wav(matrix);
    int order = std::min(r, c);
    result_2 = muh::max_sum_mdg(matrix, order); 
    muh::out(matrix, argv[3], result_1, result_2);
    if (isOutfileOpened = false)
    {
      std::cerr << "Error in openning file\n";
      if (argv[1][0] == '2')
      {
        free(ptr);
      }
      return 1;
    }
    i += r * c + 2; 
  }
  if (argv[1][0] == '2')
  {
    free(ptr);
  }
  return 0;
}

int* muhamadiarov::fll_inc_wav(muhamadiarov::matric_info matrix)
{
  namespace muh = muhamadiarov;
  int n = matrix.rows;
  int k = matrix.colons;
  int medium_n = n%2?(n/2+1):(n/2);
  int medium_k = k%2?(k/2+1):(k/2);
  for (size_t i = 0; i < k; ++i)
  {
    int p = 0;
    for (size_t j = 0; j < n; ++j)
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
      *(ptr + j*n + i) += p;
    }
  }
  return ptr;
}


long long muhamadiarov::max_sum_mdg(muhamadiarov::matric_info matrix, int order)
{
  namespace muh = muhamadiarov;
  long long max_result = 0;
  long long par_branch_right = muh::toFindMaxinRight(matrix.ptr, order);
  long long par_branch_left = muh::toFindMaxinLeft(matrix.ptr, order);
  max_result = std::max(par_branch_right, par_branch_left);
  return max_result;
}

long long muhamadiarov::toFindMaxinLeft(int* ptr, int order)
{
  long long max_r = 0;
  long long result = 0;
  int n = order, k = order;
  while (n > 0 && k > 0)
  {
    order -= 1;
    for (int i = n, int j = 1; j <= k && i > 0; --i, ++j)
    {
      result += *(ptr + i*order + j);
    }
    max_r = std::max(result, max_r);
    result = 0;
  }
  return max_r;
}

long long muhamadiarov::toFindMaxRight(int* ptr, int order)
{
  long long int max_r = 0;
  long long int result = 0;
  int n = order, k = order;
  int k1 = 2;
  while (k >= k1)
  {
    k1 += 1;
    for (int i = n, int j = 2; j <= k1 && i > 1; --i, ++j)
    {
      result += *(ptr + i*order + j);
    }
    max_r = std::max(result, max_r);
    result = 0;
  }
  return max_r;
}

void muhamadiarov::out(muhamadiarov::matric_info matrix,char output, int* res1, long long int res2)
{
  int n = matrix.rows;
  int k = matrix.colons; 
  size_t count = n * k;
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
	n = std::min(n, k);
        for (size_t i; i < n*n; ++i)
        {
          outfile << *(res1 + i) << " ";
        }
        outfile << "\n";
      }
      else
      {
        outfile << res2 << "\n";
      }
    }
    outfile.close();
  }
}


void muhamadiarov::tocoutargv(int argc, char* argv[])
{
  for (size_t i = 0; i < argc; ++i)
  {
    std::cout << argv[i] << " ";
  }
}

bool muhamadiarov::tocheckparam(int argc, char* argv[])
{
  namespace muh = muhamadiarov;
  bool flag = true;
  if (argc < 4)
  {
    muh::tocoutargv(argc, argv);
    std::cerr << "//Not enough arguments\n";
    flag = false;
  }
  if (argc > 4)
  { 
    muh::tocoutargv(argc, argv);
    std::cerr << "//Too many arguments\n";
    flag = false;
  } 
  if (argv[1][0] < '0' || argv[1][0] > '9')
  {
    muh::tocoutargv(argc, argv);
    std::cerr << "//First parameter is not a number\n";
    flag = false;
  }
  else if (argv[1][0] > 2)
  {
    muh::tocoutargv(argc, argv);
    std::cerr << "//First parameter is out of range\n";
    flag = false;
  }
  if (!flag)
  {
    return false;
  }
  return true;
}


int muhamadiarov::max_int()
{
  using namespace std;
  return numeric_limits<int>::max();
}

int muhamadiarov::min_int()
{
  using namespace std;
  return numeric_limits<int>::min();
}

