#include <iostream>
#include <string>

int main(int argc, char* argv[])
{
  if (argc < 4)
  {
    std::cerr << "Not enough arguments.\n";
    return 1;
  }

  if (argc > 4)
  {
    std::cerr << "Too many arguments.\n";
    return 1;
  }

  int arg1 = 0;
  try
  {
    arg1 = std::stoi(argv[1]);
  }
  catch(const std::invalid_argument& e)
  {
    std::cerr << "First parameter is not a number.\n";
    return 1;
  }
  catch(const std::out_of_range& e)
  {
    std::cerr << "First parameter is out of range.\n";
    return 1;
  }

  if (arg1 != 1 && arg1 != 2)
  {
    std::cerr << "First parameter is out of range.\n";
    return 1;
  }

  return 0;
}
