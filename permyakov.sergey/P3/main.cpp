#include <iostream>
#include <fstream>

int main(int argc, char ** argv)
{
  if(argc < 4){
    std::cerr << "Not enough arguments\n";
    return 1;
  }
  if(!(*argv[1] == '1' || *argv[1] == '2')){
    std::cerr << "first parametr is out of range\n";
    return 1;
  }
  return 0;
}
