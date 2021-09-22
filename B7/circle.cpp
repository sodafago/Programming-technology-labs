#include "circle.hpp"

Circle::Circle(double x, double y) :
  Shape(x, y)
{}

void Circle::draw(std::ostream& outStream) const noexcept
{
  outStream << "CIRCLE (" << x_ << ';' << y_ << ")\n";
}
