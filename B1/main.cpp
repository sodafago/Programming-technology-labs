#include <iostream>
#include <stdexcept>

#include "tasks.hpp"

int main(int nArg, char* args[])
{
  try
  {
    if (nArg < 2)
    {
      throw std::invalid_argument("Expected number of task.");
    }

    int numbTask = atoi(args[1]);

    if (numbTask == 1)
    {
      nigmatullin::task1<int>(nArg, args);
    }
    else if (numbTask == 2)
    {
      nigmatullin::task2(nArg, args);
    }
    else if (numbTask == 3)
    {
      nigmatullin::task3<int>(nArg, args);
    }
    else if (numbTask == 4)
    {
      nigmatullin::task4(nArg, args);
    }
    else
    {
      throw std::invalid_argument("Unknown number of task.");
    }
  }
  catch (const std::exception& err)
  {
    std::cerr << err.what() << '\n';
    return 1;
  }
}
