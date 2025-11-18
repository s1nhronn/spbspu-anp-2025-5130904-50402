#include <iostream>
#include <fstream>

namespace strelnikov {

  void rm(int* a, size_t r)
  {
    delete[] a;
  }

  void input(std::ifstream& in, int* a, size_t r, size_t c)
  {
    for (size_t i = 0; i < r; ++i) {
      for (size_t j = 0; j < c; ++j) {
        in >> a[i * c + j];
        if (in.fail()) {
          throw std::logic_error("Bad input\n");
        }
      }
    }
  }

  void lftBotCnt(int* mtx, size_t r, size_t c)
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

  size_t cntNzrDig(int* mtx, size_t r, size_t c)
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

  void doall(int pr, const char* inf, const char* outf)
  {
    std::ifstream in(inf);
    if (!in.is_open()) {
      throw std::logic_error("Cannot open input file\n");
    }

    size_t r, c;
    in >> r >> c;
    if (in.fail()) {
      throw std::logic_error("Bad rows and cols file input\n");
    }

    int* mtx = nullptr;

    try {
      if (pr == 1) {
        static int static_mtx[1000 * 1000];
        if (r > 1000 || c > 1000) {
          throw std::logic_error("Matrix too large\n");
        }

        input(in, static_mtx, r, c);
        mtx = static_mtx;
        in.close();

        std::ofstream out(outf);
        if (!out.is_open()) {
          throw std::logic_error("Cannot open output file");
        }

        size_t dig = cntNzrDig(mtx, r, c);
        out << dig << '\n';
        lftBotCnt(mtx, r, c);
        for (size_t i = 0; i < r; ++i) {
          for (size_t j = 0; j < c; ++j)
            out << mtx[i * c + j] << ' ';
          out << '\n';
        }
        out.close();
        return;
      } else {
        try {
          mtx = new int[r * c];
        } catch (std::bad_alloc& e) {
          throw;
        }
        input(in, mtx, r, c);
        in.close();

        std::ofstream out(outf);
        if (!out.is_open()) {
          throw std::logic_error("Cannot open output file");
        }
        size_t dig = cntNzrDig(mtx, r, c);
        out << dig << '\n';
        lftBotCnt(mtx, r, c);
        for (size_t i = 0; i < r; ++i) {
          for (size_t j = 0; j < c; ++j) {
            out << mtx[i * c + j] << ' ';
          }
          out << '\n';
        }
        out.close();
        rm(mtx, r);
      }
    } catch (const std::exception& e) {
      if (pr == 2) {
        rm(mtx, r);
      }
      throw;
    }
  }

} // namespace strelnikov
int main(int argc, char const* argv[])
{
  int ex_code = 0;
  if (argc != 4) {
    if (argc > 4) {
    } else {
      std::cerr << "Too few arguments\n";
    }
    ex_code = 1;
  } else {
    int pr;
    try {
      pr = std::stoi(argv[1]);
    } catch (const std::invalid_argument& e) {
      std::cerr << "First argument is not a number\n";
      ex_code = 1;
    } catch (const std::out_of_range& e) {
      std::cerr << "First argument is out of range\n";
      ex_code = 1;
    }
    if (ex_code == 0) {
      if (pr != 1 && pr != 2) {
        std::cerr << "First argument is out of range\n";
        ex_code = 1;
      }
    }
    if (ex_code == 0) {
      try {
        strelnikov::doall(pr, argv[2], argv[3]);
      } catch (const std::exception& e) {
        std::cerr << e.what();
        ex_code = 2;
      }
    }
  }
  return ex_code;
}
