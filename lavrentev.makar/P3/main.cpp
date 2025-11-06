#include <fstream>
#include <iostream>

int main(int argc, char **argv)
{
  if (argc != 4)
  {
    std::cerr << "Input error" << "\n";
    return 1;
  }

  std::ifstream input(argv[2]);

  int x, y;
  input >> x >> y;
  int total = x * y;
  int *arr = (int *)malloc(total * sizeof(int));
  if (arr == nullptr)
  {
    std::cerr << "Memory allocation fail" << "\n";
    return 1;
  }
  int size_arr = 0;
  for (size_t i = 0; i < total; ++i)
  {
    try
    {
      int k;
      input >> k;
      arr[i] = k;
      ++size_arr;
    } catch (const std::invalid_argument &)
    {
      free(arr);
      std::cerr << "Uncorrect file" << "\n";
      return 2;
    }
  }
  input.close();

  if (size_arr != total)
  {
    free(arr);
    std::cerr << "Uncorrect file" << "\n";
    return 2;
  }

  int ans_2 = 0;
  for (size_t i = y + 1; i < total - y; ++i)
  {
    try
    {
      if ((arr[i] < arr[i + 1]) && (arr[i] < arr[i - 1]) &&
          (arr[i] < arr[i + y]) && (arr[i] < arr[i - y]) &&
          (arr[i] < arr[i + y + 1]) && (arr[i] < arr[i - y - 1]) &&
          (arr[i] < arr[i + y - 1]) && (arr[i] < arr[i - y + 1]))
          {
        ans_2 += 1;
      }
    } catch (const std::out_of_range &)
    {
      continue;
    }
  }

  free(arr);
}