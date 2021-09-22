#ifndef __CIRCLE_HPP__
#define __CIRCLE_HPP__

#include <iostream>

#include "shape.hpp"

class Circle : public Shape
{
public:
  Circle(double x, double y);

  void draw(std::ostream& outStream) const noexcept override;
};


#endif
