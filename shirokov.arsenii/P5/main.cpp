#include <cstddef>
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
    virtual double getArea() const;
    virtual rectangle_t getFrameRect() const;
    virtual void move(point_t target);
    virtual void scale(double coefficient);
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
    double center_;
    point_t *vertices_;

  public:
    Polygon(point_t *vertices, size_t s);
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
    Xquare(point_t center, double size);
    double getArea() const override;
    rectangle_t getFrameRect() const override;
    void move(point_t target) override;
    void scale(double coefficient) override;
    ~Xquare() = default;
  };

  void scaleAboutPoint(point_t target, Shape figure);
  double getTotalArea(const Shape *const *figures, size_t s);
  rectangle_t getTotalFrameRect(const Shape *const *figures, size_t s);
  void printInfo(const Shape *const *figures, size_t s);
  const size_t s = 4;
}

int main()
{
  shirokov::point_t target = {0, 0};
  double coefficient = 0;
  std::cin >> target.x >> target.y >> coefficient;
  if (std::cin.fail())
  {
    std::cerr << "Input error\n";
    return 1;
  }
  if (coefficient < 0)
  {
    std::cerr << "The coefficient cannot be negative\n";
    return 1;
  }
  const shirokov::Shape *figures[shirokov::s];
  figures[0] = nullptr;
  figures[1] = nullptr;
  figures[2] = nullptr;
  figures[3] = nullptr;
  try
  {
    figures[0] = new shirokov::Rectangle({0, 0}, 0, 0);
    figures[1] = new shirokov::Rectangle({0, 0}, {0, 0});
    figures[2] = new shirokov::Polygon({}, 0);
    figures[3] = new shirokov::Xquare({0, 0}, 0);
  }
  catch (const std::bad_alloc &)
  {
    delete figures[0];
    delete figures[1];
    delete figures[2];
    delete figures[3];
    std::cerr << "Couldn't allocate memory\n";
    return 2;
  }

  std::cout << "Before scaling:\n";
  shirokov::printInfo(figures, shirokov::s);
  for (size_t i = 0; i < shirokov::s; ++i)
  {
    shirokov::scaleAboutPoint(target, *figures[i]);
  }
  std::cout << "After scaling:\n";
  shirokov::printInfo(figures, shirokov::s);

  delete figures[0];
  delete figures[1];
  delete figures[2];
  delete figures[3];
}

shirokov::Rectangle::Rectangle(point_t center, double width, double height)
    : Shape(), center_(center), bottomLeft_({center.x - width / 2, center.y - height / 2}),
      topRight_({center.x + width / 2, center.y + height / 2})
{
}

shirokov::Rectangle::Rectangle(point_t bottomLeft, point_t topRight)
    : center_({(topRight.x - bottomLeft.x) / 2, (topRight.y - bottomLeft.y) / 2}), bottomLeft_(bottomLeft),
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
