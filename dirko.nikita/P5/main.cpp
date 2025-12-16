#include <cmath>
#include <iostream>
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
    ~Polygon();
    Polygon(size_t size, p_t *pts);
    double getArea() const override;
    rec_t getFrameRect() const override;
    void move(double dx, double dy) override;
    void move(p_t point) override;
    void scale(double coef) override;

  private:
    size_t size_;
    p_t *pts_;
    p_t mid_;
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
  rec_t getTotalFrame(IShape **shps, size_t size);
  std::ostream &output(std::ostream &os, IShape **shps, size_t size);
}

int main()
{
  const size_t n = 3;
  dirko::Rectangle rec(5, 7, {3, 3});
  dirko::Bubble bub(5, {2, 0});
  dirko::p_t pts[] = {
      {2, 2},
      {2, 7},
      {3, 6},
      {4, 5},
      {3, 4},
  };
  dirko::Polygon pol(5, pts);
  dirko::IShape *shps[n] = {std::addressof(rec), std::addressof(bub), std::addressof(pol)};
  dirko::output(std::cout, shps, n);
  dirko::p_t point = {};
  double coef = 0;
  if (!(std::cin >> point.x >> point.y >> coef))
  {
    std::cerr << "Cant read\n";
    return 1;
  }
  if (coef <= 0)
  {
    std::cerr << "Negative coef\n";
    return 1;
  }
  dirko::scaleFromPoint(shps, n, point, coef);
  dirko::output(std::cout, shps, n);
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
dirko::Polygon::~Polygon()
{
  delete[] pts_;
}
dirko::Polygon::Polygon(size_t size, p_t *pts) : IShape(),
                                                 size_(size),
                                                 pts_(size < 3 ? nullptr : new p_t[size])
{
  if (size < 3)
  {
    throw std::logic_error("Cant create polygon");
  }
  double area = 0;
  for (size_t i = 0; i < size; ++i)
  {
    pts_[i] = pts[i];
    size_t j = (i + 1) % size;
    area += pts_[i].x * pts_[j].y;
    area -= pts_[j].x * pts_[i].y;
  }
  area = std::abs(area) / 2;
  double factor = 0.0;
  for (size_t i = 0; i < size; ++i)
  {
    size_t j = (i + 1) % size;
    factor = (pts_[i].x * pts_[j].y - pts_[j].x * pts_[i].y);
    mid_.x += (pts_[i].x + pts_[j].x) * factor;
    mid_.y += (pts_[i].y + pts_[j].y) * factor;
  }
  mid_.x /= (6.0 * area);
  mid_.y /= (6.0 * area);
}
double dirko::Polygon::getArea() const
{
  double area = 0;
  for (size_t i = 0; i < size_; ++i)
  {
    size_t j = (i + 1) % size_;
    area += pts_[i].x * pts_[j].y;
    area -= pts_[j].x * pts_[i].y;
  }
  return std::abs(area) / 2;
}
dirko::rec_t dirko::Polygon::getFrameRect() const
{
  double maxx = pts_[0].x, minx = pts_[0].x;
  double maxy = pts_[0].y, miny = pts_[0].y;
  for (size_t i = 1; i < size_; ++i)
  {
    maxx = std::max(maxx, pts_[i].x);
    minx = std::min(minx, pts_[i].x);
    maxy = std::max(maxy, pts_[i].y);
    miny = std::max(miny, pts_[i].y);
  }
  double w = maxx - minx;
  double h = maxy - miny;
  return {w, h, {maxx - w / 2, maxy - h / 2}};
}
void dirko::Polygon::move(double dx, double dy)
{
  for (size_t i = 0; i < size_; ++i)
  {
    pts_[i].x += dx;
    pts_[i].y += dy;
  }
  mid_.x += dx;
  mid_.y += dy;
}
void dirko::Polygon::move(p_t point)
{
  double dx = point.x - mid_.x;
  double dy = point.y - mid_.y;
  this->move(dx, dy);
}
void dirko::Polygon::scale(double coef)
{
  --coef;
  double dx = 0, dy = 0;
  for (size_t i = 0; i < size_; ++i)
  {
    dx = pts_[i].x - mid_.x;
    dy = pts_[i].y - mid_.y;
    pts_[i].x += dx * coef;
    pts_[i].y += dy * coef;
  }
}
dirko::Bubble::Bubble(double r, p_t dot) : IShape(),
                                           r_(r),
                                           dot_(dot)
{
}
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
dirko::rec_t dirko::getTotalFrame(IShape **shps, size_t size)
{
  if (size == 0)
  {
    return {0.0, 0.0, {0.0, 0.0}};
  }
  rec_t frame = shps[0]->getFrameRect();
  double left = frame.pos.x - frame.w / 2.0;
  double right = frame.pos.x + frame.w / 2.0;
  double bottom = frame.pos.y - frame.h / 2.0;
  double top = frame.pos.y + frame.h / 2.0;
  for (size_t i = 1; i < size; ++i)
  {
    frame = shps[i]->getFrameRect();
    double l = frame.pos.x - frame.w / 2.0;
    double r = frame.pos.x + frame.w / 2.0;
    double b = frame.pos.y - frame.h / 2.0;
    double t = frame.pos.y + frame.h / 2.0;
    if (l < left)
    {
      left = l;
    }
    if (r > right)
    {
      right = r;
    }
    if (b < bottom)
    {
      bottom = b;
    }
    if (t > top)
    {
      top = t;
    }
  }
  rec_t total;
  total.w = right - left;
  total.h = top - bottom;
  total.pos.x = (left + right) / 2.0;
  total.pos.y = (bottom + top) / 2.0;
  return total;
}
std::ostream &dirko::output(std::ostream &os, IShape **shps, size_t size)
{
  double totalArea = 0.0;
  for (size_t i = 0; i < size; ++i)
  {
    double area = shps[i]->getArea();
    totalArea += area;
    os << area << "\n";
    rec_t frame = shps[i]->getFrameRect();
    os << frame.pos.x << "\n";
    os << frame.pos.y << "\n";
    os << frame.w << "\n";
    os << frame.h << "\n";
  }
  rec_t totalFrame = getTotalFrame(shps, size);
  os << totalArea << "\n";
  os << totalFrame.pos.x << "\n";
  os << totalFrame.pos.y << "\n";
  os << totalFrame.w << "\n";
  os << totalFrame.h << "\n";
  return os;
}
