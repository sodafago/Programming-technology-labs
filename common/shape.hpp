#ifndef __SHAPE_HPP__
#define __SHAPE_HPP__

#include "base-types.hpp"

namespace nigmatullin
{
  class Shape
  {
  public:

    virtual ~Shape() = default;

    virtual const char* getTypeShape() const noexcept = 0;
    virtual double getArea() const noexcept = 0;
    virtual rectangle_t getFrameRect() const = 0;
    virtual void move(const point_t& newCenter) noexcept = 0;
    virtual void move(double deltXCenter, double deltYCenter) noexcept = 0;
    virtual void scale(double magnification) = 0;
    virtual void rotate(double angleInDegrees) noexcept = 0;

  protected:

    static double getAngleInRadians(double angleInDegrees) noexcept;
    static point_t getEndOfRotatedVector(const point_t& start, point_t end, double angleInDegrees) noexcept;
  };
}

#endif // !__SHAPE_HPP__
