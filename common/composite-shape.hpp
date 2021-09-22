#ifndef __COMPOSITE_SHAPE_HPP__
#define __COMPOSITE_SHAPE_HPP__

#include <iostream>
#include <memory>

#include "shape.hpp"
#include "vector.hpp"

namespace nigmatullin
{
  class CompositeShape : public Shape
  {
  public:

    const std::shared_ptr<Shape>& operator[](size_t index) const;
    friend std::ostream& operator<<(std::ostream& outStream, const CompositeShape& forOut);

    const char* getTypeShape() const noexcept override;
    double getArea() const noexcept override;
    rectangle_t getFrameRect() const override;
    void move(double deltXCenter, double deltYCenter) noexcept override;
    void move(const point_t& newCenter) noexcept override;
    void scale(double magnification) override;
    void rotate(double angleInDegrees) noexcept override;

    size_t getSize() const noexcept;
    CompositeShape& pushBack(const std::shared_ptr<Shape>& forAdd);
    CompositeShape& eraseByIndex(size_t index);

  private:

    Vector<std::shared_ptr<Shape>> content_;
  };

  std::ostream& operator<<(std::ostream& outStream, const CompositeShape& forOut);
}

#endif // !__COMPOSITE_SHAPE_HPP__
