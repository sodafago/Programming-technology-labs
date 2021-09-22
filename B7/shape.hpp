#ifndef __SHAPE_HPP__
#define __SHAPE_HPP__

#include <iostream>
#include <memory>

class Shape
{
public:
  Shape(double x, double y);

  virtual ~Shape() noexcept = default;

  friend std::istream& operator>>(std::istream& inStream, std::shared_ptr<Shape>& shape);

  [[nodiscard]]
  bool isMoreLeft(const Shape& other) const noexcept;

  [[nodiscard]]
  bool isUpper(const Shape& other) const noexcept;

  virtual void draw(std::ostream& outStream) const noexcept = 0;

protected:
  double x_;
  double y_;
};


#endif
