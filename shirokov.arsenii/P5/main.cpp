#include <cstddef>

namespace shirokov
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
    virtual double getArea() const;
    virtual rectangle_t getFrameRect() const;
    virtual void move(point_t target);
    virtual void scale(double coefficient);

  protected:
    virtual ~Shape() = default;
  };

  struct Rectangle final : Shape
  {
  private:
    point_t center_, bottomLeft_, topRight_;

  public:
    Rectangle(point_t center, double side);
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
    Xquare(point_t top, point_t bottom);
    double getArea() const override;
    rectangle_t getFrameRect() const override;
    void move(point_t target) override;
    void scale(double coefficient) override;
    ~Xquare() = default;
  };

  void scaleAboutPoint(point_t target, Shape figure);
  double getTotalArea(const Shape *const *figures, size_t s);
  rectangle_t getTotalFrameRect(const Shape *const *figures, size_t s);
}

int main()
{
}
