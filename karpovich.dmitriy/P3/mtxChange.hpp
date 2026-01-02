#ifndef MTX_CHANGE
#define MTX_CHANGE
#include <iosfwd>
namespace karpovich
{
  size_t locMin(const int* arrdyn, size_t rows, size_t cols);
  void lftTopClk(int* arrdyn, size_t rows, size_t cols);
}
#endif
