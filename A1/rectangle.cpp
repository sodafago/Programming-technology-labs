#include "rectangle.hpp"

#include <cassert>

Rectangle::Rectangle(const rectangle_t& rectangleT) :
  rectangle_(rectangleT)
{
  assert(rectangle_.height > 0.0 && rectangle_.width > 0.0);
}

double Rectangle::getArea() const
{
  return (rectangle_.height * rectangle_.width);
}

rectangle_t Rectangle::getFrameRect() const
{
  return rectangle_;
}

const char* Rectangle::getTypeShape() const
{
  return "Rectangle";
}

void Rectangle::move(const point_t& newCenter)
{
  rectangle_.pos = newCenter;
}

void Rectangle::move(double deltXCenter, double deltYCenter)
{
  rectangle_.pos.x += deltXCenter;
  rectangle_.pos.y += deltYCenter;
}
