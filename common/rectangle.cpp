#include "rectangle.hpp"

#define _USE_MATH_DEFINES

#include <cmath>
#include <stdexcept>
#include <algorithm>

nigmatullin::Rectangle::Rectangle(const nigmatullin::rectangle_t& rectangleT) :
  rectangle_({
    { rectangleT.pos.x - rectangleT.width / 2.0, rectangleT.pos.y - rectangleT.height / 2.0, },
    { rectangleT.pos.x - rectangleT.width / 2.0, rectangleT.pos.y + rectangleT.height / 2.0, },
    { rectangleT.pos.x + rectangleT.width / 2.0, rectangleT.pos.y + rectangleT.height / 2.0, },
    { rectangleT.pos.x + rectangleT.width / 2.0, rectangleT.pos.y - rectangleT.height / 2.0, }})
{
  if (rectangleT.height <= 0.0 || rectangleT.width <= 0.0)
  {
    throw std::invalid_argument("Sides rectangle must be positive!");
  }
}

const char* nigmatullin::Rectangle::getTypeShape() const noexcept
{
  return "Rectangle";
}

double nigmatullin::Rectangle::getArea() const noexcept
{
  return rectangle_.getArea();
}

nigmatullin::rectangle_t nigmatullin::Rectangle::getFrameRect() const noexcept
{
  return rectangle_.getFrameRect();
}

void nigmatullin::Rectangle::move(const nigmatullin::point_t& newCenter) noexcept
{
  rectangle_.move(newCenter);
}

void nigmatullin::Rectangle::move(double deltXCenter, double deltYCenter) noexcept
{
  rectangle_.move(deltXCenter, deltYCenter);
}

void nigmatullin::Rectangle::scale(double magnification)
{
  rectangle_.scale(magnification);
}

void nigmatullin::Rectangle::rotate(double angleInDegrees) noexcept
{
  rectangle_.rotate(angleInDegrees);
}
