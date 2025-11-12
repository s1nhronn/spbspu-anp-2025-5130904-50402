#include <exception>
#include <iostream>
#include <stdexcept>
#include <string>
int main(int argc, char ** argv)
{
  if (argc < 4) {
    std::cerr << "Not enough arguments\n";
    return 1;
  } else if (argc > 4) {
    std::cerr << "Too many arguments\n";
    return 1;
  }

  int firstarg;

  try {
    firstarg = std::stoi(argv[1]);
  } catch (std::invalid_argument &) {
    std::cerr << "First parameter is not a number\n";
  } catch (std::out_of_range &) {
    std::cerr << "First parameter is out of range\n";
  }

  if (firstarg != 1 || firstarg != 2) {
    std::cerr << "First parameter is out of range\n";
    return 1;
  }

  try {
    if (firstarg == 1) {
      // static array function
    } else if (firstarg == 2) {
      // dynamic array function
    }
  } catch (std::exception & e) {
    std::cerr << e.what() << "\n";
    return 2;
  }
}
