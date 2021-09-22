#include <iostream>
#include <stdexcept>
#include <string>
#include <map>

#include "firstTask.hpp"
#include "secondTask.hpp"

int main(int, char *args[])
{
  try
  {
    std::map<int, void(*)()> tasks =
    {
        { 1, runFirstTask },
        { 2, runSecondTask }
    };

    int item = std::stoi(args[1]);
    if (!tasks.count(item))
    {
      throw std::invalid_argument("Invalid item number!");
    }
    else
    {
      tasks[item]();
    }
  }
  catch (const std::exception& error)
  {
    std::cerr << error.what() << '\n';
    return 2;
  }
}
