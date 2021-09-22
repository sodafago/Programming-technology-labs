#include <iostream>

#include "static-polygon.hpp"
#include "rectangle.hpp"
#include "matrix-shape.hpp"

int main()
{
  std::shared_ptr<nigmatullin::Shape> rect1
      = std::make_shared<nigmatullin::Rectangle>(nigmatullin::rectangle_t{ { 0, 0, }, 4, 4 });
  std::shared_ptr<nigmatullin::Shape> rect2
      = std::make_shared<nigmatullin::Rectangle>(nigmatullin::rectangle_t{ { 5, 5, }, 2, 2 });
  nigmatullin::MatrixShape matrix;
  matrix.insert(rect1);
  matrix.insert(rect2);
  std::cout << matrix << '\n';
}
