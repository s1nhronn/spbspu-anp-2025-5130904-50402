#include <iostream>
#include <cctype>

void addSymb(char*& str, size_t& s, char ch)
{
  char* tmp = reinterpret_cast<char*>(malloc(s + 2));
  if (tmp == nullptr) {
    if (str) {
      free(str);
    }
    throw std::bad_alloc();
  }

  for (size_t i = 0; i < s; ++i) {
    tmp[i] = str[i];
  }

  tmp[s] = ch;
  tmp[s + 1] = '\0';

  if (str) {
    free(str);
  }

  str = tmp;
  ++s;
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
  while (in >> ch) {
    if (ch == '\n') {
      break;
    }
    try {
      addSymb(res, s, ch);
    } catch (const std::bad_alloc& e) {
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
    --s;
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
    if (isdigit(static_cast<unsigned char>(str2[i]))) {
      try {
        addSymb(a, cnt, str2[i]);
      } catch (const std::bad_alloc& e) {
        free(a);
        return nullptr;
      }
    }
  }

  char* res = reinterpret_cast<char*>(malloc(s1 + cnt + 1));
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

int main()
{
  size_t s1 = 0, s2 = 0;
  char *str1 = nullptr, *str2 = nullptr;
  try {
    str1 = getString(std::cin, s1);
    str2 = getString(std::cin, s2);
  } catch (const std::bad_alloc& e) {
    std::cerr << e.what() << "\n";
    if (str1) {
      free(str1);
    }
    if (str2) {
      free(str2);
    }
    return 1;
  } catch (const std::logic_error& e) {
    std::cerr << e.what() << "\n";
    if (str1) {
      free(str1);
    }
    if (str2) {
      free(str2);
    }
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
  free(str2);
  free(result2);
  return 0;
}
