#include "second-task.hpp"

#include <stdexcept>
#include <memory>
#include <vector>
#include <iterator>
#include <algorithm>

#include "shape.hpp"

using ShapePtr = std::shared_ptr<Shape>;

template <class Iter>
void printShapes(Iter from, Iter to) noexcept
{
  std::for_each(from, to, [](const ShapePtr& shape)
  {
    shape->draw(std::cout);
  });
}

void runSecondTask(int nArgs, [[maybe_unused]] const char* args[])
{
  if (nArgs != 2)
  {
    throw std::invalid_argument("Invalid count of arguments!");
  }

  std::vector<ShapePtr> shapes((std::istream_iterator<ShapePtr>(std::cin)), std::istream_iterator<ShapePtr>());

  if (!std::cin.eof())
  {
    throw std::ios_base::failure("Invalid input data!");
  }

  std::cout << "Original:\n";
  printShapes(shapes.begin(), shapes.end());

  std::sort(shapes.begin(), shapes.end(), [](const ShapePtr& a, const ShapePtr& b)
  {
    return a->isMoreLeft(*b);
  });

  std::cout << "Left-Right:\n";
  printShapes(shapes.begin(), shapes.end());

  std::cout << "Right-Left:\n";
  printShapes(shapes.rbegin(), shapes.rend());

  std::sort(shapes.begin(), shapes.end(), [](const ShapePtr& a, const ShapePtr& b)
  {
    return (a->isUpper(*b));
  });

  std::cout << "Top-Bottom:\n";
  printShapes(shapes.begin(), shapes.end());

  std::cout << "Bottom-Top:\n";
  printShapes(shapes.rbegin(), shapes.rend());
}
