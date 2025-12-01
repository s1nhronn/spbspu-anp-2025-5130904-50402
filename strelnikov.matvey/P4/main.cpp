#include <iostream>
#include <cctype>

namespace strelnikov {

  char* addSymb(char* str, size_t& s, char ch)
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
      if (res == nullptr) {
        return nullptr;
      }
    }

    if (in.fail() && !in.eof()) {
      free(res);
      return nullptr;
    }

    return res;
  }

  char* getStringForDgtSnd(const char* str, size_t& size)
  {
    char* res = nullptr;

    for (size_t i = 0; str[i] != '\0'; ++i) {
      if (std::isdigit(static_cast< unsigned char >(str[i]))) {
        res = addSymb(res, size, str[i]);
        if (res == nullptr) {
          return nullptr;
        }
      }
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

  void doDgtSnd(char* res, size_t size, const char* str)
  {
    size_t i = 0;
    for (i; str[i] != '\0'; ++i) {
      res[size + i] = str[i];
    }
    res[size + i] = '\0';
  }
}

int main()
{
  size_t s1 = 0;
  char* str1 = strelnikov::getString(std::cin, s1);
  if (str1 == nullptr || s1 == 0) {
    return 1;
  }
  char strHas[] = "abc";
  int hasCommon = strelnikov::doHasSam(str1, strHas);

  char strDgt[] = "g1h2k";
  size_t size = 0;
  char* str2 = strelnikov::getStringForDgtSnd(strDgt, size);
  char* resultBuffer = nullptr;
  if (size != 0) {
    resultBuffer = reinterpret_cast< char* >(malloc(s1 + size + 1));
    if (resultBuffer == nullptr) {
      free(str1);
      free(str2);
      return 1;
    }
    for (size_t i = 0; i < s1; ++i) {
      resultBuffer[i] = str1[i];
    }
    strelnikov::doDgtSnd(resultBuffer, s1, str2);
  }

  std::cout << hasCommon << '\n' << ((size > 0) ? resultBuffer : str1) << '\n';

  free(str1);
  free(str2);
  free(resultBuffer);
  return 0;
}
