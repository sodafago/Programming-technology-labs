#ifndef __SHAPE_HPP__
#define __SHAPE_HPP__

#include "base-types.hpp"

class Shape
{
public:

  virtual ~Shape() = default;

  virtual double getArea() const = 0;
  virtual rectangle_t getFrameRect() const = 0;
  virtual void move(const point_t& newCenter) = 0;
  virtual void move(double deltXCenter, double deltYCenter) = 0;
  virtual const char* getTypeShape() const = 0;
};

#endif // !__SHAPE_HPP__
