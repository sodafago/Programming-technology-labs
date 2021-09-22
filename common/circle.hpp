#ifndef __CIRCLE_HPP__
#define __CIRCLE_HPP__

#include "shape.hpp"

namespace nigmatullin
{
  class Circle : public Shape
  {
  public:

    Circle(const point_t& center, double radius);

    const char* getTypeShape() const noexcept override;
    double getArea() const noexcept override;
    rectangle_t getFrameRect() const noexcept override;
    void move(const point_t& newCenter) noexcept override;
    void move(double deltXCenter, double deltYCenter) noexcept override;
    void scale(double magnification) override;
    void rotate(double angleInDegrees) noexcept override;

    double getRadius() const noexcept;

  private:

    point_t center_;
    double radius_;
  };
}

#endif // !__CIRCLE_HPP__
