#include <iostream>
#include <stdexcept>
#include <map>

#include "first-task.hpp"
#include "second-task.hpp"

int main(int nArgs, const char* args[])
{
  try
  {
    if (nArgs < 2)
    {
      throw std::invalid_argument("A few parameters!");
    }
    const std::map<int, void(*)(int, const char*[])> tasks =
    {
      { 1, runFirstTask },
      { 2, runSecondTask },
    };
    tasks.at(std::stoi(args[1]))(nArgs, args);
  }
  catch (const std::exception& err)
  {
    std::cerr << err.what() << '\n';
    return 1;
  }
}
