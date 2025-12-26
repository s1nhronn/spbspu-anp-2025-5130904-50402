#include <iostream>
#include <cctype>

namespace strelnikov {

  using std::free;
  char* addSymb(const char* str, size_t& s, char ch)
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
      char* tmp = addSymb(res, s, ch);
      free(res);
      if (tmp == nullptr) {
        if (isSkipWp) {
          in >> std::skipws;
        }
        return nullptr;
      }
      res = tmp;
    }

    if (in.fail() && !in.eof()) {
      free(res);
      if (isSkipWp) {
        in >> std::skipws;
      }
      return nullptr;
    }
    if (isSkipWp) {
      in >> std::skipws;
    }
    return res;
  }

  char* getStringForDgtSnd(const char* str, size_t& mod)
  {
    size_t size = 0;
    char* res = nullptr;
    for (size_t i = 0; str[i] != '\0'; ++i) {
      if (std::isdigit(static_cast< unsigned char >(str[i]))) {
        char* tmp = addSymb(res, size, str[i]);
        free(res);
        if (tmp == nullptr) {
          return nullptr;
        }
        res = tmp;
      }
    }
    mod = size;
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

  void doDgtSnd(char* resultBuffer, const char* str1, const char* digits)
  {
    size_t i = 0;
    while (str1[i] != '\0') {
      resultBuffer[i] = str1[i];
      ++i;
    }

    size_t j = 0;
    while (digits[j] != '\0') {
      resultBuffer[i + j] = digits[j];
      ++j;
    }
    resultBuffer[i + j] = '\0';
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
  size_t dgt_size = 0;
  char* dgt = strelnikov::getStringForDgtSnd(strDgt, dgt_size);
  if (!dgt) {
    std::free(str1);
    std::free(dgt);
    return 1;
  }
  char* resultBuffer = reinterpret_cast< char* >(std::malloc(s1 + dgt_size + 1));
  resultBuffer[s1+dgt_size] = '\0';
  strelnikov::doDgtSnd(resultBuffer, str1, dgt);
  std::cout << hasCommon << '\n' << resultBuffer << '\n';
  std::free(str1);
  std::free(dgt);
  std::free(resultBuffer);
  return 0;
}
