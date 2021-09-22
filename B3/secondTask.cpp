#include "secondTask.hpp"

#include <iostream>
#include <iterator>

#include "container.hpp"

void runSecondTask()
{
  std::copy(Container::begin(), Container::end(), std::ostream_iterator<size_t>(std::cout, " "));
  std::cout << '\n';
  std::reverse_iterator<Container::Iterator> rbegin(Container::end());
  std::reverse_iterator<Container::Iterator> rend(Container::begin());
  std::copy(rbegin, rend, std::ostream_iterator<size_t>(std::cout, " "));
  std::cout << '\n';
}
