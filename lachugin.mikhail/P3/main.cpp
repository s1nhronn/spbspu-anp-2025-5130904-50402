#include <iostream>
#include <fstream>
namespace lachugin {

  void convert_int(int **a, long long r, long long c, int *res1) {
    long long start = 0;
    for (long long i = 0; i < r; i++) {
      for (long long j = 0; j < c; j++) {
        res1 [start] = a[i][j];
        start++;
      }
    }
  }

  void convert_dbl(double **a, long long r, long long c, double *res2) {
    long long start = 0;
    for (long long i = 0; i < r; i++) {
      for (long long j = 0; j < c; j++) {
        res2 [start] = a[i][j];
        start++;
      }
    }
  }

  void make(std::ifstream& fin,long long rows, long long cols, int **mtx){
    fin.seekg(3);
    for (long long i = 0; i < rows; i++) {
      for (long long j = 0; j < cols; j++) {
        fin >> mtx[i][j];
        if (fin.eof()) {
          throw std::logic_error("Not enough data\n");
        }
        if (fin.fail()) {
          throw std::logic_error("Can't read\n");
        }
      }
    }
  }
  int *LFT_BOT_CLK (int *mtx, long long rows, long long cols, int *res1) {
    int d = 1;
    long long n = 0;
    while (d < rows * cols+1) {
      for (long long i = cols*(rows-1-n)+n; i >= n*(cols+1); i=-cols) {   // up
        mtx[i] -= d;
        d++;
      }
      if (d == rows * cols+1) {
        break;
      }
      for (long long i = n*(cols+1)+1; i <= cols*(1+n)-n-1; i++) { // right
        mtx[i] -= d;
        d++;
      }
      if (d == rows * cols+1) {
        break;
      }
      for (long long i=cols*(2+n)-n-1; i <= cols*(rows-n)-n-1 ; i+=cols) {   // down
        mtx[i] -= d;
        d++;
      }
      if (d == rows * cols+1) {
        break;
      }
      for (long long i = cols*(rows-n)-n-2; i > cols*(rows-1-n)+n; i--) {   // left
        mtx[i] -= d;
        d++;
      }
      n++;
    }

    convert_int(mtx, rows, cols, res1);
    return res1;
  }

  void fopy (double **ptr, int **mtx, long long r, long long c){
    for (long long i = 0; i < r; i++) {
      for (long long j = 0; j < c; j++) {
        ptr[i][j] = mtx[i][j];
      }
    }
  }

  double circle(int **mtx, long long i, long long j, long long r, long long c){
    long long k = 0;
    long long sum = 0;
    if (i-1 >= 0&& j-1 >= 0) {
      k++;
      sum += mtx[i-1][j-1];
    }
    if (j-1 >= 0) {
      k++;
      sum += mtx[i][j-1];
    }
    if (i+1 <=r-1 && j-1 >= 0) {
      k++;
      sum += mtx[i+1][j-1];
    }
    if (i+1 <= (r-1)) {
      k++;
      sum += mtx[i+1][j];
    }
    if (i+1 <= r-1 && j+1 <= c-1) {
      k++;
      sum += mtx[i+1][j+1];
    }
    if (j+1 <= c-1) {
      k++;
      sum += mtx[i][j+1];
    }
    if (j+1 <= c-1 && i-1 >= 0) {
      k++;
      sum += mtx[i-1][j+1];
    }
    if (i-1>=0) {
      k++;
      sum += mtx[i-1][j];
    }
    double result = ((static_cast<double>(sum)/static_cast<double>(k)) *10 + 0.5) / 10.0;
    return result;
  }

  double *BLT_SMT_MTR (int **mtx, long long rows, long long cols, int prmt, double *res2){
    double **ptr = nullptr;
    double* pointers[100];
    if (prmt == 1) {
      static double a[100][100];
      for (long long i = 0; i < rows; i++) {
        pointers[i] = a[i];
      }
      ptr = &pointers[0];
    }
    if (prmt == 2) {
      double **b = new double*[rows];
      for (long long i = 0; i < rows; i++) {
        b[i] = new double[cols];
      }
      ptr = b;

    }
    fopy(ptr, mtx, rows, cols);

    for (long long i = 0; i < rows; i++) {
      for (long long j = 0; j < cols; j++) {
        ptr[i][j] = circle(mtx, i, j, rows, cols);
      }
    }

    convert_dbl(ptr, rows, cols, res2);
    if (prmt == 2) {
      for  (long long i = 0; i < rows; i++) {
        delete[] ptr[i];
      }
      delete [] ptr;
    }
    return res2;
  }
  void rm(int **mtx, long long r) {
    for (long long i = 0; i < r; i++) {

      delete []mtx[i];
    }
    delete [] mtx;
  }
}
int main(int argc, char ** argv) {
  if (argc < 4 ) {
    std::cerr << "Not enough arguments\n";
    return 1;
  }
  if ( argc > 4 ) {
    std::cerr << "Too many arguments\n";
    return 1;
  }
  int prmt = 0;
  try{
    prmt = std::stoi(argv[1]);
  } catch (const std::invalid_argument& e){
    std::cerr << "First parameter is not a number\n";
    return 1;
  }
  if ( prmt != 2 && prmt != 1 ){
    std::cerr << "First parameter is out of range\n";
    return 1;
  }
  std::ifstream fin(argv[2]);
  if (!fin.is_open()) {
     std::cerr << "Error opening file\n";
    return 1;
  }
  long long rows = 0, cols = 0;
  fin >> rows >> cols;
  if (fin.fail()) {
    std::cerr <<  "Error reading file\n";
    return 1;
  }
  int *var1 = nullptr;
  double *var2 = nullptr;
  if (prmt == 2) {
    int *res1 = new int[rows*cols];
    int **mtx1 = new int *[rows];
    for (long long i = 0; i < rows; i++){
      mtx1[i] = new int[cols];
    };
    double *res2 = new double[rows*cols];
    int **mtx2 = new int *[rows];
    for (long long i = 0; i < rows; i++){
      mtx2[i] = new int[cols];
    };
    try {
      lachugin::make(fin, rows, cols, mtx1);
      var1 = lachugin::LFT_BOT_CLK(mtx1, rows, cols, res1);
      lachugin::make(fin, rows, cols, mtx2);
      var2 = lachugin::BLT_SMT_MTR(mtx2, rows, cols, prmt, res2);
      std::ofstream output(argv[3]);
      output << rows << ' ' << cols << ' ';
      for (long long i = 0; i < rows * cols; ++i) {
        output << var1[i] << ' ';
      }
      output << '\n';
      output << rows << ' ' << cols << ' ';
      for (long long i = 0; i < rows * cols; ++i) {
        output << var2[i] << ' ';
      }
      output << '\n';
      output.close();
      lachugin::rm (mtx2, rows);
      lachugin::rm (mtx1, rows);
      delete [] res1;
      delete [] res2;
    } catch (std::logic_error &e) {
      std::cerr << e.what() << '\n';
      lachugin::rm (mtx2, rows);
      lachugin::rm (mtx1, rows);
      delete [] res1;
      delete [] res2;
      return 2;
    }
  }
  if (prmt == 1) {
    int res1[10000];
    int arr1[100][100];
    int* pointers1[100];
    try {
      for (long long i = 0; i < rows; i++) {
        pointers1[i] = arr1[i];
      }
      lachugin::make(fin, rows, cols, pointers1);
      var1 = lachugin::LFT_BOT_CLK(pointers1, rows, cols, res1);
      double res2[10000];
      int arr2[100][100];
      int* pointers2[100];
      for (long long i = 0; i < rows; i++) {
        pointers2[i] = arr2[i];
      }
      lachugin::make(fin, rows, cols, pointers2);
      var2 = lachugin::BLT_SMT_MTR(pointers2, rows, cols, prmt, res2);
      fin.close();

      std::ofstream output(argv[3]);
      output << rows << ' ' << cols << ' ';
      for (long long i = 0; i < rows * cols; ++i) {
        output << var1[i] << ' ';
      }
      output << '\n';
      output << rows << ' ' << cols << ' ';
      for (long long i = 0; i < rows * cols; ++i) {
        output << var2[i] << ' ';
      }
      output << '\n';
      output.close();
    } catch (std::logic_error &e) {
      std::cerr<<e.what()<<'\n';
      return 2;
    }
  }
}
