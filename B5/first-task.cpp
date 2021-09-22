#include "first-task.hpp"

#include <stdexcept>
#include <set>
#include <string>
#include <iterator>
#include <iostream>

void runFirstTask(int nArgs, [[maybe_unused]] const char* args[])
{
  if (nArgs != 2)
  {
    throw std::invalid_argument("Wrong count of parameters!");
  }

  std::set<std::string> uniqWords((std::istream_iterator<std::string>(std::cin)), std::istream_iterator<std::string>());
  if (!std::cin.eof())
  {
    throw std::ios_base::failure("Invalid read!");
  }

  std::copy(uniqWords.begin(), uniqWords.end(), std::ostream_iterator<std::string>(std::cout, "\n"));
}
