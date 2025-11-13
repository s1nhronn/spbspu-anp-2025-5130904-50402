#include <iostream>
#include <iomanip>
#include <cctype>

namespace dirko
{
  char *getLine(std::istream &in, size_t &size);
  size_t DIF_LAT(char *str);
  char *UPP_LOW(const char *source, char *distention);
  std::ostream &output(std::ostream &out, size_t res1, char *res2);
}
int main()
{
  char *str = nullptr;
  size_t size = 0;
  dirko::getLine(std::cin, size);
  size_t result1 = dirko::DIF_LAT(str);
  char *result2 = nullptr;
  result2 = reinterpret_cast<char *>(malloc(sizeof(char) * size));
  dirko::UPP_LOW(str, result2);
  dirko::output(std::cout, result1, result2) << '\n';
  free(str);
  free(result2);
}
