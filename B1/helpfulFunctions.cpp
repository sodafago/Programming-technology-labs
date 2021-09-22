#include "helpfulFunctions.hpp"

#include <random>

void nigmatullin::fillRandom(double* array, size_t size)
{
  static std::mt19937 rnd;
  for (size_t i = 0; i < size; ++i)
  {
    double now = rnd() * (rnd() % 2 ? 1.0 : -1.0);
    while (!(-1.0 <= now && now <= 1.0))
    {
      now /= 10.0;
    }
    array[i] = now;
  }
}
