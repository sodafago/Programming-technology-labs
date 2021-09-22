#ifndef __TRIANGLE_HPP__
#define __TRIANGLE_HPP__

#include "shape.hpp"

class Triangle : public Shape
{
public:
  Triangle(double x, double y);

  void draw(std::ostream& outStream) const noexcept override;
};

#endif
