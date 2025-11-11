#include <iostream>
#include <fstream>

void rm(int ** a, size_t r){
  if(!a){
    return;
  }
  for(size_t i = 0; i < r; ++i){
    delete[] a[i];
  }
  delete[] a;
}

void staticmtx(std::ifstream& out, int ** a, size_t r, size_t c){
  size_t cnt = 0;
  for(size_t i = 0; i < r; ++i){
    for(size_t j = 0; j < c; ++j){
      out >> a[i][j];
      if(out.eof() || out.fail()){
        throw std::logic_error("bad input");
      }
      ++cnt;
    }
  }

  if(cnt/r != c){
    throw std::logic_error("Wrong format");
  }
}

int ** dynamicmtx(std::ifstream& out, size_t r, size_t c){
  int ** a = nullptr;
  size_t cnt = 0;
  try{
    a = new int*[r];
  }catch(const std::bad_alloc &e){
    throw;
  }
  for(size_t i = 0; i < r; ++i){
      try{
        a[i] = new int[c];
      }catch(const std::bad_alloc &e){
        rm(a,i);
        throw;
      }
    }
  for(size_t i = 0; i < r; ++i){
    for(size_t j = 0; j < c; ++j){
      out >> a[i][j];
      if(out.fail()){
        rm(a, r);
        throw std::logic_error("bad input");
      }
      ++cnt;
    }
  }
  if(cnt/r != c){
    throw std::logic_error("wrong format");
  }
  return a;
}

int ** create(int pr, std::ifstream& out, int ** mtx, size_t r, size_t c){
  out >> r >> c;
  if(std::cin.fail()){
    throw std::logic_error("Wrong format");
  }
  if(pr == 1){
    staticmtx(out,mtx,r,c);
  }else{
    mtx = dynamicmtx(out,r,c);
  }
  return mtx;
}

void doall(int pr, const char * outf, const char * inf){
  std::ifstream out;
  out.open(outf);
  if(!out.is_open()){
    throw std::logic_error("Cannot open out file\n");
  }
  out.clear();
  out.seekg(0);
  int ** mtx = nullptr;
  /*
  dosmth
  */
  out.close();
  std::ofstream in;
  in.open(inf);
  if(!in.is_open()){
    
    throw std::logic_error("Cannot open in file\n");
  }
  in.close();
  /*
  все созданное удаляется здесь
  */
}

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
