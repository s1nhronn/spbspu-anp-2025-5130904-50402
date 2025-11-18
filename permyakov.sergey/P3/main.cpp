#include <iostream>
#include <fstream>
#include <memory>

namespace permyakov
{
  bool isErr(size_t sizeArr, size_t size);
  int * lft_top_clk(int * arr, size_t n, size_t m);
  int * lft_bot_cnt(int * arr, size_t n, size_t m);
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
      arr1 = per::lft_top_clk(arr, n, m);
    } catch(std::bad_alloc()){
      std::cerr << "Failure to allocate memoty\n";
      return 3;
    }
    try{
      arr2 = per::lft_bot_cnt(arr, n, m);
    } catch(std::bad_alloc()){
      std::cerr << "Failure to allocate memory\n";
      free(arr1);
      return 3;
    }
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
      arr1 = per::lft_top_clk(d_arr, n, m);
    } catch(std::bad_alloc()){
      std::cerr << "Failure to allocate memory\n";
      free(d_arr);
      return 3;
    }
    try{
      arr2 = per::lft_bot_cnt(d_arr, n, m);
    } catch(std::bad_alloc()){
      std::cerr << "Failure to allocate memory\n";
      free(arr1);
      free(d_arr);
      return 3;
    }
    free(d_arr);
  }

  std::ofstream output(argv[3]);
  output << n << " " << m << " ";
  for(size_t i = 0; i < n * m; ++i){
    output << arr1[i] << " ";
  }
  output << "\n" << n << " " << m << " ";
  for(size_t i = 0; i < n * m; ++i){
    output << arr2[i] << " ";
  }
  output.close();
  free(arr1);
  free(arr2);
}

int * permyakov::lft_top_clk(int * arr, size_t n, size_t m)
{
  int * arr1 = reinterpret_cast< int * >(malloc(sizeof(int) * n * m));
  if(arr1 == nullptr){
    throw std::bad_alloc();
  }
  for(size_t i = 0; i < n * m; ++i){
    arr1[i] = arr[i];
  }
  size_t lef = 0, rig = m - 1, top = 0, bot = n - 1;
  size_t cnt = 1, i = 0, j = 0;
  while(cnt < n * m){
    while(j < rig){
      arr1[i * n + j] -= cnt;
      cnt++;
      j++;
    }
    top++;
    while(i < bot){
      arr1[i * n + j] -= cnt;
      cnt++;
      i++;
    }
    rig--;
    while(j > lef){
      arr1[i * n + j] -= cnt;
      cnt++;
      j--;
    }
    bot--;
    while(i > top){
      arr1[i * n + j] -= cnt;
      cnt++;
      i--;
    }
    lef++;
    if(cnt == m * n){
      arr1[i * n + j] -= cnt;
    }
  }
  return arr1;
}

int * permyakov::lft_bot_cnt(int * arr, size_t n, size_t m)
{
  int * arr2 = reinterpret_cast< int * >(malloc(sizeof(int) * n * m));
  if(arr2 == nullptr){
    throw std::bad_alloc();
  }
  for(size_t i = 0; i < n * m; ++i){
    arr2[i] = arr[i];
  }
  size_t lef = 0, rig = m - 1, top = 0, bot = n - 1;
  size_t cnt = 1, i = n - 1, j = 0;
  while(cnt < n * m){
    while(j < rig){
      arr2[i * n + j] += cnt;
      cnt++;
      j++;
    }
    bot--;
    while(i > top){
      arr2[i * n + j] += cnt;
      cnt++;
      i--;
    }
    rig--;
    while(j > lef){
      arr2[i * n + j] += cnt;
      cnt++;
      j--;
    }
    top++;
    while(i < bot){
      arr2[i * n + j] += cnt;
      cnt++;
      i++;
    }
    lef++;
    if(cnt == n * m){
      arr2[i * n + j] += cnt;
    }
  }
  return arr2;
}
