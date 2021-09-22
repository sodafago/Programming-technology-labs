#ifndef __RECTANGLE_HPP__
#define __RECTANGLE_HPP__

#include "shape.hpp"

class Rectangle : public Shape
{
public:

  Rectangle(const rectangle_t& rectangleT);

  double getArea() const override;
  rectangle_t getFrameRect() const override;
  void move(const point_t& newCenter) override;
  void move(double deltXCenter, double deltYCenter) override;
  const char* getTypeShape() const override;

private:

  rectangle_t rectangle_;
};

#endif // !__RECTANGLE_HPP__
