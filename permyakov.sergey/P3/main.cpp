#include <iostream>
#include <fstream>
#include <memory>

bool isErr1(int argc, char ** argv);
bool isErr2(int sizeArr, int size);
bool isEmptyFile(std::ifstream & input);
void coutArr(int * a, int s)
{
  for(int i = 0; i < s; ++i){
    std::cout << a[i] << " ";
  }
  std:: cout << "\n";
}

int main(int argc, char ** argv)
{
  if(isErr1(argc, argv)){
    return 1;
  }

  std::ifstream input(argv[2]);
  std::ofstream output(argv[3]);
  if(isEmptyFile(input)){
    return 2;
  }
  int n = 0, m = 0;
  input >> n >> m;
  if(input.fail()){
    if(input.eof()){
      std::cerr << "Missing size of array\n";
    } else {
      std::cerr << "Invalid format of size\n";
    }
    return 2;
  }

  int * arr = reinterpret_cast< int * >(malloc(sizeof(int) * n * m));
  if(arr == nullptr){
    std::cerr << "Failure to allocate memory\n";
    return 3;
  }

  int s = 0;
  for(int n = 0; input >> n; ++s){
    arr[s] = n;
  }
  if(!input.eof()){
    std::cerr << "Invalid array format\n";
    free(arr);
    return 2;
  }
  if(isErr2(s, n * m)){
    free(arr);
    return 2;
  }
  coutArr(arr, n * m);
  return 0;
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
  std::ifstream input(argv[2]);
  if(input.fail()){
    std::cerr << "Second argument does not exist between files\n";
    return true;
  }
  std::ifstream output(argv[3]);
  if(output.fail()){
    std::cerr << "Third argument does not exist between files\n";
    return true;
  }
  return false;
}

bool isErr2(int sizeArr, int size)
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
{//конец файла. не придумал как по другому сделать
  if(input.peek() == std::ifstream::traits_type::eof()){
    std::cerr << "Input file is empty\n";
    return true;
  }
  return false;
}
