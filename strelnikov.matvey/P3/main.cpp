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

void lftBotCnt(int** mtx, int r, int c){

}

size_t cntNzrDig(int ** mtx, size_t r, size_t c){
  size_t min = (r < c)?r:c;
  int cnt = 0;
  for (size_t i = 1; i < min; ++i) {
    int tr = 1;
    size_t ecri = i;
    for (size_t j = 0; j < min - i; ++j) {
      if (mtx[j][ecri] == 0) {
        tr = 0;
      }
      ++ecri;
    }
    cnt += tr;
  }
  for (size_t i = 1; i < min; ++i) {
    size_t ecri = i;
    int tr = 1;
    for (size_t j = 0; j < min - i; ++j) {
      if (mtx[ecri][j] == 0) {
        tr = 0;
      }
      ++ecri;
    }
    cnt += tr;
  }
  return cnt;
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

void doall(int pr, const char * outf, const char * inf){
  std::ifstream out;
  out.open(outf);
  if(!out.is_open()){
    throw std::logic_error("Cannot open out file\n");
  }
  out.clear();
  out.seekg(0);
  int ** mtx = nullptr;
  size_t r, c;
  out >> r >> c;
  if(std::cin.fail()){
    throw std::logic_error("Wrong format");
  }
  try{
    if(pr == 1){
      staticmtx(out,mtx,r,c);
    }else{
      mtx = dynamicmtx(out,r,c);
    }
  }catch(const std::logic_error &e){
    rm(mtx, r);
    throw;
  }
  out.close();
  std::ofstream in;
  in.open(inf);
  if(!in.is_open()){
    throw std::logic_error("Cannot open in file\n");
  }
  size_t dig = cntNzrDig(mtx, r, c);
  in << dig;
  lftBotCnt(mtx, r, c);
  for(size_t i = 0; i < r; ++i){
    for(size_t j = 0; j < r; ++j){
      in << mtx[i][j] << ' ';
    }
    std::cout << '\n';
  }
  in.close();
  rm(mtx, r);
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
