#ifndef __SQUARE_HPP__
#define __SQUARE_HPP__

#include "shape.hpp"

class Square : public Shape
{
public:
  Square(double x, double y);

  void draw(std::ostream& outStream) const noexcept override;
};


#endif
