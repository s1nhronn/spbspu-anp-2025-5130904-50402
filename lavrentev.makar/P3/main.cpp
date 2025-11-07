#include <fstream>
#include <iostream>

int main(int argc, char **argv)
{
  /*int q = static_cast<int>(argv[1]);
  if(argv[1] != '1' || argv[1] != '2')
  {

  }*/
  if (argc != 4)
  {
    std::cerr << "Input error" << "\n";
    return 1;
  }

  std::ifstream input(argv[2]);

  size_t x, y;
  input >> x >> y;
  size_t total = x * y;
  int total_for_memory = static_cast<int>(x) * static_cast<int>(y);
  int *arr = static_cast<int*>(malloc(total_for_memory * sizeof(int)));
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

  if (size_arr != total_for_memory)
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

  int ans_11 = 0;

  int mas[y][2];
  for (size_t i = 0; i < y; ++i)
  {
    mas[i][0] = -1;
    mas[i][1] = 0;
  }

  for (size_t i = 0; i < total; ++i)
  {
    size_t j = i % y;
    if (mas[j][0] == -1)
    {
      mas[j][0] = j + 1;
      mas[j][1] = 1;
    }else
    {
      if (arr[i] == arr[i - y])
      {
        ++mas[j][1];
      } else
      {
        if(mas[j][1] > ans_11)
        {
          ans_11 = mas[j][1];
        }
        mas[j][1] = 1;
      }
    }
  }
  
  for (size_t i = 0; i < y; ++i)
  {
    if (ans_11 < mas[i][1])
    {
      ans_11 = mas[i][1];
    }
  }

  std::ofstream output;
  output.open(argv[3]);

  output << "Answer for var_2: " << ans_2 << "\n";
  output << "Answer for var_11: " << ans_11 << "\n";

  free(arr);
}
