#include <iostream>
#include <fstream>
#include <memory>

bool isErr1(int argc, char ** argv);
bool isErr2(size_t sizeArr, size_t size);
bool isEmptyFile(std::ifstream & input);
int * changeArrVar1(const int * arr, size_t n);
int * changeArrVar2(const int * arr, size_t n);

int main(int argc, char ** argv)
{
  if(argc == 0){
    return 0;
  }
  if(isErr1(argc, argv)){
    return 1;
  }

  std::ifstream input(argv[2]);
  if(isEmptyFile(input)){
    return 2;
  }
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
  if(argv[1][0] == '1'){
    int arr[10000]{};
    for(size_t num = 0; input >> num; ++s){
      arr[s] = num;
    }
    if(!input.eof()){
      std::cerr << "Invalid array format\n";
      return 2;
    }
    input.close();
    if(isErr2(s, n * m)){
      return 2;
    }
    try{
      arr1 = changeArrVar1(arr, n);
      arr2 = changeArrVar2(arr, n);
    } catch(std::bad_alloc()){
      std::cerr << "Failure to allocate memoty\n";
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
    if(isErr2(s, n * m)){
      free(d_arr);
      return 2;
    }
    try{
      arr1 = changeArrVar1(d_arr, n);
      arr2 = changeArrVar2(d_arr, n);
    } catch(std::bad_alloc()){
      std::cerr << "Failure to allocate memoty\n";
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

bool isErr1(int argc, char ** argv)
{
  if(argc < 4){
    std::cerr << "Not enough arguments\n";
    return true;
  }
  if(argc > 4){
    std::cerr << "Too many arguments\n";
    return true;
  }
  if(argv[1][0] != '1' && argv[1][0] != '2'){
    std::cerr << "First argument is not correct\n";
    return true;
  }
  return false;
}

bool isErr2(size_t sizeArr, size_t size)
{
  if(sizeArr < size){
    std::cerr << "Not enough numbers to create array\n";
    return true;
  }
  if(sizeArr > size){
    std::cerr << "Too many numbers in file\n";
    return true;
  }
  return false;
}

bool isEmptyFile(std::ifstream & input)
{
  if(input.peek() == std::ifstream::traits_type::eof()){
    std::cerr << "Input file is empty\n";
    return true;
  }
  return false;
}

int * changeArrVar1(const int * arr, size_t n)
{
  int * arr1 = reinterpret_cast< int * >(malloc(sizeof(int) * n * n));
  if(arr1 == nullptr){
    throw std::bad_alloc();
  }
  for(size_t i = 0; i < n * n; ++i){
    arr1[i] = arr[i];
  }
  size_t lef = 0, rig = n - 1, top = 0, bot = n - 1;
  size_t cnt = 1, i = 0, j = 0;
  while(cnt < n * n){
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
  }
  arr1[i * n + j] -= cnt;
  return arr1;
}

int * changeArrVar2(const int * arr, size_t n)
{
  int * arr2 = reinterpret_cast< int * >(malloc(sizeof(int) * n * n));
  if(arr2 == nullptr){
    throw std::bad_alloc();
  }
  for(size_t i = 0; i < n * n; ++i){
    arr2[i] = arr[i];
  }
  size_t lef = 0, rig = n - 1, top = 0, bot = n - 1;
  size_t cnt = 1, i = n - 1, j = 0;
  while(cnt < n * n){
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
  }
  arr2[i * n + j] += cnt;
  return arr2;
}
