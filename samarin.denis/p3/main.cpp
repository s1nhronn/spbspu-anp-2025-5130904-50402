#include<fstream>;
#include <iostream>

int loc_max_fixed(char * file_name);
int loc_max_dynamic(char * file_name);

int main(int argc, char ** argv) {
  int m = 0;
  int n = 0;

  std::ifstream input("input.txt");
  input >> m >> n;

  if (argv[0] == '1') {
    int a[10000] = {};
  }
  else if (argv[0] == '1') {
    int * a = nullptr;
    int * a = reinterpret_cast<int*>(malloc(sizeof(int) * n * m));
    if (a == nullptr) {
      std::cerr << "Bad alloc" << '\n';
      return 2;
    }
  }
  int counter = 0;
  size_t i = 0;
  while (input.good() && i < n*m) {
    input >> b;
    a[i] = b;
    ++i;
  }
  for (int i = 0; i < m; ++i) {
    for (int j = 0; j < n; ++j) {
      if (i != 0 && j != 0 && check_max(a, i, j, n, m)) {
        counter++;
      }
    }
  }
}

//функция для статической памяти
bool check_max(int a[], size_t i, size_t j, size_t n, size_t m) {
  check_i = i-1;
  check_j = j-1;
  for (; check_i < i+2; check_i++) {
    for (; check_j < j+2; check_j++) {
      if (a[check_j + check_i * n] >= a[j + i * n] && !(check_i == i && check_j == j)) {
        return false;
      }
    }
  }
  return true;
}

//функция для динамической памяти
bool check_max(int * a, size_t i, size_t j, size_t n, size_t m) {
  check_i = i-1;
  check_j = j-1;
  for (; check_i < i+2; check_i++) {
    for (; check_j < j+2; check_j++) {
      if (a[check_j + check_i * n] >= a[j + i * n] && !(check_i == i && check_j == j)) {
        return false;
      }
    }
  }
  return true;
}