#include <iostream>
#include <fstream>
#include <memory>

namespace permyakov
{
  void movePointToEnd(int * arr, size_t & ij, size_t & cnt, size_t end,
  size_t & i, size_t & j, size_t m, bool isCntInc, bool isIncr);
  void lft_top_clk(int * arr2, int * arr, size_t n, size_t m);
  void lft_bot_cnt(int * arr2, int * arr, size_t n, size_t m);
  void arrOutInFile(int * arr, size_t n, size_t m, std::ofstream & out);
}

int main(int argc, char ** argv)
{
  namespace per = permyakov;
  if(argc < 4){
    std::cerr << "Not enough arguments\n";
    return 1;
  }
  if(argc > 4){
    std::cerr << "Too many arguments\n";
    return 1;
  }
  int task = std::stoi(argv[1]);

  if(task != 1 && task != 2){
    std::cerr << "First argument is not correct\n";
    return 1;
  }
  std::ifstream input(argv[2]);
  size_t n = 0, m = 0;
  input >> n >> m;
  if(input.fail()){
    if(input.eof()){
      std::cerr << "Missing size of array\n";
    } else {
      std::cerr << "Invalid format of size\n";
    }
    return 2;
  }
  int * arr1 = nullptr;
  int * arr2 = nullptr;
  size_t s = 0;
  const size_t SIZE_OF_MATRIX = 10000;
  if(task == 1){
    int arr[SIZE_OF_MATRIX]{};
    for(size_t num = 0; input >> num; ++s){
      arr[s] = num;
    }
    if(!input.eof()){
      std::cerr << "Invalid array format\n";
      return 2;
    }
    input.close();
    if(s != n * m){
      std::cerr << "Failure to define array";
      return 2;
    }
    try{
      arr1 = reinterpret_cast< int * >(malloc(sizeof(int) * n * m));;
    } catch(std::bad_alloc()){
      std::cerr << "Failure to allocate memoty\n";
      return 3;
    }
    try{
      arr2 = reinterpret_cast< int * >(malloc(sizeof(int) * n * m));
    } catch(std::bad_alloc()){
      std::cerr << "Failure to allocate memory\n";
      free(arr1);
      return 3;
    }
    per::lft_top_clk(arr1, arr, n, m);
    per::lft_bot_cnt(arr2, arr, n, m);
  } else {
    int * d_arr = reinterpret_cast< int * >(malloc(sizeof(int) * n * m));
    if(d_arr == nullptr){
      std::cerr << "Failure to allocate memory\n";
      return 3;
    }
    for(size_t num = 0; input >> num; ++s){
      d_arr[s] = num;
    }
    if(!input.eof()){
      std::cerr << "Invalid array format\n";
      free(d_arr);
      return 2;
    }
    input.close();
    if(s != n * m){
      std::cerr << "Failure to define array";
      free(d_arr);
      return 2;
    }
    try{
      arr1 = reinterpret_cast< int * >(malloc(sizeof(int) * n * m));
    } catch(std::bad_alloc()){
      std::cerr << "Failure to allocate memory\n";
      free(d_arr);
      return 3;
    }
    try{
      arr2 = reinterpret_cast< int * >(malloc(sizeof(int) * n * m));
    } catch(std::bad_alloc()){
      std::cerr << "Failure to allocate memory\n";
      free(arr1);
      free(d_arr);
      return 3;
    }
    per::lft_top_clk(arr1, d_arr, n, m);
    per::lft_bot_cnt(arr2, d_arr, n, m);
    free(d_arr);
  }

  std::ofstream output(argv[3]);
  per::arrOutInFile(arr1, n, m, output);
  output << "\n";
  per::arrOutInFile(arr2, n, m, output);
  free(arr1);
  free(arr2);
}
//прошу прощения за функцию ниже,
//но это самый очевидный вариант вынести цикл в отдельную функцию
void permyakov::movePointToEnd(int * arr, size_t & ij, size_t & cnt, size_t end,
size_t & i, size_t & j, size_t m, bool isCntInc, bool isIncr)
{
  if(isIncr){
    while(ij < end){
      arr[i * m + j] += cnt * (isCntInc ? 1 : -1);
      cnt++;
      ij++;
    }
  } else {
    while(ij > end){
      arr[i * m + j] += cnt * (isCntInc ? 1 : -1);
      cnt++;
      ij--;
    }
  }
}

void permyakov::lft_top_clk(int * arr1, int * arr, size_t n, size_t m)
{
  if(n * m == 0){
    return;
  }
  for(size_t i = 0; i < n * m; ++i){
    arr1[i] = arr[i];
  }
  size_t lef = 0, rig = m - 1, top = 0, bot = n - 1;
  size_t cnt = 1, i = 0, j = 0;
  namespace per = permyakov;
  while(cnt < n * m){
    per::movePointToEnd(arr1, j, cnt, rig, i, j, m, false, true);
    top++;
    per::movePointToEnd(arr1, i, cnt, bot, i, j, m, false, true);
    rig--;
    per::movePointToEnd(arr1, j, cnt, lef, i, j, m, false, false);
    bot--;
    per::movePointToEnd(arr1, i, cnt, top, i, j, m, false, false);
    lef++;
    if(cnt == m * n){
      arr1[i * m + j] -= cnt;
    }
  }
}

void permyakov::lft_bot_cnt(int * arr2, int * arr, size_t n, size_t m)
{
  if(n * m == 0){
    return;
  }
  for(size_t i = 0; i < n * m; ++i){
    arr2[i] = arr[i];
  }
  size_t lef = 0, rig = m - 1, top = 0, bot = n - 1;
  size_t cnt = 1, i = n - 1, j = 0;
  namespace per = permyakov;
  while(cnt < n * m){
    per::movePointToEnd(arr2, j, cnt, rig, i, j, m, true, true);
    bot--;
    per::movePointToEnd(arr2, i, cnt, top, i, j, m, true, false);
    rig--;
    per::movePointToEnd(arr2, j, cnt, lef, i, j, m, true, false);
    top++;
    per::movePointToEnd(arr2, i, cnt, bot, i, j, m, true, true);
    lef++;
    if(cnt == n * m){
      arr2[i * m + j] += cnt;
    }
  }
}

void permyakov::arrOutInFile(int * arr, size_t n, size_t m, std::ofstream & out)
{
  out << n << " " << m;
  for(size_t i = 0; i < n * m; ++i){
    out << " " << arr[i];
  }
}
