#ifndef __STATIC_POLYGON_HPP__
#define __STATIC_POLYGON_HPP__

#include <initializer_list>
#include <stdexcept>

#include "polygon.hpp"

namespace nigmatullin
{
  template <size_t size>
  class StaticPolygon : public Polygon
  {
  public:

    StaticPolygon(const StaticPolygon& forCopy) noexcept;
    StaticPolygon(StaticPolygon&& forMove) noexcept;
    StaticPolygon(const std::initializer_list<point_t>& iniPoints);
    ~StaticPolygon() = default;

    StaticPolygon& operator=(const StaticPolygon& forCopy) noexcept;
    StaticPolygon& operator=(StaticPolygon&& forMove) noexcept;
    StaticPolygon& operator=(const std::initializer_list<point_t>& iniPoints);

  private:

    point_t content_[size];
  };
}

template <size_t size>
nigmatullin::StaticPolygon<size>::StaticPolygon(const StaticPolygon& forCopy) noexcept :
  Polygon(content_, size)
{
  *this = forCopy;
}

template <size_t size>
nigmatullin::StaticPolygon<size>::StaticPolygon(StaticPolygon&& forMove) noexcept :
  Polygon(content_, size)
{
  *this = std::move(forMove);
}

template <size_t size>
nigmatullin::StaticPolygon<size>::StaticPolygon(const std::initializer_list<point_t>& iniPoints) :
  Polygon(content_, size)
{
  *this = iniPoints;
}

template <size_t size>
nigmatullin::StaticPolygon<size>& nigmatullin::StaticPolygon<size>::operator=(const StaticPolygon& forCopy) noexcept
{
  if (this != &forCopy)
  {
    std::copy(forCopy.contentPtr_, forCopy.contentPtr_ + size_, contentPtr_);
  }

  return *this;
}

template <size_t size>
nigmatullin::StaticPolygon<size>& nigmatullin::StaticPolygon<size>::operator=(StaticPolygon&& forMove) noexcept
{
  if (this != &forMove)
  {
    std::swap(size_, forMove.size_);
    std::swap(content_, forMove.content_);

    contentPtr_ = content_;
    forMove.contentPtr_ = forMove.content_;
  }

  return *this;
}

template <size_t size>
nigmatullin::StaticPolygon<size>&
    nigmatullin::StaticPolygon<size>::operator=(const std::initializer_list<point_t>& iniPoints)
{
  if (iniPoints.size() != size_)
  {
    throw std::invalid_argument("Unexpected number of points!");
  }
  copyPoints_(iniPoints);

  return *this;
}

#endif // !__STATIC_POLYGON_HPP__
