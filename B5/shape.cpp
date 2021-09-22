#include "shape.hpp"

#include <string>
#include <sstream>
#include <algorithm>

std::istream& operator>>(std::istream& inStream, Point& point)
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

  if (inStream.peek() != '(')
  {
    inStream.setstate(std::ios::failbit);

    return inStream;
  }
  inStream.ignore();

  int x;
  inStream >> x;
  if (inStream.fail() || inStream.eof())
  {
    return inStream;
  }

  inStream >> std::ws;
  if (inStream.peek() != ';')
  {
    inStream.setstate(std::ios::failbit);
  }
  inStream.ignore();

  int y;
  inStream >> y;
  if (inStream.fail() || inStream.eof())
  {
    return inStream;
  }

  inStream >> std::ws;
  if (inStream.peek() != ')')
  {
    inStream.setstate(std::ios::failbit);

    return inStream;
  }
  inStream.ignore();

  point.x = x;
  point.y = y;

  return inStream;
}

std::ostream& operator<<(std::ostream& outStream, const Point& point)
{
  outStream << '(' << point.x << ";" << point.y << ')';

  return outStream;
}

std::istream& operator>>(std::istream& inStream, Shape& shape)
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

  size_t size;
  inStream >> size;
  if (inStream.fail())
  {
    return inStream;
  }
  Shape temp(size);

  std::string line;
  std::getline(inStream, line);
  std::stringstream stream(line);
  for (auto& el : temp)
  {
    stream >> el;
  }

  if (stream.fail())
  {
    inStream.setstate(std::ios::failbit);

    return inStream;
  }

  stream >> std::ws;
  if (!stream.eof())
  {
    inStream.setstate(std::ios::failbit);

    return inStream;
  }

  shape = std::move(temp);

  return inStream;
}

std::ostream& operator<<(std::ostream& outStream, const Shape& shape)
{
  if (!shape.empty())
  {
    outStream << shape[0];
    for (size_t i = 1; i < shape.size(); ++i)
    {
      outStream << ' ' << shape[i];
    }
  }

  return outStream;
}

bool isTriangle(const Shape& shape) noexcept
{
  return shape.size() == 3;
}

bool isSquare(const Shape& shape) noexcept
{
  if (isRectangle(shape))
  {
    static auto compareX = [](Point a, Point b)
    {
      return a.x < b.x;
    };

    static auto compareY = [](Point a, Point b)
    {
      return a.y < b.y;
    };

    const int minX = std::min_element(shape.begin(), shape.end(), compareX)->x;
    const int maxX = std::max_element(shape.begin(), shape.end(), compareX)->x;

    const int minY = std::min_element(shape.begin(), shape.end(), compareY)->y;
    const int maxY = std::max_element(shape.begin(), shape.end(), compareY)->y;

    if (maxX - minX == maxY - minY)
    {
      return true;
    }
  }

  return false;
}

bool isRectangle(const Shape& shape) noexcept
{
  return shape.size() == 4;
}
