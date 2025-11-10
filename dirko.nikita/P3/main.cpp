#include <iostream>
#include <fstream>

namespace dirko
{
  void staticInput(std::istream &in, int *arr, size_t r, size_t c)
  {
    for (size_t i = 0; i < r * c; ++i)
    {
      in >> arr[i];
      if (in.eof())
      {
        throw std::logic_error("Not enougth data\n");
      }
      else if (in.fail())
      {
        throw std::logic_error("Cant read\n");
      }
    }
  }
  int *dinamicInput(std::istream &in, size_t r, size_t c)
  {
    try
    {
      int *arr = new int[r * c];
      for (size_t i = 0; i < r * c; ++i)
      {
        in >> arr[i];
        if (in.fail())
        {
          throw std::logic_error("Cant read");
        }
      }
      return arr;
    }
    catch (std::bad_alloc &e)
    {
      throw;
    }
  }
  int *var1(int *arr, size_t r, size_t c);
  bool var2(const int *arr, size_t r, size_t c)
  {
    size_t min = (r > c) ? c : r;
    if (min < 2)
    {
      return false;
    }
    size_t line = 0;
    for (size_t i = 0; i < min; ++i)
    {
      for (size_t j = line + i + 1; j < line + min; j++)
      {
        if (arr[i + j] != 0)
        {
          return false;
        }
      }
      line += min - 1;
    }
    return true;
  }
  std::ostream &output(std::ostream &out, const int *arr, size_t r, size_t c)
  {
    out << r << ' ' << c << ' ';
    for (size_t i = 0; i < r * c - 1; ++i)
    {
      out << arr[i] << ' ';
    }
    return out << arr[r * c - 1];
  }
}

int main(int argc, char const **argv)
{
  int mode = 0;
  if (argc < 4)
  {
    std::cerr << "Not enough arguments\n";
    return 1;
  }
  if (argc > 4)
  {
    std::cerr << "Too many arguments\n";
    return 1;
  }
  try
  {
    mode = std::stoi(argv[1]);
  }
  catch (std::out_of_range &e)
  {
    std::cerr << "First parameter is not a number\n";
    return 1;
  }
  if (mode < 1 || mode > 2)
  {
    std::cerr << "First parameter is out of range\n";
    return 1;
  }
  std::ifstream fin(argv[2]);
  if (!fin.is_open())
  {
    std::cerr << "Cant open input file\n";
    return 2;
  }
  size_t rows = 0, cols = 0;
  fin >> rows >> cols;
  if (fin.eof())
  {
    std::cerr << "Not enougth data\n";
  }
  else if (fin.fail())
  {
    std::cerr << "Cant read\n";
    return 2;
  }

  if (mode == 1)
  {
    int arr[1000]{};
    int *res1 = nullptr;
    bool res2 = false;
    try
    {
      dirko::staticInput(fin, arr, rows, cols);
      fin.close();
      res1 = dirko::var1(arr, rows, cols);
      res2 = dirko::var2(arr, rows, cols);
      std::ofstream fout(argv[3]);
      dirko::output(fout, res1, rows, cols) << '\n';
      fout << std::boolalpha << res2 << '\n';
      delete[] res1;
    }
    catch (std::logic_error &e)
    {
      std::cerr << e.what();
      delete[] res1;
      return 2;
    }
  }
  else
  {
    int *arr = nullptr;
    int *res1 = nullptr;
    bool res2 = false;
    try
    {
      arr = dirko::dinamicInput(fin, rows, cols);
      fin.close();
    }
    catch (std::logic_error &e)
    {
      std::cerr << e.what();
      return 2;
    }
    catch (std::bad_alloc &e)
    {
      std::cerr << "Cant alloc\n";
      return 3;
    }
    res1 = dirko::var1(arr, rows, cols);
    res2 = dirko::var2(arr, rows, cols);
    std::ofstream fout(argv[3]);
    dirko::output(fout, res1, rows, cols) << '\n';
    fout << std::boolalpha << res2 << '\n';
    delete[] arr;
    delete[] res1;
  }
}
