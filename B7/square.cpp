#include "square.hpp"

Square::Square(double x, double y) :
  Shape(x, y)
{}

void Square::draw(std::ostream& outStream) const noexcept
{
  outStream << "SQUARE (" << x_ << ';' << y_ << ")\n";
}
