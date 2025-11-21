#include <iostream>
#include <iomanip>
namespace karpovich
{
  char* getline(std::istream& in, size_t& s)
  {
    bool is_skipws = in.flags() & std::ios_base::skipws;
    char* str = nullptr;
    char ch = 0;
    if (is_skipws) {
      in >> std::noskipws;
    }
    while (in >> ch && ch != '\n') {
      char* temp = reinterpret_cast< char* >(malloc(s + 1));
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
    char* temp = reinterpret_cast< char* >(malloc(s + 1));
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
  void repsym(const char* str, char* data, const size_t size)
  {
    size_t MAX_ascii = 256;
    if (!str || !data) {
      data[0] = 0;
      return;
    }

    int repeat[MAX_ascii] = {};
    for (size_t i = 0; i < size && str[i] != 0; ++i) {
      unsigned char c = static_cast< unsigned char >(str[i]);
      ++repeat[c];
    }

    int saw[MAX_ascii] = {};
    size_t pos = 0;
    for (size_t i = 0; i < size && str[i] != 0; ++i) {
      unsigned char c = static_cast< unsigned char >(str[i]);
      if (repeat[c] > 1 && saw[c] == 0) {
        data[pos++] = c;
        saw[c] = 1;
      }
    }
    data[pos] = 0;
  }
  void unitwo(const char* str1, const char* str2, const size_t s1, const size_t s2, char* data)
  {
      if (!str1 || !str2 || !data) {
          data[0] = 0;
          return;
      }

      size_t i = 0, j = 0, k = 0;
      while (i < s1 && j < s2) {
          data[k++] = str1[i++];
          data[k++] = str2[j++];
      }
      while (i < s1) {
        data[k++] = str1[i++];
      }
      while (j < s2) {
        data[k++] = str2[j++];
      }
      data[k] = 0;
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

  char* data = reinterpret_cast< char* >(malloc(s + 1));
  if (!data) {
    free(str);
    std::cerr << "Failed to alloc memory";
    return 1;
  }
  karp::repsym(str, data, s);


  size_t s2 = 4;
  const char* str2 = "def ";

  char* data2 = reinterpret_cast< char* >(malloc(s + s2 + 1));
  if (!data2) {
    std::free(data);
    std::free(str);
    std::cerr << "Failed to alloc memory";
    return 1;
  }
  karp::unitwo(str, str2, s, s2, data2);

  std::cout << data << '\n';
  std::cout << data2 << '\n';

  free(data2);
  free(str);
  free(data);
  return 0;
}
