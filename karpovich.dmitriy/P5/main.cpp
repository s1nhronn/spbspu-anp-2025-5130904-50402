#include <iostream>

namespace karpovich
{
  constexpr double PI = 3.14;
  struct point_t
  {
    double x, y;
  };
  struct rectangle_t
  {
    double width, height;
    point_t pos;
  };
  struct Shape
  {
    virtual double getArea() const = 0;
    virtual rectangle_t getFrameRect() const = 0;
    virtual void move(point_t p) = 0;
    virtual void move(double dx, double dy) = 0;
    virtual void scale(double k) = 0;
  };
  struct Rectangle: Shape
  {
    Rectangle(double width, double height, point_t centr);
    double getArea() const override;
    rectangle_t getFrameRect() const override;
    void move(double dx, double dy) override;
    void move(point_t p) override;
    void scale(double k) override;
    private:
      double width_, height_;
      point_t centr_;
  };
  struct Rubber: Shape
  {
    Rubber(double radius1, double radius2, point_t centr1, point_t centr2);
    double getArea() const override;
    rectangle_t getFrameRect() const override;
    void move(double dx, double dy) override;
    void move(point_t p) override;
    void scale(double k) override;
    private:
      double radius1_, radius2_;
      point_t centr1_, centr2_;
  };
  struct Elipse: Shape
  {
    Elipse(double semiax1, double semiax2, point_t centr);
    double getArea() const override;
    rectangle_t getFrameRect() const override;
    void move(double dx, double dy) override;
    void move(point_t p) override;
    void scale(double k) override;
    private:
      double semiax1_, semiax2_;
      point_t centr_;
  };
}

int main()
{
  namespace karp = karpovich;
}

karpovich::Rectangle::Rectangle(double width, double height, point_t centr):
  karpovich::Shape(),
  width_(width),
  height_(height),
  centr_(centr)
{}
double karpovich::Rectangle::getArea() const
{
  return height_ * width_;
}
karpovich::rectangle_t karpovich::Rectangle::getFrameRect() const
{
  rectangle_t frame;
  frame.pos = centr_;
  frame.height = height_;
  frame.width = width_;
  return frame;
}
void karpovich::Rectangle::move(point_t p)
{
  centr_ = p;
}
void karpovich::Rectangle::move(double dx, double dy)
{
  centr_.x += dx;
  centr_.y += dy;
}
void karpovich::Rectangle::scale(double k)
{
  width_ *= k;
  height_ *= k;
}
karpovich::Elipse::Elipse(double semiax1, double semiax2, point_t centr):
  karpovich::Shape(),
  semiax1_(semiax1),
  semiax2_(semiax2),
  centr_(centr)
{}
double karpovich::Elipse::getArea() const
{
  return PI * semiax1_ * semiax2_;
}
karpovich::rectangle_t karpovich::Elipse::getFrameRect() const
{
  rectangle_t frame;
  frame.pos = centr_;
  frame.height = 2 * semiax1_;
  frame.width = 2 * semiax2_;
}
void karpovich::Elipse::move(point_t p)
{
  centr_ = p;
}
void karpovich::Elipse::move(double dx, double dy)
{
  centr_.x += dx;
  centr_.y += dy;
}
void karpovich::Elipse::scale(double k)
{
  semiax1_ *= k;
  semiax2_ *= k;
}
karpovich::Rubber::Rubber(double radius1, double radius2, point_t centr1, point_t centr2):
  karpovich::Shape(),
  radius1_(radius1),
  radius2_(radius2),
  centr1_(centr1),
  centr2_(centr2)
{}
double karpovich::Rubber::getArea() const
{
  return PI * (radius1_ * radius1_ - radius2_ * radius2_);
}
karpovich::rectangle_t karpovich::Rubber::getFrameRect() const
{
  rectangle_t frame;
  frame.pos = centr1_;
  frame.width = frame.height = 2 * radius1_;
}
void karpovich::Rubber::move(point_t p)
{
  centr1_.x -= p.x - centr2_.x;
  centr1_.y -= p.y - centr2_.y;
  centr2_ = p;
}
void karpovich::Rubber::move(double dx, double dy)
{
  centr1_.x += dx;
  centr1_.y += dy;
  centr2_.x += dx;
  centr2_.y += dy;
}
void karpovich::Rubber::scale(double k)
{
  radius1_ *= k;
  radius2_ *= k;
}