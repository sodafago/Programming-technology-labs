#include "polygon.hpp"

#include <stdexcept>
#include <algorithm>
#include <cassert>

const char* nigmatullin::Polygon::getTypeShape() const noexcept
{
  return "Polygon";
}

double nigmatullin::Polygon::getArea() const noexcept
{
  double area = 0.0;
  for (size_t i = 0; i < size_; ++i)
  {
    point_t& pt1 = contentPtr_[i > 0 ? i - 1 : size_ - 1];
    point_t& pt2 = contentPtr_[i];
    area += (pt1.x - pt2.x) * (pt1.y + pt2.y);
  }

  return std::abs(area) / 2.0;
}

nigmatullin::rectangle_t nigmatullin::Polygon::getFrameRect() const noexcept
{
  point_t leftDown = contentPtr_[0];
  point_t rightUp = contentPtr_[0];
  for (size_t i = 0; i < size_; ++i)
  {
    point_t& now = contentPtr_[i];
    leftDown.x = std::min(leftDown.x, now.x);
    leftDown.y = std::min(leftDown.y, now.y);
    rightUp.x = std::max(rightUp.x, now.x);
    rightUp.y = std::max(rightUp.y, now.y);
  }

  return { { (leftDown.x + rightUp.x) / 2.0, (leftDown.y + rightUp.y) / 2.0, },
      rightUp.x - leftDown.x, rightUp.y - leftDown.y, };
}

void nigmatullin::Polygon::move(const point_t& newCenter) noexcept
{
  point_t oldCenter = getFrameRect().pos;
  move(newCenter.x - oldCenter.x, newCenter.y - oldCenter.y);
}

void nigmatullin::Polygon::move(double deltXCenter, double deltYCenter) noexcept
{
  for (size_t i = 0; i < size_; ++i)
  {
    contentPtr_[i].x += deltXCenter;
    contentPtr_[i].y += deltYCenter;
  }
}

void nigmatullin::Polygon::scale(double magnification)
{
  if (magnification <= 0.0)
  {
    throw std::invalid_argument("Expected positive magnification");
  }
  point_t center = getFrameRect().pos;
  for (size_t i = 0; i < size_; ++i)
  {
    contentPtr_[i].x += (contentPtr_[i].x - center.x) * (magnification - 1.0);
    contentPtr_[i].y += (contentPtr_[i].y - center.y) * (magnification - 1.0);
  }
}

void nigmatullin::Polygon::rotate(double angleInDegrees) noexcept
{
  point_t center = getFrameRect().pos;
  for (size_t i = 0; i < size_; ++i)
  {
    contentPtr_[i] = getEndOfRotatedVector(center, contentPtr_[i], angleInDegrees);
  }
}

size_t nigmatullin::Polygon::getSize() const noexcept
{
  return size_;
}

nigmatullin::Polygon::Polygon() :
  Polygon(nullptr, 0) {}

nigmatullin::Polygon::Polygon(point_t* contentPtr, size_t size) :
  contentPtr_(contentPtr),
  size_(size) {}

void nigmatullin::Polygon::copyPoints_(const std::initializer_list<point_t>& iniPoints)
{
  assert(size_ == iniPoints.size());
  if (!isConvex_(iniPoints))
  {
    throw std::invalid_argument("Polygon must be convex!");
  }
  std::copy(iniPoints.begin(), iniPoints.end(), contentPtr_);
}

bool nigmatullin::Polygon::isConvex_(const std::initializer_list<point_t>& points) noexcept
{
  if (points.size() < 3)
  {
    return false;
  }

  bool clockwiseRotation = false;
  bool counterclockwiseRotation = false;
  for (size_t i = 0; i < points.size(); ++i)
  {
    const point_t& pt1 = *(points.begin() + i);
    const point_t& pt2 = *(points.begin() + (i + 1) % points.size());
    const point_t& pt3 = *(points.begin() + (i + 2) % points.size());
    double doubleSignArea = (pt2.x - pt1.x) * (pt3.y - pt1.y) - (pt2.y - pt1.y) * (pt3.x - pt1.x);
    clockwiseRotation |= (doubleSignArea < 0);
    counterclockwiseRotation |= (doubleSignArea > 0);
  }

  return (clockwiseRotation != counterclockwiseRotation);
}
