#include <iostream>
#include <cstddef>
#include <stdexcept>

#include "tasks.hpp"

int main(int nArgs, char* args[])
{
  try
  {
    if (nArgs < 2)
    {
      throw std::invalid_argument("Expected number of task!");
    }

    size_t idTask = atoi(args[1]);
    if (idTask == 1)
    {
      task1();
    }
    else if (idTask == 2)
    {
      task2();
    }
    else
    {
      throw std::invalid_argument("Invalid number of task!");
    }
  }
  catch(const std::exception& e)
  {
    std::cerr << e.what() << '\n';
    return 1;
  }
}
