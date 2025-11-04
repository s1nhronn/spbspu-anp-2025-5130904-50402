#include <iostream>

int main(int argc, char ** argv)
{
  if (argc < 4) {
    std::cerr << "Not enough arguments\n";
    return 1;
  } else if (argc > 4) {
    std::cerr << "Too many arguments\n";
    return 1;
  } else if (*argv[1] > 2) {
    std::cerr << "First parameter is out of range\n";
    return 1;
  }

}
