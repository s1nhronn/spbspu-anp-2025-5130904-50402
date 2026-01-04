#ifndef SHAPE_HPP
#define SHAPE_HPP
#include "pods.hpp"

namespace shirokov
{
  struct Shape
  {
    virtual ~Shape() = default;
    virtual double getArea() const noexcept = 0;
    virtual rectangle_t getFrameRect() const noexcept = 0;
    virtual void move(point_t target) noexcept = 0;
    virtual void move(double x, double y) noexcept = 0;
    void doScale(double coefficient);

  private:
    virtual void scale(double coefficient) noexcept = 0;
  };
}

#endif
