#include <cmath>
#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <new>

namespace shirokov
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
    virtual void move(point_t target) = 0;
    virtual void scale(double coefficient) = 0;
    virtual ~Shape() = default;
  };

  struct Rectangle final : Shape
  {
  private:
    point_t center_, bottomLeft_, topRight_;

  public:
    Rectangle(point_t center, double width, double height);
    Rectangle(point_t bottomLeft, point_t topRight);
    double getArea() const override;
    rectangle_t getFrameRect() const override;
    void move(point_t target) override;
    void scale(double coefficient) override;
    ~Rectangle() = default;
  };

  struct Polygon final : Shape
  {
  private:
    point_t center_;
    point_t *vertices_;
    size_t s_;

  public:
    Polygon(const point_t *vertices, size_t s);
    double getArea() const override;
    rectangle_t getFrameRect() const override;
    void move(point_t target) override;
    void scale(double coefficient) override;
    ~Polygon();
  };

  struct Xquare final : Shape
  {
  private:
    point_t center_, top_, bottom_;

  public:
    Xquare(point_t center, double side);
    Xquare(point_t top, point_t bottom);
    double getArea() const override;
    rectangle_t getFrameRect() const override;
    void move(point_t target) override;
    void scale(double coefficient) override;
    ~Xquare() = default;
  };

  void scaleAboutPoint(point_t target, Shape *figure);
  double getTotalArea(const Shape *const *figures, size_t s);
  rectangle_t getTotalFrameRect(const Shape *const *figures, size_t s);
  void printInfo(const Shape *const *figures, size_t s);
  const size_t size = 5;
}

int main()
{
  shirokov::Shape *figures[shirokov::size];
  for (size_t i = 0; i < shirokov::size; ++i)
  {
    figures[i] = nullptr;
  }
  try
  {
    figures[0] = new shirokov::Rectangle({5, 5}, 10, 10);
    figures[1] = new shirokov::Rectangle({0, 0}, {10, 10});
    const shirokov::point_t vertices[] = {{0, 0}, {4, 0}, {4, 3}, {0, 3}};
    figures[2] = new shirokov::Polygon(vertices, 4);
    figures[3] = new shirokov::Xquare({0, 0}, 5);
    figures[4] = new shirokov::Xquare({0, 5}, {0, 0});
  }
  catch (const std::bad_alloc &)
  {
    for (size_t i = 0; i < shirokov::size; ++i)
    {
      delete figures[i];
    }
    std::cerr << "Couldn't allocate memory\n";
    return 2;
  }

  std::cout << "Before scaling:\n";
  shirokov::printInfo(figures, shirokov::size);

  shirokov::point_t target = {0, 0};
  double coefficient = 0;
  std::cin >> target.x >> target.y >> coefficient;
  if (std::cin.fail())
  {
    std::cerr << "Input error\n";
    for (size_t i = 0; i < shirokov::size; ++i)
    {
      delete figures[i];
    }
    return 1;
  }
  if (coefficient < 0)
  {
    std::cerr << "The coefficient cannot be negative\n";
    for (size_t i = 0; i < shirokov::size; ++i)
    {
      delete figures[i];
    }
    return 1;
  }

  for (size_t i = 0; i < shirokov::size; ++i)
  {
    shirokov::scaleAboutPoint(target, figures[i]);
  }
  std::cout << "After scaling:\n";
  shirokov::printInfo(figures, shirokov::size);

  for (size_t i = 0; i < shirokov::size; ++i)
  {
    delete figures[i];
  }
}

shirokov::Rectangle::Rectangle(point_t center, double width, double height)
    : Shape(), center_(center), bottomLeft_({center.x - width / 2, center.y - height / 2}),
      topRight_({center.x + width / 2, center.y + height / 2})
{
}

shirokov::Rectangle::Rectangle(point_t bottomLeft, point_t topRight)
    : Shape(), center_({(topRight.x - bottomLeft.x) / 2, (topRight.y - bottomLeft.y) / 2}), bottomLeft_(bottomLeft),
      topRight_(topRight)
{
}

double shirokov::Rectangle::getArea() const
{
  return (topRight_.x - bottomLeft_.x) * (topRight_.y - bottomLeft_.y);
}

shirokov::rectangle_t shirokov::Rectangle::getFrameRect() const
{
  return {topRight_.x - bottomLeft_.x, topRight_.y - bottomLeft_.y, center_};
}

void shirokov::Rectangle::move(point_t target)
{
  point_t delta = {center_.x - target.x, center_.y - target.y};
  center_ = target;
  topRight_ = {topRight_.x - delta.x, topRight_.y - delta.y};
  bottomLeft_ = {bottomLeft_.x - delta.x, bottomLeft_.y - delta.y};
}

void shirokov::Rectangle::scale(double coefficient)
{
  bottomLeft_ = {center_.x + coefficient * (bottomLeft_.x - center_.x),
                 center_.y + coefficient * (bottomLeft_.y - center_.y)};
  topRight_ = {center_.x + coefficient * (topRight_.x - center_.x),
               center_.y + coefficient * (topRight_.y - center_.y)};
}

shirokov::Polygon::Polygon(const point_t *vertices, size_t s)
    : Shape(), center_({0, 0}), vertices_(new point_t[s]), s_(s)
{
  for (size_t i = 0; i < s; ++i)
  {
    vertices_[i] = vertices[i];
  }

  double A = 0;
  double cx = 0, cy = 0;
  for (size_t i = 0; i < s; ++i)
  {
    double xi = vertices_[i].x;
    double yi = vertices_[i].y;
    size_t j = (i + 1) % s_;
    double xj = vertices_[j].x;
    double yj = vertices_[j].y;
    double cross = xi * yj - xj * yi;
    A += cross;
    cx += (xi + xj) * cross;
    cy += (yi + yj) * cross;
  }
  A *= 0.5;
  cx /= 6 * A;
  cy /= 6 * A;

  center_ = {cx, cy};
}

double shirokov::Polygon::getArea() const
{
  double A = 0;
  for (size_t i = 0; i < s_; ++i)
  {
    double xi = vertices_[i].x;
    double yi = vertices_[i].y;
    size_t j = (i + 1) % s_;
    double xj = vertices_[j].x;
    double yj = vertices_[j].y;
    double cross = xi * yj - xj * yi;
    A += cross;
  }
  A *= 0.5;
  return std::abs(A);
}

shirokov::rectangle_t shirokov::Polygon::getFrameRect() const
{
  double maxx = vertices_[0].x, minx = vertices_[0].x, maxy = vertices_[0].y, miny = vertices_[0].y;
  for (size_t i = 0; i < s_; ++i)
  {
    maxx = std::max(maxx, vertices_[i].x);
    minx = std::min(maxx, vertices_[i].x);
    maxy = std::max(maxx, vertices_[i].x);
    miny = std::min(maxx, vertices_[i].x);
  }
  double width = maxx - minx;
  double height = maxy - miny;
  point_t pos = {(minx + maxx) / 2, (miny + maxy) / 2};
  rectangle_t res = {width, height, pos};
  return res;
}

void shirokov::Polygon::move(point_t target)
{
  point_t delta = {center_.x - target.x, center_.y - target.y};
  center_ = target;
  for (size_t i = 0; i < s_; ++i)
  {
    vertices_[i] = {vertices_[i].x - delta.x, vertices_[i].y - delta.y};
  }
}

void shirokov::Polygon::scale(double coefficient)
{
  for (size_t i = 0; i < s_; ++i)
  {
    vertices_[i] = {center_.x + coefficient * (vertices_[i].x - center_.x),
                    center_.y + coefficient * (vertices_[i].y - center_.y)};
  }
}

shirokov::Polygon::~Polygon()
{
  delete[] vertices_;
}

shirokov::Xquare::Xquare(point_t center, double side)
    : Shape(), center_(center), top_({center.x, center.y + side / std::sqrt(2)}),
      bottom_({center.x, center.y - side / std::sqrt(2)})
{
}

shirokov::Xquare::Xquare(point_t top, point_t bottom)
    : Shape(), center_({(top.x + bottom.x) / 2, (top.y + bottom.y) / 2}), top_(top), bottom_(bottom)
{
}

double shirokov::Xquare::getArea() const
{
  double side = (top_.y - bottom_.y) / std::sqrt(2);
  return side * side;
}

shirokov::rectangle_t shirokov::Xquare::getFrameRect() const
{
  double width = top_.y - bottom_.y;
  double height = width;
  point_t pos = center_;
  return {width, height, pos};
}

void shirokov::Xquare::move(point_t target)
{
  point_t delta = {center_.x - target.x, center_.y - target.y};
  center_ = target;
  top_ = {top_.x - delta.x, top_.y - delta.y};
  bottom_ = {bottom_.x - delta.x, bottom_.y - delta.y};
}

void shirokov::Xquare::scale(double coefficient)
{
  bottom_.y = center_.y + coefficient * (bottom_.y - center_.y);
  top_.y = center_.y + coefficient * (top_.y - center_.y);
}

void shirokov::scaleAboutPoint(shirokov::point_t target, shirokov::Shape *figure)
{
  (void) target;
  (void) figure;
}

double shirokov::getTotalArea(const shirokov::Shape *const *figures, size_t s)
{
  double res = 0;
  for (size_t i = 0; i < s; ++i)
  {
    res += figures[i]->getArea();
  }
  return res;
}

shirokov::rectangle_t shirokov::getTotalFrameRect(const shirokov::Shape *const *figures, size_t s)
{
  rectangle_t frameRect = figures[0]->getFrameRect();
  double minX = frameRect.pos.x - frameRect.width / 2;
  double maxX = frameRect.pos.x + frameRect.width / 2;
  double minY = frameRect.pos.y - frameRect.height / 2;
  double maxY = frameRect.pos.y + frameRect.height / 2;
  for (size_t i = 1; i < s; ++i)
  {
    frameRect = figures[i]->getFrameRect();
    double left = frameRect.pos.x - frameRect.width / 2;
    double right = frameRect.pos.x + frameRect.width / 2;
    double bottom = frameRect.pos.y - frameRect.height / 2;
    double top = frameRect.pos.y + frameRect.height / 2;

    minX = std::min(minX, left);
    maxX = std::max(maxX, right);
    minY = std::min(minY, bottom);
    maxY = std::max(maxY, top);
  }
  double width = maxX - minX;
  double height = maxY - minY;
  point_t pos = {(maxX + minX) / 2, (maxY + minY) / 2};

  return {width, height, pos};
}

void shirokov::printInfo(const Shape *const *figures, size_t s)
{
  std::cout << "Areas of figures:\n";
  for (size_t i = 0; i < s; ++i)
  {
    std::cout << "\tFigure " << i + 1 << ": " << figures[i]->getArea() << '\n';
  }
  std::cout << "Total area: " << shirokov::getTotalArea(figures, s) << '\n';
  std::cout << "Frame rect of figures:\n";
  for (size_t i = 0; i < s; ++i)
  {
    shirokov::rectangle_t frameRect = figures[i]->getFrameRect();
    std::cout << "\tFigure " << i + 1 << ": \n";
    std::cout << "\t\tWidth: " << frameRect.width << '\n';
    std::cout << "\t\tHeight: " << frameRect.height << '\n';
    std::cout << "\t\tCenter: \n";
    std::cout << "\t\t\tx: " << frameRect.pos.x << '\n';
    std::cout << "\t\t\ty: " << frameRect.pos.y << '\n';
  }
  shirokov::rectangle_t frameRect = shirokov::getTotalFrameRect(figures, s);
  std::cout << "Total frame rect: \n";
  std::cout << "\t\tWidth: " << frameRect.width << '\n';
  std::cout << "\t\tHeight: " << frameRect.height << '\n';
  std::cout << "\t\tCenter: \n";
  std::cout << "\t\t\tx: " << frameRect.pos.x << '\n';
  std::cout << "\t\t\ty: " << frameRect.pos.y << '\n';
}
