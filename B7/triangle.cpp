#include "triangle.hpp"

Triangle::Triangle(double x, double y) :
  Shape(x, y)
{}

void Triangle::draw(std::ostream& outStream) const noexcept
{
  outStream << "TRIANGLE (" << x_ << ';' << y_ << ")\n";
}
