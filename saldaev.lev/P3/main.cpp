#include <iostream>
#include <fstream>

size_t CNT_ROW_NSM(int long long* matrix, size_t rows, size_t cols);
int long long* LFT_BOT_CLK(int long long* matrix, size_t rows, size_t cols);

int main(int argc, char ** argv)
{
  if (argc < 4)
  {
    std::cerr << "Not enough arguments\n";
    return 1;
  }
  else if (argc > 4)
  {
    std::cerr << "Too many arguments\n";
    return 1;
  }

  std::string arg = argv[1];
  if (arg != "1" and arg != "2")
  {
    std::cerr << "First parameter is unacceptable\n";
    return 1;
  }

  std::ifstream input(argv[2]);
  std::ofstream output(argv[3]);

  if (arg == "1")
  {
    //работа с массивом фиксированного размера
  }
  else
  {
    //работа с динамическим массивом
  }

  return 0;
}