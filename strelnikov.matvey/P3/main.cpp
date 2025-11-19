#include <iostream>
#include <fstream>

namespace strelnikov {

  bool prValidation(char* a)
  {
    if (std::string(a) != "1" && std::string(a) != "2") {
      return false;
    }
    return true;
  }

  void input(std::ifstream& in, int* a, size_t r, size_t c)
  {
    for (size_t i = 0; i < r; ++i) {
      for (size_t j = 0; j < c; ++j) {
        in >> a[i * c + j];
        if (!in) {
          throw std::logic_error("Wrong format\n");
        }
      }
    }
  }

  void output(std::ofstream& out, int* a, size_t r, size_t c)
  {
    for (size_t i = 0; i < r; ++i) {
      for (size_t j = 0; j < c; ++j) {
        out << a[i * c + j] << ' ';
      }
      out << '\n';
    }
  }

  void doLftBotCnt(int* mtx, size_t r, size_t c)
  {
    if (r == 0 || c == 0) {
      return;
    }
    size_t top = 0, left = 0;
    size_t bot = r - 1, right = c - 1;
    int cnt = 1;

    while (left <= right && top <= bot) {
      for (size_t j = left; j <= right; ++j) {
        mtx[bot * c + j] += cnt++;
      }
      if (bot == 0) {
        break;
      }
      --bot;

      if (left <= right) {
        for (size_t i = bot; i >= top; --i) {
          mtx[i * c + right] += cnt++;
          if (i == 0) {
            break;
          }
        }
        if (right == 0) {
          break;
        }
        --right;
      }

      if (top <= bot && left <= right) {
        for (size_t j = right; j >= left; --j) {
          mtx[top * c + j] += cnt++;
          if (j == 0) {
            break;
          }
        }
        ++top;
      }

      if (left <= right && top <= bot) {
        for (size_t i = top; i <= bot; ++i) {
          mtx[i * c + left] += cnt++;
        }
        ++left;
      }
    }
  }

  size_t doCntNzrDig(int* mtx, size_t r, size_t c)
  {
    size_t min = (r < c) ? r : c;
    size_t cnt = 0;
    for (size_t i = 1; i < min; ++i) {
      int tr = 1;
      for (size_t j = 0; j < min - i; ++j) {
        if (mtx[j * c + j + i] == 0) {
          tr = 0;
          break;
        }
      }

      int tr2 = 1;
      for (size_t j = 0; j < min - i; ++j) {
        if (mtx[(j + i) * c + j] == 0) {
          tr2 = 0;
          break;
        }
      }
      cnt += tr + tr2;
    }
    return cnt;
  }

}
int main(int argc, char* argv[])
{
  if (argc != 4) {
    if (argc > 4) {
      std::cerr << "Too many arguments\n";
    } else {
      std::cerr << "Too few arguments\n";
    }
    return 1;
  }
  if (!strelnikov::prValidation(argv[1])) {
    std::cerr << "First argument must be a number(1 or 2)\n";
    return 1;
  }
  int pr = std::stoi(argv[1]);

  std::ifstream in(argv[2]);
  if (!in.is_open()) {
    std::cerr << "Cannot open input file\n";
    return 2;
  }

  size_t r, c;
  in >> r >> c;
  if (!in) {
    std::cerr << "Bad rows and cols file input\n";
    return 2;
  }
  if ((r > 1000 || c > 1000) && pr == 1) {
    std::cerr << "Matrix too large\n";
    return 2;
  }

  int* mtx = nullptr;
  try {
    if (pr == 1) {
      static int static_mtx[1000 * 1000];
      try {
        strelnikov::input(in, static_mtx, r, c);
      } catch (std::logic_error& e) {
        std::cerr << e.what();
        return 2;
      }
      mtx = static_mtx;
      in.close();
    } else {
      mtx = new int[r * c];
      try {
        strelnikov::input(in, mtx, r, c);
      } catch (std::logic_error& e) {
        std::cerr << e.what();
        delete[] mtx;
        return 2;
      }
      in.close();
    }
  } catch (const std::exception& e) {
    if (pr == 2) {
      delete[] mtx;
    }
    return 2;
  }
  std::ofstream out(argv[3]);
  if (!out.is_open()) {
    std::cerr << "Cannot open output file\n";
    if (pr == 2) {
      delete[] mtx;
    }
    return 2;
  }
  size_t dig = strelnikov::doCntNzrDig(mtx, r, c);
  strelnikov::doLftBotCnt(mtx, r, c);
  out << dig << '\n';
  strelnikov::output(out, mtx, r, c);
  if (pr == 2) {
    delete[] mtx;
  }
}
