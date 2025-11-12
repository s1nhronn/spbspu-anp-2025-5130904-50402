#include <iostream>
#include <fstream>

bool isErr(int argc, char ** argv)
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
  if(input.fail()){
    std::cerr << "Third argument does not exist between files\n";
    return true;
  }
  return false;
}

int main(int argc, char ** argv)
{
  if(isErr(argc, argv)){
    return 1;
  }
  return 0;
}
