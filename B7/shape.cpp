#include "shape.hpp"

#include <string>
#include <sstream>

#include "circle.hpp"
#include "triangle.hpp"
#include "square.hpp"

Shape::Shape(double x, double y) :
  x_(x),
  y_(y)
{}

std::istream& operator>>(std::istream& inStream, std::shared_ptr<Shape>& shape)
{
  if (inStream.fail())
  {
    return inStream;
  }

  inStream >> std::ws;
  if (inStream.eof())
  {
    inStream.setstate(std::ios::failbit);

    return inStream;
  }

  std::string line;
  std::getline(inStream, line);
  long long openBracketPos = line.find('(');
  if (openBracketPos == -1)
  {
    inStream.setstate(std::ios::failbit);

    return inStream;
  }
  line = line.substr(0, openBracketPos) + ' ' + line.substr(openBracketPos);

  std::stringstream stream(line);
  std::string type;
  stream >> type >> std::ws;
  if (stream.eof())
  {
    inStream.setstate(std::ios::failbit);

    return inStream;
  }
  if (stream.get() != '(')
  {
    inStream.setstate(std::ios::failbit);

    return inStream;
  }
  double x;
  stream >> x;
  if (inStream.fail() || (stream >> std::ws).get() != ';')
  {
    inStream.setstate(std::ios::failbit);

    return inStream;
  }
  double y;
  stream >> y;
  if (inStream.fail() || (stream >> std::ws).get() != ')')
  {
    inStream.setstate(std::ios::failbit);

    return inStream;
  }
  if (type == "CIRCLE")
  {
    shape = std::make_shared<Circle>(x, y);
  }
  else if (type == "TRIANGLE")
  {
    shape = std::make_shared<Triangle>(x, y);
  }
  else
  {
    shape = std::make_shared<Square>(x, y);
  }
  return inStream;
}

bool Shape::isMoreLeft(const Shape& other) const noexcept
{
  return x_ < other.x_;
}

bool Shape::isUpper(const Shape& other) const noexcept
{
  return y_ > other.y_;
}
