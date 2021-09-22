#include "circle.hpp"

#define _USE_MATH_DEFINES

#include <cmath>
#include <cassert>

Circle::Circle(const point_t& center, double radius) :
  center_(center),
  radius_(radius)
{
  assert(radius_ > 0.0);
}

double Circle::getArea() const
{
  return (M_PI * radius_ * radius_);
}

rectangle_t Circle::getFrameRect() const
{
  rectangle_t res;
  res.pos = center_;
  res.height = 2.0 * radius_;
  res.width = 2.0 * radius_;
  return res;
}

const char* Circle::getTypeShape() const
{
  return "Circle";
}

void Circle::move(const point_t& newCenter)
{
  center_ = newCenter;
}

void Circle::move(double deltXCenter, double deltYCenter)
{
  center_.x += deltXCenter;
  center_.y += deltYCenter;
}
