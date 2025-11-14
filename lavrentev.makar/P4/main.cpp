#include <iostream>
#include <cstring>

size_t dif_lat(std::string s);
std::string uni_two(std::string s);
char * del(char * a, char * b, char el);

int main()
{
  std::string s;
  std::getline(std::cin, s);

  int ans_7 = dif_lat(s);
  std::string ans_12 = uni_two(s);




  
  std::cout << "Ans 7: " << ans_7 << "\n";
  std::cout << "Ans 12: " << ans_12 << "\n";
}

size_t dif_lat(std::string s){
  size_t ex = s.size();

  size_t answer = 0;

  char * ans = new char[ex];
  if (ans == nullptr)
  {
    std::cerr << "Memory allocation fail" << "\n";
    return 1;
  }

  for(size_t i = 0; i < ex; ++i){
    ans[i] = '#';
  }

  char * repeat = new char[ex];
  if (repeat == nullptr)
  {
    std::cerr << "Memory allocation fail" << "\n";
    return 1;
  }

  for(size_t i = 0; i < ex; ++i){
    repeat[i] = '#';
  }

  for(size_t i = 0; i < ex; ++i){
    bool flag = false;
    for(size_t j = 0; j < ex; ++j){
      if(ans[j] == s[i]){
        flag = true;
        break;
      }
    }

    if(flag){
      repeat[i] = s[i];
    }else{
      ans[i] = s[i];
    }
   
  }

  for(size_t i = 0; i < ex; ++i){
    bool flag = true;
    for(size_t j = 0; j < ex; ++j){
      if(repeat[j] != ans[i] && ans[i] != '#'){
        continue;
      }else{
        flag = false;
        break;
      }
    }
    if(flag){
      ++answer;
    }
  }
  delete[] ans;
  delete[] repeat;

  return answer;
}

char * del(char * a, char * b, char el){

}
