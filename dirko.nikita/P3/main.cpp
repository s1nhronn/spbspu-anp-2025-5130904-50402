#include <iostream>
#include <cstring>

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
  mode = atoi(argv[1]);
  if (mode == 0 || std::strlen(argv[1]) > 1)
  {
    std::cerr << "First parameter is not a number\n";
    return 1;
  }
  if (mode < 1 || mode > 2)
  {
    std::cerr << "First parameter is out of range\n";
    return 1;
  }
}
