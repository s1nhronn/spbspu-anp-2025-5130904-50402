#include <iostream>
#include <fstream>
#include <string>

int main (int argc, char ** argv)
{
  if (argc == 4)
  {
    std::string arg = argv[1];
    if (arg == "2")
    {
      std::cout << 22 << "\n";
      // Динамический
    } else if (arg == "1")
    {
      std::cout << 11 << "\n";
      // Фиксированный
    } else {
      std::cerr << "Invalid first argument" << "\n";
      return 1;
    }
  } else
  {
    std::cerr << "Incorrect quantity of arguments" << "\n";
    return 1;
  }
  
  
  return 0;
}
