#include <iostream>
#include <iomanip>
namespace karpovich
{
  char* getline(std::istream& in, size_t& s) {
    bool is_skipws = in.flags() & std::ios_base::skipws;
    char* str = nullptr;
    char ch = 0;
    if (is_skipws) {
      in >> std::noskipws;
    }
    while (in >> ch && ch != '\n') {
      char* temp = reinterpret_cast<char*>(malloc(s + 1));
      if (temp == nullptr) {
        free(str);
        if (is_skipws) {
          in >> std::skipws;
        }
        return nullptr;
      }
      for (size_t i = 0; i < s; ++i) {
        temp[i] = str[i];
      }
      free(str);
      str = temp;
      str[s] = ch;
      ++s;
    }
    if (in.fail() && s == 0 && ch != '\n') {
      free(str);
      if (is_skipws) {
        in >> std::skipws;
      }
      return nullptr;
    }
    char* temp = reinterpret_cast<char*>(malloc(s + 1));
    if (temp == nullptr) {
      free(str);
      if (is_skipws) {
        in >> std::skipws;
      }
      return nullptr;
    }
    for (size_t i = 0; i < s; ++i) {
      temp[i] = str[i];
    }
    free(str);
    str = temp;
    str[s] = 0;
    if (is_skipws) {
      in >> std::skipws;
    }
    return str;
  }
}

int main() {
  namespace karp = karpovich;
  size_t s = 0;
  char* str = karp::getline(std::cin, s);
  if (!str) {
    std::cerr << "Faled to alloc memory";
    return 1;
  }
  std::cout << str << '\n' << s << '\n';
  free(str);
}
