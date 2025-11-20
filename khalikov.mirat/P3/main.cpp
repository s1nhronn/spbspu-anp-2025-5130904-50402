#include <iostream>
#include <fstream>

namespace khalikov
{
  bool proverka(const char* str);
  void output_mtx(std::ostream & out, const int * a, size_t n, size_t m);
  size_t input_mtx(std::istream & in, int * a, size_t n, size_t m);
  size_t count_seddle(const int * a, size_t n, size_t m);
  int * spiral(const int * a, int * res, size_t n, size_t m,
  size_t st_row, size_t st_col, size_t end_row, size_t end_col, size_t &c);
  int * spiral(const int * a, int * res, size_t n, size_t m);
}

bool khalikov::proverka(const char* str)
{
  if (str == nullptr)
  {
    return false;
  }
  size_t length = 0;
  while (str[length] != '\0')
  {
    length++;
  }

  if (length > 1)
  {
    return false;
  }

  if (length != 1)
  {
    return false;
  }

  return 1;
}

void khalikov::output_mtx(std::ostream & out, const int * a, size_t n, size_t m)
{
  for (size_t i = 0; i < n; ++i)
  {
    for (size_t j = 0; j < m; ++j)
    {
       out << a[i*m + j] << " ";
    }
    out << "\n";
  }
}

size_t khalikov::input_mtx(std::istream & in, int * a, size_t n, size_t m)
{
  size_t count = 0;
  for (size_t i = 0; i < n*m; ++i)
  {
    if(!(in >> a[i]))
    {
      break;
    }
    count++;
  }
  return count;
}

size_t khalikov::count_seddle(const int * a, size_t n, size_t m)
{
  int min = 0;
  int max = 0;
  size_t count = 0;
  for (size_t i = 0; i < n; ++i)
  {
    for (size_t j = 0; j < m; ++j)
    {
      min =a[i*m];
      max =a[j];
      for (size_t k = 1; k < m; ++k)
      {
        for (size_t w = 1; w < n; ++w)
          {
            if (a[i*m + k] < min)
            {
              min = a[i*m + k];
            }
            if (a[w*m + j] > max)
            {
              max = a[w*m + j];
            }
          }
      }
      if (min == max)
      {
        count+=1;
      }
    }
  }
  return count;
}

int * khalikov::spiral(const int * a, int * res, size_t n, size_t m,
size_t st_row, size_t st_col, size_t end_row, size_t end_col, size_t &c)
{
  if (st_row > end_row || st_col > end_col)
  {
    return res;
  }

  for(size_t i = st_col; i <= end_col; ++i)
  {
    size_t step = st_row * m + i;
    res[step] = a[step] - c;
    ++c;
  }

  for(size_t i = st_row + 1; i <= end_row; ++i)
  {
    size_t step = end_col + i * m;
    res[step] = a[step] - c;
    ++c;
  }

  if (st_row < end_row)
  {
    for(size_t i = end_col - 1; i >= st_col; --i)
    {
      size_t step = end_row * m + i;
      res[step] = a[step] - c;
      ++c;
      if (i == 0)
      {
        break;
      }
    }
  }

  if (st_col < end_col)
  {
    for(size_t i = end_row - 1; i > st_row; --i)
    {
      size_t step = st_col + i * m;
      res[step] = a[step] - c;
      ++c;
      if (i == 0)
      {
        break;
      }
    }
  }
  return khalikov::spiral(a, res, n, m, st_row + 1, st_col + 1, end_row - 1, end_col - 1, c);
}

int * khalikov::spiral(const int * a, int * res, size_t n, size_t m)
{
  if (n == 0 || m == 0)
  {
    return res;
  }
  size_t c = 1;
  return khalikov::spiral(a, res, n, m, 0, 0, n-1, m-1, c);
}
int main(int argc, char ** argv)
{
  if (argc < 4)
  {
    std::cerr << "Not enough arguments" << "\n";
    return 1;
  }
  if (argc > 4)
  {
    std::cerr << "Too many arguments" << "\n";
    return 1;
  }
  if (!khalikov::proverka(argv[1]))
  {
    std::cerr << "First parameter is not a number" << "\n";
    return 1;
  }
  if ((*argv[1] != '1') && (*argv[1] != '2'))
  {
    std::cerr << "First parametr is out of range" << "\n";
    return 1;
  }
  std::ifstream input(argv[2]);
  size_t n = 0;
  size_t m = 0;
  size_t elements = 0;
  std::string extra;
  namespace kh = khalikov;
  input >> n >> m;
  if (input.fail())
  {
    std::cerr << "Input error" << "\n";
    return 2;
  }
  if (*argv[1] == '1')
  {
    int a[10000] = {};
    elements = kh::input_mtx(input, a, n, m);
    if (elements != n*m || input >> extra)
    {
      std::cerr << "Input error" << "\n";
      input.close();
      return 2;
    }
    input.close();
    std::ofstream output(argv[3]);
    kh::output_mtx(output, a, n, m);
    output << "\n";
    output << kh::count_seddle(a, n, m) << "\n";
  }
  if (*argv[1] == '2')
  {
    int * b = nullptr;
    int * res = nullptr;
    try
    {
      b = new int[n*m];
    }
    catch(std::bad_alloc &)
    {
      std::cerr << "bad_alloc";
      delete[] b;
      return 2;
    }
    try
    {
      res = new int[n*m];
    }
    catch(std::bad_alloc &)
    {
      std::cerr << "bad_alloc";
      delete[] res;
      return 2;
    }
    elements = kh::input_mtx(input, b, n, m);
    if (elements != n*m || input >> extra)
    {
      std::cerr << "Input error" << "\n";
      delete[] res;
      delete[] b;
      input.close();
      return 2;
    }
    input.close();
    std::ofstream output(argv[3]);
    kh::output_mtx(output, b, n, m);
    output << "\n";
    res = kh::spiral(b, res, n, m);
    kh::output_mtx(output, res, n, m);
    delete[] res;
    delete[] b;
  }
  return 0;
}
