#include <iostream>
#include <iomanip>
#include <cctype>
namespace petrov
{
  char* getLine(std::istream& input, size_t& lenght) {
    bool skipWs = input.flags() & std::ios::skipws;
    if(skipWs) {
      input >> std::noskipws;
    }
    char* resStr = nullptr;
    char tmp = ' ';
    while ( input >> tmp && tmp != '\n') {
      char* tmpStr = static_cast< char* >(realloc(resStr, lenght+2));
      if (tmpStr == nullptr) {
        free(resStr);
        throw std::bad_alloc();
      }
      resStr = tmpStr;
      resStr[lenght++] = tmp;
    }
    if (input.fail() && !input.eof()) {
      free(resStr);
      throw std::logic_error("Invalid reading\n");
    }
    if (skipWs) {
      input >> std::skipws;
    }
    if (resStr != nullptr) {
      resStr[lenght] = '\0';
    }
    return resStr;
  }
  void duplicateForUncSym(const char* str1, const char* str2, char* result, size_t& place) {
    for(size_t i = 0; str1[i] != '\0'; ++i) {
      bool flag1 = false;
      for (size_t j = 0; str2[j] != '\0'; ++j) {
        if (str1[i] == str2[j]) {
          flag1 = true;
          break;
        }
      }
      if(!flag1) {
        bool flag2 = false;
        for (size_t k = 0; k < place; ++k) {
          if (result[k] == str1[i]) {
            flag2 = true;
            break;
          }
        }
        if (!flag2) {
          result[place++] = str1[i];
        }
      }
    }
  }

  void doUncSym(const char* str1, const char* str2, char* result) {
    size_t place = 0;
    duplicateForUncSym(str1, str2, result, place);
    duplicateForUncSym(str2, str1, result, place);
    result[place] = '\0';
  }

  size_t doSeqSym(const char* str) {
    if (str == nullptr || str[0] == '\0') {
      return 0;
    }
    for (size_t i = 1; str[i] != '\0'; ++i) {
      if (str[i] == str[i-1]) {
        return 1;
      }
    }
    return 0;
  }
}

int main()
{
  char* str = nullptr;
  size_t len = 0;
  try {
    str = petrov::getLine(std::cin, len);
  } catch (const std::logic_error& e) {
    std::cerr << e.what() << "\n";
    return 1;
  } catch (const std::bad_alloc& e) {
    std::cerr << "Bad alloc error\n";
    return 1;
  }
  const char* sec_str = "abc ef";
  char* ansUncSym = static_cast< char* >(malloc(len+7));
  if (ansUncSym == nullptr) {
    std::cerr << "Alloc failed\n";
    free(str);
    return 1;
  }
  petrov::doUncSym(str, sec_str, ansUncSym);
  size_t ansSeqSym = petrov::doSeqSym(str);
  std::cout << ansUncSym << "\n";
  std::cout << ansSeqSym << "\n";
  free(str);
  free(ansUncSym);
  return 0;
}
