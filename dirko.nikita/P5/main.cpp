#include <cmath>
namespace dirko
{
  const double PI = acos(-1.0);
  struct p_t
  {
    double x, y;
  };
  struct rec_t
  {
    double w, h;
    p_t pos;
  };
  struct IShape
  {
    virtual double getArea() const = 0;
    virtual rec_t getFrameRect() const = 0;
    virtual void move(p_t point) = 0;
    virtual void move(double dx, double dy) = 0;
    virtual void scale(double coef) = 0;
    virtual ~IShape() = default;
  };
  struct Rectangle : IShape
  {
    Rectangle(double w, double h, p_t mid);
    double getArea() const override;
    rec_t getFrameRect() const override;
    void move(double dx, double dy) override;
    void move(p_t point) override;
    void scale(double coef) override;

  private:
    double w_, h_;
    p_t mid_;
  };
  struct Polygon : IShape
  {

  private:
  };
  struct Bubble : IShape
  {
    Bubble(double r, p_t dot);
    double getArea() const override;
    rec_t getFrameRect() const override;
    void move(double dx, double dy) override;
    void move(p_t point) override;
    void scale(double coef) override;

  private:
    double r_;
    p_t dot_;
  };
  void scaleFromPoint(IShape **shps, size_t size, p_t point, double coef);
}

int main()
{
}

dirko::Rectangle::Rectangle(double w, double h, p_t mid) : IShape(),
                                                           w_(w),
                                                           h_(h),
                                                           mid_(mid) {}

double dirko::Rectangle::getArea() const
{
  return w_ * h_;
}
dirko::rec_t dirko::Rectangle::getFrameRect() const
{
  return {w_, h_, mid_};
}
void dirko::Rectangle::move(p_t point)
{
  mid_ = point;
}
void dirko::Rectangle::move(double dx, double dy)
{
  mid_.x += dx;
  mid_.y += dy;
}
void dirko::Rectangle::scale(double coef)
{
  w_ *= coef;
  h_ *= coef;
}

dirko::Bubble::Bubble(double r, p_t dot) : IShape(),
                                           r_(r),
                                           dot_(dot) {}
double dirko::Bubble::getArea() const
{
  return PI * r_ * r_;
}
dirko::rec_t dirko::Bubble::getFrameRect() const
{
  p_t tmp = {dot_.x + r_ / 2, dot_.y};
  return {r_, r_, tmp};
}
void dirko::Bubble::move(p_t point)
{
  dot_ = point;
}
void dirko::Bubble::move(double dx, double dy)
{
  dot_.x += dx;
  dot_.y += dy;
}
void dirko::Bubble::scale(double coef)
{
  r_ *= coef;
}
void dirko::scaleFromPoint(IShape **shps, size_t size, p_t point, double coef)
{
  for (size_t i = 0; i < size; ++i)
  {
    shps[i]->move(-point.x, -point.y);
    shps[i]->scale(coef);
    shps[i]->move(point.x, point.y);
  }
}