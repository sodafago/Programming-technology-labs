#include "first-task.hpp"

#define _USE_MATH_DEFINES
#include <cmath>
#include <list>
#include <iterator>
#include <iostream>
#include <algorithm>
#include <stdexcept>

class MultiplyFunctor
{
public:
  explicit MultiplyFunctor(double coefficient) :
    coefficient_(coefficient)
  {}

  void operator()(double& elem) const noexcept
  {
    elem *= coefficient_;
  }

private:
  double coefficient_;
};

void runFirstTask(int nArgs, [[maybe_unused]] const char* args[])
{
  if (nArgs != 2)
  {
    throw std::invalid_argument("Invalid count of arguments!");
  }

  std::list<double> list((std::istream_iterator<double>(std::cin)), std::istream_iterator<double>());

  if (!std::cin.eof())
  {
    throw std::ios_base::failure("Invalid input data!");
  }

  std::for_each(list.begin(), list.end(), MultiplyFunctor(M_PI));
  std::copy(list.begin(), list.end(), std::ostream_iterator<double>(std::cout, " "));
}
