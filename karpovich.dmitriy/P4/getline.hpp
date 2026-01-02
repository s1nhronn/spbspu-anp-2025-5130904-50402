#ifndef GET_LINE
#define GET_LINE
#include <iosfwd>
namespace karpovich
{
  char* getline(std::istream& in, size_t& s);
}
#endif
