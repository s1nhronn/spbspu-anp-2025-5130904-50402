#include <iostream>

namespace karpovich
{
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
    Elipse(double semiax1_, double semiax2_, point_t centr);
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
