#include "circle.hpp"

#define _USE_MATH_DEFINES

#include <cmath>
#include <stdexcept>

nigmatullin::Circle::Circle(const point_t& center, double radius) :
  center_(center),
  radius_(radius)
{
  if (radius_ <= 0.0)
  {
    throw std::invalid_argument("Radius must be positive!");
  }
}

const char* nigmatullin::Circle::getTypeShape() const noexcept
{
  return "Circle";
}

double nigmatullin::Circle::getArea() const noexcept
{
  return M_PI * radius_ * radius_;
}

nigmatullin::rectangle_t nigmatullin::Circle::getFrameRect() const noexcept
{
  return { center_, 2.0 * radius_, 2.0 * radius_ };
}

void nigmatullin::Circle::move(const point_t& newCenter) noexcept
{
  center_ = newCenter;
}

void nigmatullin::Circle::move(double deltXCenter, double deltYCenter) noexcept
{
  center_.x += deltXCenter;
  center_.y += deltYCenter;
}

void nigmatullin::Circle::scale(double magnification)
{
  if (magnification <= 0.0)
  {
    throw std::invalid_argument("Magnification must be positive!");
  }
  radius_ *= magnification;
}

void nigmatullin::Circle::rotate(double) noexcept
{
  return;
}

double nigmatullin::Circle::getRadius() const noexcept
{
  return radius_;
}
