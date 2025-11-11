#include <iostream>
#include <string>

void doall(int pr, const char * outf, const char * inf);

int main(int argc, char const *argv[]){
  int ex_code = 0;
  if(argc != 4){
    if(argc > 4){

    }else{
      std::cerr << "Too few arguments\n";
    }
    ex_code = 1;
  }else{
    int pr;
    try{
      pr = std::stoi(argv[1]);
    } catch (const std::invalid_argument& e) {
      std::cerr << "First argument is not a number\n";
      ex_code = 1;
    } catch (const std::out_of_range& e) {
      std::cerr << "First argument is out of range\n";
      ex_code = 1;
    }
    if(ex_code == 0){
      if( pr != 1 && pr != 2){
        std::cerr << "First argument is out of range\n";
        ex_code = 1;
      }
    }
    if(ex_code == 0){
      try{
        //doall(pr, argv[2], argv[3]);
      }catch(...){
        ex_code = 3;
      }
    }
  }
  return ex_code;
}
