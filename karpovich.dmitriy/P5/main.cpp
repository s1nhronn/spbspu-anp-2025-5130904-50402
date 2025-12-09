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
    virtual ~Shape() = default;
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
  struct Ellipse: Shape
  {
    Ellipse(double semiax1, double semiax2, point_t centr);
    double getArea() const override;
    rectangle_t getFrameRect() const override;
    void move(double dx, double dy) override;
    void move(point_t p) override;
    void scale(double k) override;
    private:
      double semiax1_, semiax2_;
      point_t centr_;
  };
  void scalefrompt(Shape* shapes[], size_t size, double k, point_t pt);
}

int main()
{
  namespace karp = karpovich;
  karp::Rectangle rect(4.0, 2.0, {1.0, 1.0});
  karp::Ellipse ell(3.0, 2.0, {-2.0, 0.0});
  karp::Rubber rub(5.0, 2.0, {0.0, 0.0}, {1.0, 1.0});
  const size_t n = 3;
  karp::Shape* shapes[n] = {&rect, &ell, &rub};
  
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
karpovich::Ellipse::Ellipse(double semiax1, double semiax2, point_t centr):
  karpovich::Shape(),
  semiax1_(semiax1),
  semiax2_(semiax2),
  centr_(centr)
{}
double karpovich::Ellipse::getArea() const
{
  return PI * semiax1_ * semiax2_;
}
karpovich::rectangle_t karpovich::Ellipse::getFrameRect() const
{
  rectangle_t frame;
  frame.pos = centr_;
  frame.height = 2 * semiax1_;
  frame.width = 2 * semiax2_;
}
void karpovich::Ellipse::move(point_t p)
{
  centr_ = p;
}
void karpovich::Ellipse::move(double dx, double dy)
{
  centr_.x += dx;
  centr_.y += dy;
}
void karpovich::Ellipse::scale(double k)
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
  double left   = std::min(centr1_.x - radius1_, centr2_.x - radius2_);
  double right  = std::max(centr1_.x + radius1_, centr2_.x + radius2_);
  double bottom = std::min(centr1_.y - radius1_, centr2_.y - radius2_);
  double top    = std::max(centr1_.y + radius1_, centr2_.y + radius2_);

  rectangle_t frame;
  frame.width  = right - left;
  frame.height = top - bottom;
  frame.pos.x  = (left + right) / 2.0;
  frame.pos.y  = (bottom + top) / 2.0;
  return frame;
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
void karpovich::scalefrompt(Shape* shapes[], size_t size, double k, point_t pt)
{
  for (size_t i = 0; i < size; ++i) {
    shapes[i]->move(-pt.x, -pt.y);
    shapes[i]->scale(k);
    shapes[i]->move(pt.x, pt.y);
  }
}