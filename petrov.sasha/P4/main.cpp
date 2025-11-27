#include <iostream>
#include <iomanip>
#include <cctype>
namespace petrov
{
  char* getLine(std::istream& input) {
    size_t lenght = 0;
    bool skipWs = input.flags() & std::ios::skipws;
    if(skipWs) {
      input >> std::noskipws;
    }
    char* resStr = nullptr;
    char tmp = ' ';
    while ( input >> tmp && tmp != '\n') {
      char* tmpStr = static_cast< char* >(realloc(resStr, lenght+1));
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
    resStr[lenght] = '\0';
    return resStr;
  }

  char* doUncSym() {
  
  }

  size_t doSeqSym() {
  
  }
}

int main()
{
  char* str = nullptr;
  try {
    str = petrov::getLine(std::cin);
  } catch (const std::logic_error& e) {
    std::cerr << e.what() << "\n";
    return 1;
  }
}
