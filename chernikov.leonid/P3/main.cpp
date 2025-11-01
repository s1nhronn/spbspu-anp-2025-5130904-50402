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
  if (std::ifstream.fail())
  {
    std::cerr << "Failed to read file\n";
    return 1;
  }
  char size[3] = {};
  for (int i = 0; i < 3; ++i)
  {
    char ch;
    if (file.get(ch))
    {
      size[i] = ch;
    }
    else
    {
      std::cerr << "failed to count the character\n"
      return 2;
    }
  }
  int rows = static_cast<int>(size[0]);
  int cols = static_cast<int>(size[2]);
  argv[1] = 1 ? int a[10000] = {} : int * adyn = new int[rows * cols];

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
