#ifndef __DYNAMIC_POLYGON_HPP__
#define __DYNAMIC_POLYGON_HPP__

#include <initializer_list>

#include "vector.hpp"
#include "polygon.hpp"

namespace nigmatullin
{
  class DynamicPolygon : public Polygon
  {
  public:

    DynamicPolygon(const DynamicPolygon& forCopy);
    DynamicPolygon(DynamicPolygon&& forMove) noexcept;
    DynamicPolygon(const std::initializer_list<point_t>& iniPoints);
    ~DynamicPolygon() = default;

    DynamicPolygon& operator=(const DynamicPolygon& forCopy);
    DynamicPolygon& operator=(DynamicPolygon&& forMove) noexcept;
    DynamicPolygon& operator=(const std::initializer_list<point_t>& iniPoints);

  private:

    Vector<point_t> content_;
  };
}

#endif // !__DYNAMIC_POLYGON_HPP__
