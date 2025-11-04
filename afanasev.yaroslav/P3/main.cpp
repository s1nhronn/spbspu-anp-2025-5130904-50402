#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>

//./"main" 2 input.txt output.txt

namespace afanasev {
  int long long CNT_LOC_MIN(long long *mtx, size_t a)
  {
    return 0;
  }

  int long long CNT_LOC_MAX(long long *mtx, size_t a)
  {
    return 0;
  }
}

int main (int argc, char ** argv)
{
  if (argc == 4)
  {
    std::string arg = argv[1];
    if (arg != "2" && arg != "1")
    {
      std::cerr << "Invalid first argument" << "\n";
      return 1;
    }

    size_t r = 0, c = 0;

    std::ifstream input(argv[2]);
    input >> r >> c;
    if (!(r * c))
    {
      std::ofstream output(argv[3]);
      output << "0 0";
      output.close();
    } else if (arg == "2")
    {
      // Динамический
      long long *mtx = (long long *)malloc(r * c * sizeof(long long));

      if (mtx == nullptr)
      {
        std::cerr << "Get memory failed" << "\n";
        return 2;
      }

      for (size_t i = 0; i < (r * c); i++)
      {
        input >> mtx[i];
        if (input.fail()) {
          std::cerr << "Incorrect input" << "\n";
          free(mtx);
          return 2;
        }
      }


      int long long min = 0;
      min = afanasev::CNT_LOC_MIN(mtx, r * c);
      int long long max = 0;
      min = afanasev::CNT_LOC_MAX(mtx, r * c);

      free(mtx);

      std::ofstream output(argv[3]);
      output << min << " " << max << "\n";
      output.close();

    } else if (arg == "1")
    {
      // Фиксированный
      int long long mtx[10000];

      for (size_t i = 0; i < (r * c); i++)
      {
        input >> mtx[i];
        if (input.fail()) {
          std::cerr << "Incorrect input" << "\n";
          return 2;
        }
      }
      
      //for (size_t i = 0; i < (r * c); i++)
      //{
      //  std::cout << mtx[i] << "\n";
      //}
    }

    input.close();

  } else
  {
    std::cerr << "Incorrect quantity of arguments" << "\n";
    return 1;
  }
  return 0;
}
