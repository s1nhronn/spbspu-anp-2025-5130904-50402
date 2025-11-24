#include <iostream>
#include <fstream>
namespace lachugin
{
  void make(std::ifstream& fin, size_t rows, size_t cols, int *mtx)
  {
    fin >> rows >> cols;
    for (size_t i = 0; i < rows*cols; i++) {
      fin >> mtx[i];
      if (fin.eof()) {
        throw std::logic_error("Not enough data\n");
      }
      if (fin.fail()) {
        throw std::logic_error("Can't read\n");
      }
    }
  }
  void LFT_BOT_CLK (int *mtx, size_t rows, size_t cols)
  {
    int d = 1;
    size_t n = 0;
    while (d < rows * cols+1) {
      for (size_t i = cols*(rows-1-n)+n; i >= n*(cols+1); i-=cols) {
        mtx[i] -= d;
        d++;
      }
      if (d == rows * cols+1) {
        break;
      }
      for (size_t i = n*(cols+1)+1; i <= cols*(1+n)-n-1; i++) {
        mtx[i] -= d;
        d++;
      }
      if (d == rows * cols+1) {
        break;
      }
      for (size_t i=cols*(2+n)-n-1; i <= cols*(rows-n)-n-1 ; i+=cols) {
        mtx[i] -= d;
        d++;
      }
      if (d == rows * cols+1) {
        break;
      }
      for (size_t i = cols*(rows-n)-n-2; i > cols*(rows-1-n)+n; i--) {
        mtx[i] -= d;
        d++;
      }
      n++;
    }
  }
  void fopy (double *ptr, const int *mtx, size_t r, size_t c)
  {
    for (long long i = 0; i < r*c; i++) {
      ptr[i] = mtx[i];
    }
  }
  double circle(const int *mtx, size_t i, size_t r, size_t c)
  {
    double k = 0;
    double sum = 0;
    size_t row = i / c;
    size_t col = i % c;
    if (row > 0) {
      if (col > 0) {
        k++;
        sum += mtx[i-1-c];
      }
      k++;
      sum += mtx[i-c];
      if (col < c-1) {
        k++;
        sum += mtx[i+1-c];
      }
    }
    if (col > 0) {
      k++;
      sum += mtx[i-1];
    }
    if (col < c-1) {
      k++;
      sum += mtx[i+1];
    }
    if (row < r-1) {
      if (col > 0) {
        k++;
        sum += mtx[i-1+c];
      }
      k++; sum += mtx[i+c];
      if (col < c-1) {
        k++;
        sum += mtx[i+1+c];
      }
    }
    double arf_Mean = sum/k;
    int temp = arf_Mean*10;
    double res = temp/10.0;
    return res;
  }
  void BLT_SMT_MTR (const int *mtx, size_t rows, size_t cols, double *res2)
  {
    fopy(res2, mtx, rows, cols);
    for (size_t i = 0; i < rows*cols; i++) {
      res2[i] = circle(mtx, i, rows, cols);
    }
  }
  void output(std::ofstream& output, size_t rows, size_t cols, int *res1, double *res2)
  {
    output << rows << ' ' << cols << ' ';
    for (size_t i = 0; i < rows * cols; ++i) {
      if (i == rows*cols-1) {
        output << res1[i];
      } else {
        output << res1[i] << ' ';
      }
    }
    output << '\n';
    output << rows << ' ' << cols << ' ';
    for (size_t i = 0; i < rows * cols; ++i) {
      if (i == rows*cols-1) {
        output << res2[i];
      } else {
        output << res2[i]<< ' ';
      }
    }
    output << '\n';
    output.close();
  }
  void doall (char *infile, char *outfile, size_t rows, size_t cols, int *res1, double *res2, int *mtx)
  {
    std::ifstream fin(infile);
    make(fin, rows, cols, res1);
    fin.close();
    LFT_BOT_CLK(res1, rows, cols);
    fin.open(infile);
    fin.clear();
    make(fin, rows, cols, mtx);
    BLT_SMT_MTR(mtx, rows, cols, res2);
    fin.close();
    std::ofstream output(outfile);
    lachugin::output(output, rows, cols, res1, res2);
  }
}
int main(int argc, char ** argv)
{
  if (argc < 4) {
    std::cerr << "Not enough arguments\n";
    return 1;
  }
  if (argc > 4) {
    std::cerr << "Too many arguments\n";
    return 1;
  }
  char *endFrstArg = nullptr;;
  long prmt = std::strtol(argv[1], std::addressof(endFrstArg), 10);
  if (!(prmt == 1 || prmt == 2) || *endFrstArg != '\0') {
    std::cerr << "First argument is not correct\n";
    return 1;
  }
  std::ifstream fin(argv[2]);
  if (!fin.is_open()) {
     std::cerr << "Error opening file\n";
    return 1;
  }
  size_t rows = 0, cols = 0;
  fin >> rows >> cols;
  if (fin.fail()) {
    std::cerr <<  "Error reading file\n";
    return 1;
  }
  fin.close();
  if (prmt == 2) {
    int *res1 = new int[rows*cols];
    double *res2 = new double[rows*cols];
    int *mtx = new int[rows*cols];
    try
    {
      lachugin::doall(argv[2], argv[3], rows, cols, res1, res2, mtx);
      delete [] res1;
      delete [] res2;
      delete [] mtx;
    } catch (std::logic_error &e) {
      std::cerr << e.what() << '\n';
      delete [] mtx;
      delete [] res1;
      delete [] res2;
      return 2;
    }
  }
  if (prmt == 1) {
    int res1[10000];
    double res2[10000];
    int mtx[10000];
    try
    {
      lachugin::doall(argv[2], argv[3], rows, cols, res1, res2, mtx);
    } catch (std::logic_error &e) {
      std::cerr<<e.what()<<'\n';
      return 2;
    }
  }
}
