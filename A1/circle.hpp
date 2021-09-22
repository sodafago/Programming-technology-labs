#ifndef __CIRCLE_HPP__
#define __CIRCLE_HPP__

#include "shape.hpp"

class Circle : public Shape
{
public:

  Circle(const point_t& center, double radius);

  double getArea() const override;
  rectangle_t getFrameRect() const override;
  void move(const point_t& newCenter) override;
  void move(double deltXCenter, double deltYCenter) override;
  const char* getTypeShape() const override;

private:

  point_t center_;
  double radius_;
};

#endif // !__CIRCLE_HPP__
