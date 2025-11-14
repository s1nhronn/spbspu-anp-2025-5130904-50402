#include <iostream>
#include <cstring>

size_t dif_lat(char * ans, std::string s);
std::string uni_two(std::string s);
char * del(char * a, char * b, char el);

int main()
{
  std::string s;
  std::getline(std::cin, s);

  size_t ex = s.size();
  char * ans = new char[ex];
  if (ans == nullptr)
  {
    std::cerr << "Memory allocation fail" << "\n";
    return 1;
  }

  int ans_7 = dif_lat(ans, s);

  //std::string ans_12 = uni_two(s);

  std::cout << "Ans 7: " << ans_7 << "\n";
  //std::cout << "Ans 12: " << ans_12 << "\n";

  delete[] ans;
}

size_t dif_lat(char * ans, std::string s){
  size_t ex = s.size();

  size_t answer = 0;

  for(size_t i = 0; i < ex; ++i){
    ans[i] = '#';
  }

  for(size_t i = 0; i < ex; ++i){
    bool flag = false;
    for(size_t j = 0; j < ex; ++j){
      if(ans[j] == s[i]){
        flag = true;
        break;
      }
    }

    int k = s[i];
    if(!flag && k ){
      ans[i] = s[i];
    }
   
  }

  for(size_t i = 0; i < ex; ++i){
    if(ans[i] != '#'){
      ++answer;
    }
  }
  
  return answer;
}

char * del(char * a, char * b, char el){

}
