#ifndef __RECTANGLE_HPP__
#define __RECTANGLE_HPP__

#include "shape.hpp"
#include "static-polygon.hpp"

namespace nigmatullin
{
  class Rectangle : public Shape
  {
  public:

    Rectangle(const rectangle_t& rectangleT);

    const char* getTypeShape() const noexcept override;
    double getArea() const noexcept override;
    rectangle_t getFrameRect() const noexcept override;
    void move(const point_t& newCenter) noexcept override;
    void move(double deltXCenter, double deltYCenter) noexcept override;
    void scale(double magnification) override;
    void rotate(double angleInDegrees) noexcept override;

  private:

    static const size_t COUNT_CORNERS = 4;
    StaticPolygon<COUNT_CORNERS> rectangle_;
  };
}

#endif // !__RECTANGLE_HPP__
