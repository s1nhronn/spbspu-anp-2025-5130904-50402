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

int doHasSam(char* str1, size_t s1, char* str2, size_t s2)
{
  for (size_t i = 0; i < s1; ++i) {
    for (size_t j = 0; j < s2; ++j) {
      if (str1[i] = str2[j]) {
        return 1;
      }
    }
  }
  return 0;
}

char* doDgtSnd(char* str1, size_t s1, char* str2, size_t s2)
{
  char* a = nullptr;
  size_t size = 0;
  for (size_t i = 0; i < s2; ++i) {
    if (isdigit(str2[i])) {
      char* tmp = reinterpret_cast<char*>(malloc(size + 1));
      if (!tmp) {
        if (a) {
          free(a);
        }
        std::cerr << "Bad alloc\n";
        return nullptr;
      }
      for (size_t j = 0; j < size; ++j) {
        tmp[j] = a[j];
      }
      tmp[size] = str2[i];
      if (a) {
        free(a);
      }
      a = tmp;
      ++size;
    }
  }

  char* res = reinterpret_cast<char*>(malloc(s1 + size));
  if (!res) {
    if (a) {
      free(a);
    }
    return nullptr;
  }
  for (size_t i = 0; i < s1; ++i) {
    res[i] = str1[i];
  }
  for (size_t i = s1; i < s1 + size; ++i) {
    res[i] = a[i - s1];
  }
  if (a) {
    free(a);
  }
  return res;
}

int main()
{
  size_t s1 = 0, s2 = 0; 
  char* str1 = nullptr, *str2 = nullptr; 
  try { 
    str1 = getString(std::cin, s1);
  } catch (const std::bad_alloc& e){
    std::cerr << e.what() << '\n';
    return 1;
  } catch (const std::logic_error& e) {
    std::cerr << e.what() << '\n';
    return 2;
  } 

  try {
    str2 = getString(std::cin, s2);
  } catch (const std::bad_alloc& e) { 
    std::cerr << e.what() << '\n';
    return 1;
  } catch (const std::logic_error& e) {
    std::cerr << e.what() << '\n';
    return 2;
  } 
  int hasCommon = doHasSam(str1, s1, str2, s2);
  std::cout << hasCommon << '\n';
  char* result2 = doDgtSnd(str1, s1, str2, s2);
  if (!result2) {
    std::cerr << "Memory allocation failed\n";
    free(str1);
    return 1;
  }
  std::cout << result2 << '\n';
  free(str1);
  free(result2);
  return 0;
}
