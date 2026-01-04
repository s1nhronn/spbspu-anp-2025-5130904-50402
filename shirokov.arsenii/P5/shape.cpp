#include "shape.hpp"
#include <stdexcept>

void shirokov::Shape::doScale(double coefficient)
{
  if (coefficient <= 0)
  {
    throw std::logic_error("The coefficient cannot be negative");
  }
  scale(coefficient);
}
