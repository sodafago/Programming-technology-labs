#ifndef __SHAPE_HPP__
#define __SHAPE_HPP__

#include <vector>
#include <iostream>

struct Point
{
  int x;
  int y;
};

using Shape = std::vector<Point>;

std::istream& operator>>(std::istream& inStream, Point& point);

std::ostream& operator<<(std::ostream& outStream, const Point& point);

std::istream& operator>>(std::istream& inStream, Shape& shape);

std::ostream& operator<<(std::ostream& outStream, const Shape& shape);

bool isTriangle(const Shape& shape) noexcept;

bool isSquare(const Shape& shape) noexcept;

bool isRectangle(const Shape& shape) noexcept;

#endif
