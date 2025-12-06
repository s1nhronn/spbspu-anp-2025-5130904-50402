#include <iostream>

namespace karpovich
{
  struct point_t
  {
    double x, y;
  };
  struct rectangle_t
  {
    double width, height, pos;
  };
  struct Shape
  {
    double getArea();
    double getFrameRect();
    void move();
    void scale();
  };
  struct Rectangle: Shape
  {

  };
}

int main()
{
  namespace karp = karpovich;
}