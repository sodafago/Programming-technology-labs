#include "second-task.hpp"

#include <algorithm>
#include <iterator>
#include <list>
#include <numeric>
#include <stdexcept>

#include "shape.hpp"

size_t getTotalNumberOfVertices(const std::list<Shape>& list) noexcept
{
  return std::accumulate(list.begin(), list.end(), 0, [](size_t totalVertices, const Shape& shape)
  {
    return totalVertices + shape.size();
  });
}

size_t getTotalNumberOfTriangles(const std::list<Shape>& list) noexcept
{
  return std::count_if(list.begin(), list.end(), isTriangle);
}

size_t getTotalNumberOfSquares(const std::list<Shape>& list) noexcept
{
  return std::count_if(list.begin(), list.end(), isSquare);
}

size_t getTotalNumberOfRectangles(const std::list<Shape>& list) noexcept
{
  return std::count_if(list.begin(), list.end(), isRectangle);
}

void erasePentagons(std::list<Shape>& list) noexcept
{
  list.erase(std::remove_if(list.begin(), list.end(), [](const Shape& shape)
  {
    return shape.size() == 5;
  }), list.end());
}

std::vector<Point> getShapesPoints(const std::list<Shape>& list)
{
  std::vector<Point> res;
  std::transform(list.begin(), list.end(), std::back_inserter(res), [](const Shape& shape)
  {
    return shape.at(0);
  });

  return res;
}

void runSecondTask(int nArgs, [[maybe_unused]] const char* args[])
{
  if (nArgs != 2)
  {
    throw std::invalid_argument("Wrong count of parameters!");
  }

  std::list<Shape> shapes((std::istream_iterator<Shape>(std::cin)), std::istream_iterator<Shape>());
  if (!std::cin.eof())
  {
    throw std::ios_base::failure("Invalid read data!");
  }

  size_t countVertices = getTotalNumberOfVertices(shapes);
  size_t countTriangles = getTotalNumberOfTriangles(shapes);
  size_t countSquares = getTotalNumberOfSquares(shapes);
  size_t countRectangles = getTotalNumberOfRectangles(shapes);
  erasePentagons(shapes);
  auto shapePoints = getShapesPoints(shapes);
  auto trianglesEnd = std::partition(shapes.begin(), shapes.end(), isTriangle);
  auto squaresEnd = std::partition(trianglesEnd, shapes.end(), isSquare);
  std::partition(squaresEnd, shapes.end(), isRectangle);

  std::cout << "Vertices: " << countVertices << '\n';
  std::cout << "Triangles: " << countTriangles << '\n';
  std::cout << "Squares: " << countSquares << '\n';
  std::cout << "Rectangles: " << countRectangles << '\n';
  std::cout << "Points: " << shapePoints << '\n';
  std::cout << "Shapes:\n";
  for (auto& el : shapes)
  {
    std::cout << el.size();
    if (!el.empty())
    {
      std::cout << ' ' << el;
    }
    std::cout << '\n';
  }
}
