#include <fstream>
#include <ostream>

void input(const std::istream &in, const int *m);
std::ostream &output(const std::ostream &out, const int *m);

int main(int argc, char **argv)
{
  char *num = argv[1];
  std::ifstream in(argv[2]);
  std::ofstream out(argv[3]);

  int a[10000] = {};
  int *b = new int[1];
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
