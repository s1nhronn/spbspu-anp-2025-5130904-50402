#include <iostream>
#include <cctype>

void addSymb(char*& str, size_t& s, char ch)
{
  char* tmp = reinterpret_cast<char*>(malloc(s + 1));
  if (tmp == nullptr) {
    if (str) {
      free(str);
    }
    throw std::bad_alloc();
  }

  for (size_t i = 0; i < s; ++i) {
    tmp[i] = str[i];
  }
  if (str) {
    free(str);
  }
  str = tmp;
  str[s] = ch;
  ++s;
}

char* getString(std::istream& in, size_t& s)
{
  bool isSkipWp = in.flags() & std::ios::skipws;
  if (isSkipWp) {
    in >> std::noskipws;
  }
  char* res = nullptr;
  char ch;
  while (in >> ch) {
    if (ch == '\n') {
      break;
    }
    try {
      addSymb(res, s, ch);
    } catch (const std::exception& e) {
      if (res) {
        free(res);
      }
      throw;
    }
  }

  if (in.fail() && !in.eof()) {
    throw std::logic_error("In fail");
  }
  try {
    addSymb(res, s, '\0');
  } catch (const std::exception& e) {
    if (res) {
      free(res);
    }
    throw;
  }

  return res;
}

int doHasSam(char * str1, size_t s1, char * str2, size_t s2){
  for(size_t i = 0; i < s1; ++i){
    for(size_t j = 0; j < s2; ++j){
      if(str1[i] = str2[j]){
        return 1;
      }
    }
  }
  return 0;
}

void doDgtSnt();

int main()
{
  size_t s = 0;
  char* str = nullptr;
  try {
    str = getString(std::cin, s);
  } catch (const std::exception& e) {
    std::cerr << e.what() << '\n';
    return 2;
  }

  for (size_t i = 0; i < s; ++i) {
    std::cout << str[i];
  }
  std::cout << '\n' << s << '\n';
  if (str) {
    free(str);
  }
  return 0;
}
