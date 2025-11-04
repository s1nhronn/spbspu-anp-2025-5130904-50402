#include <iostream>
#include <fstream>

int main(int argc, char ** argv) {
  if (argc > 4) {
    std::cerr << "Too many arguments\n";
    return 1;
  } else if (argc < 4) {
    std::cerr << "Not enough arguments\n";
    return 1;
  } else if ((argv[1][0] > '2' && argv[1][0] < '9')|| (argv[1][0] < '1' && argv[1][0] > '0')) {
    std::cerr << "First parametr is out of range\n";
    return 1;
  } else if (argv[1][0] != '2' && argv[1][0] != '1') {
    std::cerr << "First parametr is not a number\n";
    return 1;
  }
  std::ifstream input(argv[2]);
  std::ifstream input(argv[3]);
}
