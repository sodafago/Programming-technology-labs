#include <iostream>
#include <random>
#include <algorithm>

#include "rectangle.hpp"
#include "circle.hpp"
#include "composite-shape.hpp"

const size_t N = 15;
const size_t RIGHT_RANGE = 50;

std::mt19937 myRnd(228);

double getRandom(size_t rightRange = RIGHT_RANGE)
{
  size_t rnd = myRnd();
  return (1.0 + static_cast<double>(rnd % rightRange));
}

nigmatullin::Rectangle getRandomRectangle()
{
  nigmatullin::Rectangle res({ { getRandom(), getRandom(), }, getRandom(), getRandom(), });
  return res;
}

nigmatullin::Circle getRandomCircle()
{
  nigmatullin::Circle res({ getRandom(), getRandom(), }, getRandom());
  return res;
}

int main()
{
  nigmatullin::CompositeShape test;
  for (size_t i = 0; i < N; ++i)
  {
    bool flag = (getRandom(2) == 0.0);
    if (flag)
    {
      test.pushBack(std::make_shared<nigmatullin::Rectangle>(getRandomRectangle()));
    }
    else
    {
      test.pushBack(std::make_shared<nigmatullin::Circle>(getRandomCircle()));
    }
  }
  std::cout << test << "\n\n";
  nigmatullin::rectangle_t frameRect = test.getFrameRect();
  std::cout << "Center frameRect CompositeShape: { " << frameRect.pos.x << ", " << frameRect.pos.y << " };\n";
  test.move(getRandom(), getRandom());
  std::cout << "\nCompositeShape after moving:\n\n";
  std::cout << test << '\n';
}
