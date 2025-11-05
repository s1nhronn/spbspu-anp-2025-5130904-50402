#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>

namespace afanasev
{
  int long long CNT_LOC_MIN(const int long long *mtx, const size_t r, const size_t c)
  {
    bool flag = 1;
    int long long n = 0;
    size_t ans = 0;

    for (size_t y = 1; y < r - 1; y++)
    {
      flag = 1;
      for (size_t x = 1; x < c - 1; x++)
      {
        n = mtx[(y * c) + (x)];
        flag = flag && (n < mtx[(y - 1) * c + (x - 1)]);
        flag = flag && (n < mtx[(y - 1) * c + (x)]);
        flag = flag && (n < mtx[(y - 1) * c + (x + 1)]);

        flag = flag && (n < mtx[(y * c) + (x - 1)]);
        flag = flag && (n < mtx[(y * c) + (x + 1)]);

        flag = flag && (n < mtx[(y + 1) * c + (x - 1)]);
        flag = flag && (n < mtx[(y + 1) * c + (x)]);
        flag = flag && (n < mtx[(y + 1) * c + (x + 1)]);

        if (flag)
        {
          ans++;
        }
      }
    }
    return ans;
  }

  int long long CNT_LOC_MAX(const int long long *mtx, const size_t r, const size_t c)
  {
    bool flag = 1;
    int long long n = 0;
    size_t ans = 0;

    for (size_t y = 1; y < r - 1; y++)
    {
      flag = 1;
      for (size_t x = 1; x < c - 1; x++)
      {
        n = mtx[(y * c) + (x)];
        flag = flag && (n > mtx[(y - 1) * c + (x - 1)]);
        flag = flag && (n > mtx[(y - 1) * c + (x)]);
        flag = flag && (n > mtx[(y - 1) * c + (x + 1)]);

        flag = flag && (n > mtx[(y * c) + (x - 1)]);
        flag = flag && (n > mtx[(y * c) + (x + 1)]);

        flag = flag && (n > mtx[(y + 1) * c + (x - 1)]);
        flag = flag && (n > mtx[(y + 1) * c + (x)]);
        flag = flag && (n > mtx[(y + 1) * c + (x + 1)]);

        if (flag)
        {
          ans++;
        }
      }
    }
    return ans;
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
    if (input.fail())
    {
      std::cerr << "Incorrect input" << "\n";
      return 2;
    }

    if (arg == "2")
    {
      int long long *mtx = (int long long *)malloc(r * c * sizeof(int long long));

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
      min = afanasev::CNT_LOC_MIN(mtx, r, c);
      int long long max = 0;
      max = afanasev::CNT_LOC_MAX(mtx, r, c);

      free(mtx);

      std::ofstream output(argv[3]);
      output << min << " " << max << "\n";
      output.close();
    }
    else if (arg == "1")
    {
      int long long mtx[10000] = {};

      for (size_t i = 0; i < (r * c); i++)
      {
        input >> mtx[i];
        if (input.fail())
        {
          std::cerr << "Incorrect input" << "\n";
          return 2;
        }
      }
      int long long min = 0;
      min = afanasev::CNT_LOC_MIN(mtx, r, c);
      int long long max = 0;
      max = afanasev::CNT_LOC_MAX(mtx, r, c);

      std::ofstream output(argv[3]);
      output << min << " " << max << "\n";
      output.close();
    }
    input.close();
  }
  else
  {
    std::cerr << "Incorrect quantity of arguments" << "\n";
    return 1;
  }
  return 0;
}
