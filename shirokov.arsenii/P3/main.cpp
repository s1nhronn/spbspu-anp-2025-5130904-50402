#include <fstream>
#include <ostream>

size_t lengthInput(char *file);
void input(const std::istream &in, const int *m);
std::ostream &output(const std::ostream &out, const int *m, size_t a, size_t b);

int main(int argc, char **argv)
{
  char *num = argv[1];

  int a[10000] = {};
  int *b = new int[lengthInput(argv[2])];
  std::ifstream in(argv[2]);
  int *m = nullptr;
  if (num[0] == '1')
  {
    input(in, a);
    m = a;
    delete[] b;
  }
  else
  {
    input(in, a);
    m = b;
  }
}

size_t lengthInput(char *file)
{
  std::ifstream in(file);
  size_t count = 0;
  int temp = 0;
  in >> temp >> temp;
  while (in >> temp)
  {
    count++;
  }
  in.close();
  return count;
}
