#include <iostream>
#include <fstream>
#include <string>

//./"main" 2 input.txt output.txt

int main (int argc, char ** argv)
{
  if (argc == 4)
  {
    std::string arg = argv[1];
    if (arg != "2" && arg != "1") {
      std::cerr << "Invalid first argument" << "\n";
      return 1;
    }

    size_t r = 0, c = 0;
    int a = 0;

    std::ifstream input(argv[2]);
    input >> r >> c;
    input >> a;

    input.close();

    std::cout << "file :" << r << c << a << "\n";

    std::ofstream output(argv[3]);
    //output << a;

    if (arg == "2")
    {
      std::cout << 22 << "\n";
      // Динамический
    } else if (arg == "1")
    {
      std::cout << 11 << "\n";
      // Фиксированный
    }
  } else
  {
    std::cerr << "Incorrect quantity of arguments" << "\n";
    return 1;
  }
  
  
  return 0;
}
