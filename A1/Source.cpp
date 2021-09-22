#include <iostream>

#include "rectangle.hpp"
#include "circle.hpp"

int main()
{
  const int nShapes = 2;
  Shape** shapes = new Shape*[nShapes];
  shapes[0] = new Rectangle({ {0.0, 0.0, },  10.0, 10.0, });
  shapes[1] = new Circle({ 0.0, 0.0, }, 7.0);

  for (size_t i = 0; i < nShapes; ++i)
  {
    std::cout << "This shape is " << shapes[i]->getTypeShape() << "\n";
    std::cout << "Area of this " << shapes[i]->getTypeShape() << " is " << shapes[i]->getArea() << "\n";
    rectangle_t describedRectangle = shapes[i]->getFrameRect();
    std::cout << "The center of the described rectangle is "
        << describedRectangle.pos.x << ' ' << describedRectangle.pos.y << "\n";
    std::cout << "The size of the rectangle is "
        << describedRectangle.height << ' ' << describedRectangle.width << "\n\n";
  }
  for (size_t i = 0; i < nShapes; ++i)
  {
    delete shapes[i];
  }
  delete[] shapes;

  return 0;
}
