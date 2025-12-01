#include <iostream>
#include <cctype>

namespace strelnikov {

  char * addSymb(char* str, size_t& s, char ch)
  {
    char* tmp = reinterpret_cast< char* >(malloc(s + 2));
    if (tmp == nullptr) {
      return nullptr;
    }

    for (size_t i = 0; i < s; ++i) {
      tmp[i] = str[i];
    }

    tmp[s] = ch;
    tmp[s + 1] = '\0';

    ++s;
    free(str);
    return tmp;
  }

  char* getString(std::istream& in, size_t& s)
  {
    bool isSkipWp = in.flags() & std::ios::skipws;
    if (isSkipWp) {
      in >> std::noskipws;
    }
    char* res = nullptr;
    s = 0;

    char ch;
    while (in >> ch && ch != '\n') {
      res = addSymb(res, s, ch);
      if(res == nullptr){
        return nullptr;
      }
    }

    if (in.fail() && !in.eof()) {
      free(res);
      return nullptr;
    }

    return res;
  }

  int doHasSam(char* str1, char* str2)
  {
    for (size_t i = 0; str1[i] != '\0'; ++i) {
      for (size_t j = 0; str2[j] != '\0'; ++j) {
        if (str1[i] == str2[j]) {
          return 1;
        }
      }
    }
    return 0;
  }

  char* doDgtSnd(const char* str1, size_t s1, const char* str2, size_t s2)
  {
    char* a = nullptr;
    size_t cnt = 0;

    for (size_t i = 0; i < s2; ++i) {
      if (std::isdigit(static_cast< unsigned char >(str2[i]))) {
        try {
          a = addSymb(a, cnt, str2[i]);
        } catch (const std::bad_alloc& e) {
          free(a);
          return nullptr;
        }
      }
    }

    char* res = reinterpret_cast< char* >(malloc(s1 + cnt + 1));
    if (!res) {
      free(a);
      return nullptr;
    }

    for (size_t i = 0; i < s1; ++i) {
      res[i] = str1[i];
    }
    for (size_t i = 0; i < cnt; ++i) {
      res[s1 + i] = a[i];
    }

    res[s1 + cnt] = '\0';
    free(a);
    return res;
  }
}

int main()
{
  size_t s1 = 0;
  char* str1 = strelnikov::getString(std::cin, s1);
  if(str1 == nullptr || s1 == 0){
    return 1;
  }
  char strHas[] = "abc";
  int hasCommon = strelnikov::doHasSam(str1, strHas);
  std::cout << hasCommon << '\n';
  char strDgt[] = "g1h2k";
  char* result2 = strelnikov::doDgtSnd(str1, s1, strDgt, 5);
  if (result2 == nullptr) {
    free(str1);
    return 1;
  }

  std::cout << result2 << '\n';

  free(str1);
  free(result2);
  return 0;
}
