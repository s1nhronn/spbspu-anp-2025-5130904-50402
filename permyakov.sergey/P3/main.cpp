#include <iostream>
#include <fstream>
#include <memory>

bool isErr1(int argc, char ** argv);
bool isErr2(std::ifstream & input);

int main(int argc, char ** argv)
{
  if(isErr1(argc, argv)){
    return 1;
  }
  std::ifstream input(argv[2]);
  std::ofstream output(argv[3]);
  if(isErr2(input)){
    return 2;
  }
  int n = 0, m = 0;
  input >> n >> m;
  if(argv[1][0] == '1'){
    int arr[n * m] = {};
    (void) arr;
  } else {
    int * arr = reinterpret_cast< int * >(
     malloc(sizeof(int) * n * m));
    if(arr == nullptr){
      std::cerr << "Failure to allocate memory";
      return 3;
    }
  }
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

bool isErr2(std::ifstream & input)
{//файл пуст. не придумал как по другому сделать
  if(input.peek() == std::ifstream::traits_type::eof()){
    std::cerr << "Input file is empty\n";
    return true;
  }
  return false;
}
