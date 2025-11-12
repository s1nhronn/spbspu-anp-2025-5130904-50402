#include <fstream>
#include <iostream>
#include <stdexcept>

size_t lengthInput(char *file);
void input(std::istream &in, int *m, size_t lng);
std::ostream &output(std::ostream &out, const int *m, size_t a, size_t b);

int main(int argc, char **argv)
{
  if (argc < 4)
  {
    std::cerr << "Not enough arguments\n";
    return 1;
  }
  if (argc > 4)
  {
    std::cerr << "Too many arguments\n";
  }
  // TODO: Условие для argv[1] > 2 и для argv[1] -  не число

  char *num = argv[1];
  size_t lng = 0;
  try
  {
    lng = lengthInput(argv[2]);
  } catch (const std::logic_error &e)
  {
    std::cerr << e.what() << '\n';
    return 2;
  }
  int a[10000] = {};
  int *b = new int[lng];
  std::ifstream in(argv[2]);
  size_t m, n;
  in >> m >> n;

  int *massive = nullptr;
  if (num[0] == '1')
  {
    input(in, a, lng);
    massive = a;
    delete[] b;
  }
  else
  {
    input(in, a, lng);
    massive = b;
  }
}

size_t lengthInput(char *file)
{
  std::ifstream in(file);
  size_t a, b;
  in >> a >> b;
  if (in.fail())
  {
    throw std::logic_error("Size of massive is not correct");
  }
  return a * b;
}

void input(std::istream &in, int *m, size_t lng)
{
  for (size_t i = 0; i < lng; i++)
  {
    in >> m[i];
    if (in.fail())
    {
      throw std::logic_error("Values in massive is not correct");
    }
  }
}
