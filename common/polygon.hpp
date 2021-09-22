#ifndef __POLYGON_HPP__
#define __POLYGON_HPP__

#include <initializer_list>
#include <cstddef>

#include "shape.hpp"

namespace nigmatullin
{
  class Polygon : public Shape
  {
  public:

    virtual ~Polygon() = default;

    const char* getTypeShape() const noexcept override;
    double getArea() const noexcept override;
    rectangle_t getFrameRect() const noexcept override;
    void move(const point_t& newCenter) noexcept override;
    void move(double deltXCenter, double deltYCenter) noexcept override;
    void scale(double magnification) override;
    void rotate(double angleInDegrees) noexcept override;

    size_t getSize() const noexcept;

  protected:

    point_t* contentPtr_;
    size_t size_;

    Polygon();
    Polygon(point_t* contentPtr, size_t size);

    void copyPoints_(const std::initializer_list<point_t>& iniPoints);

    static bool isConvex_(const std::initializer_list<point_t>& points) noexcept;
  };
}

#endif // !__POLYGON_HPP__
