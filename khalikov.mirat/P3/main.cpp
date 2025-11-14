#include <iostream>
#include <fstream>

void output(std::ostream & out, const int * a, size_t n, size_t m)
{
  for (size_t i = 0; i < n; ++i)
  {
    for (size_t j = 0; j < m; ++j)
    {
       out << a[i*m + j] << " ";
    }
    std::cout << "\n";
  }
}

void input(std::ostream & in, const int * a, size_t n, size_t m)
{
  for (size_t i = 0; i < n*m; ++i)
  {
    in >> a[i];
  }
}

int main(int argc, char ** argv)
{
  std::ifstream input(argv[2]);
  std::ofstream output(argv[3]);
}
