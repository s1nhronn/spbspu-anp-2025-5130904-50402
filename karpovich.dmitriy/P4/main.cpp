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
  void repsym(const char* str, char*& data, const size_t size) {
    if (size == 0) {
      data[0] = 0;
      return;
    }
    size_t pos = 0;
    for (size_t i = 0; i < size && str[i] != '\0'; ++i) {
      char ch = str[i];
      size_t j = 0;
      for (; j < i; ++j) {
        if (str[j] == ch) {
          break;
        }
      }
      if (j == i) {
        data[pos] = ch;
        ++pos;
      }
    }
    data[pos] = 0;
  }
}

int main() {
  namespace karp = karpovich;
  size_t s = 0;
  char* str = karp::getline(std::cin, s);
  if (!str) {
    std::cerr << "Failed to alloc memory";
    return 1;
  }
  char* data = reinterpret_cast<char*>(malloc(s + 1));
  karp::repsym(str, data, s);
  std::cout << data << '\n';
  free(str);
  free(data);
}
