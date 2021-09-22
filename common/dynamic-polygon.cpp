#include "dynamic-polygon.hpp"

nigmatullin::DynamicPolygon::DynamicPolygon(const DynamicPolygon& forCopy) :
  Polygon()
{
  *this = forCopy;
}

nigmatullin::DynamicPolygon::DynamicPolygon(DynamicPolygon&& forMove) noexcept :
  Polygon()
{
  *this = std::move(forMove);
}

nigmatullin::DynamicPolygon::DynamicPolygon(const std::initializer_list<point_t>& iniPoints) :
  Polygon()
{
  *this = iniPoints;
}

nigmatullin::DynamicPolygon& nigmatullin::DynamicPolygon::operator=(const DynamicPolygon& forCopy)
{
  if (this != &forCopy)
  {
    content_ = forCopy.content_;
    contentPtr_ = content_.getRawPtr();
    size_ = content_.getSize();
  }

  return *this;
}

nigmatullin::DynamicPolygon& nigmatullin::DynamicPolygon::operator=(DynamicPolygon&& forMove) noexcept
{
  if (this != &forMove)
  {
    content_ = std::move(forMove.content_);
    contentPtr_ = content_.getRawPtr();
    size_ = content_.getSize();

    forMove.contentPtr_ = nullptr;
    forMove.size_ = 0;
  }

  return *this;
}

nigmatullin::DynamicPolygon& nigmatullin::DynamicPolygon::operator=(const std::initializer_list<point_t>& iniPoints)
{
  if (!isConvex_(iniPoints))
  {
    throw std::invalid_argument("Polygon must be convex!");
  }
  content_.resize(iniPoints.size());
  contentPtr_ = content_.getRawPtr();
  size_ = content_.getSize();
  copyPoints_(iniPoints);

  return *this;
}
