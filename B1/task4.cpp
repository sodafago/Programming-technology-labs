#include "tasks.hpp"

#include <vector>
#include <stdexcept>

#include "helpfulFunctions.hpp"

void nigmatullin::task4(int nArgs, char* args[])
{
  if (nArgs != 4)
  {
    throw std::invalid_argument("Invalid number of arguments.");
  }

  size_t vecSize = atoi(args[3]);

  if (!vecSize && strcmp("0", args[3]) != 0)
  {
    throw std::invalid_argument("Invalid size for vector.");
  }

  std::vector<double> arr(vecSize);

  fillRandom(arr.data(), arr.size());

  print(arr);

  sort<AccessByBrackets>(arr, getComparator<double>(args[2]));

  print(arr);
}
