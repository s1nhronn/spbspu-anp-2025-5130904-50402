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

    std::ifstream input(argv[2]);
    input >> r >> c;

    if (arg == "2")
    {
      // Динамический
    } else if (arg == "1")
    {
      // Фиксированный
      int long long mtx[10000];

      for (size_t i = 0; i <= (r + c); i++)
      {
        input >> mtx[i];
        if (input.fail()) {
          std::cerr << "Incorrect input" << "\n";
          return 2;
        }
      }
      
      //for (size_t i = 0; i <= (r + c); i++)
      //{
      //  std::cout << mtx[i] << "\n";
      //}
    }

    input.close();

    //std::cout << "file :" << r << c << a << "\n";

    std::ofstream output(argv[3]);
    //output << a;

    


  } else
  {
    std::cerr << "Incorrect quantity of arguments" << "\n";
    return 1;
  }
  
  
  return 0;
}
