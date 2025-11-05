#include <iostream>
#include <fstream>

namespace dirko
{

}

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
  try
  {
    mode = std::stoi(argv[1]);
  }
  catch (std::out_of_range &e)
  {
    std::cerr << "First parameter is not a number\n";
    return 1;
  }
  if (mode < 1 || mode > 2)
  {
    std::cerr << "First parameter is out of range\n";
    return 1;
  }
  std::ifstream fin(argv[2]);
  // std::ofstream fout(argv[3]);
  if (!fin.is_open())
  {
    std::cerr << "Cant open input file\n";
    return 2;
  }
}
