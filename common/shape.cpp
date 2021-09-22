#include "shape.hpp"

#define _USE_MATH_DEFINES

#include <cmath>

double nigmatullin::Shape::getAngleInRadians(double angleInDegrees) noexcept
{
  return (angleInDegrees * M_PI / 180.0);
}

nigmatullin::point_t nigmatullin::Shape::getEndOfRotatedVector(const point_t& start, point_t end,
    double angleInDegrees) noexcept
{
  double angleInRadians = getAngleInRadians(angleInDegrees);
  end.x -= start.x;
  end.y -= start.y;

  return { start.x + end.x * std::cos(angleInRadians) - end.y * std::sin(angleInRadians),
      start.y + end.y * std::cos(angleInRadians) + end.x * std::sin(angleInRadians), };
}
