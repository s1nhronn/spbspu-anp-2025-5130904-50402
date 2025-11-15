#include <iostream>
#include <fstream>

void output_mtx(std::ostream & out, const int * a, size_t n, size_t m)
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

void input_mtx(std::istream & in, int * a, size_t n, size_t m)
{
  for (size_t i = 0; i < n*m; ++i)
  {
    in >> a[i];
  }
}

size_t cols(std::istream & in)
{
  size_t m = 0;
  in >> m;
  return m;
}

size_t rows(std::istream & in)
{
  size_t n = 0;
  in >> n;
  return n;
}

int main(int argc, char ** argv)
{
  if (argc < 4)
  {
    std::cerr << "Not enough arguments" << "\n";
    return 1;
  }
  std::ifstream input(argv[2]);
  size_t n, m;
  n = rows(input);
  m = cols(input);
  int * a = new int[n*m];
  input_mtx(input, a, n, m);
  input.close();
  std::ofstream output(argv[3]);
  output_mtx(output, a, n, m);
  delete[] a;
  return 0;
}
