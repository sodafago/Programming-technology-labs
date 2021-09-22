#include <algorithm>
#include <functional>
#include <iostream>
#include <iterator>

#include "functor.hpp"

int main()
{
  Functor info;
  std::for_each(std::istream_iterator<long long>(std::cin), std::istream_iterator<long long>(), std::ref(info));
  try
  {
    if (!std::cin.eof())
    {
      throw std::ios_base::failure("Invalid input data!");
    }
    info.printInfo(std::cout);
  }
  catch (const std::exception& err)
  {
    std::cerr << err.what() << '\n';

    return 1;
  }
}
