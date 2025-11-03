#include <iostream>
#include <fstream>

void output(const int * a, size_t c, size_t r);

int main (int argc, char ** argv)
{
  // checking the number of parameters
  if (argc < 4)
  {
    std::cerr << "Mismatch in the number of parameters\n";
    return 1;
  {

  // reading file_1: memory allocation
    std::ifstream input(argv[2]);
  if (!input.is_open())
  {
    std::cerr << "Failed to read file\n";
    return 2;
  }
  int rows, cols;
  if (!(input >> rows >> cols))
  {
    std::cerr << "Failed to read matrix dimensions\n";
    return 2;
  }
  if (rows == 0 && cols == 0) {
    std::cerr << "Empty matrix\n";
    return 2;
  }
  if (rows < 0 || cols < 0) {
    std::cerr << "Invalid matrix dimensions\n";
    return 2;
  }

  // memory allocation
  if (argv[1] == "1")
  {
    int a[10000] = {};
  }
  else if (argv[1] == "2")
  {
      int* nums = reinterpret_cast<int*>(malloc(sizeof(int) * (rows * cols)));
      if (nums == nullptr)
      {
        std::cerr << "Memory allocation failed\n";
        return 2;
      }
  }
  else
  {
    std::cerr << "parameter 2 is set incorrectly";
    return 2;
  }

  // reading file_2: filling the matrix

  input.close()

  /*int a[10000] ={}'
  int * adyn = new int[rows * cols];

  argv = 1 ?*/

  std::ofstream output(argv[3]);
  output(output, ... ) << "\n"
  if (std::ofstream.fail())
  {
    return 1;
  }
  //output << a;
}

void output (std::ostream & out, const int * a, size_t c, size_t r)
{
  return out << ... ;
}
