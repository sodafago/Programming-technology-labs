#include "tasks.hpp"

#include <list>
#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <map>
#include <iterator>

#include "queueWithPriority.hpp"

void task1()
{
  static std::map<std::string, nigmatullin::elementPriority> getPrior =
  {
    { "low", nigmatullin::LOW },
    { "normal", nigmatullin::NORMAL },
    { "high", nigmatullin::HIGH }
  };

  nigmatullin::QueueWithPriority<std::string> priorQueueTask1;

  std::string operation;
  while (std::getline(std::cin, operation))
  {
    std::stringstream stream(operation);
    std::string command;
    stream >> command >> std::ws;
    if (command == "add")
    {
      std::string priority;
      stream >> priority;
      stream >> std::ws;
      std::string element;
      std::getline(stream, element);
      if (element.empty() || !getPrior.count(priority))
      {
        std::cout << "<INVALID COMMAND>\n";
      }
      else
      {
        priorQueueTask1.putElementToQueue(element, getPrior[priority]);
      }
    }
    else if (command == "get" && stream.eof())
    {
      if (priorQueueTask1.isEmpty())
      {
        std::cout << "<EMPTY>\n";
      }
      else
      {
        std::cout << priorQueueTask1.getElementFromQueue() << '\n';
        priorQueueTask1.pop();
      }
    }
    else if (command == "accelerate" && stream.eof())
    {
      priorQueueTask1.accelerate();
    }
    else
    {
      std::cout << "<INVALID COMMAND>\n";
    }
  }
}

void task2()
{
  std::list<int> listTask2;

  int curElem;
  std::cin >> std::ws;
  while (!std::cin.eof() && std::cin >> curElem >> std::ws)
  {
    if (!(1 <= curElem && curElem <= 20))
    {
      throw std::ios::failure("Invalid input data!");
    }
    listTask2.push_back(curElem);
  }
  if (!std::cin || listTask2.size() > 20)
  {
    throw std::ios::failure("Invalid input data!");
  }
  if (listTask2.empty())
  {
    return;
  }
  auto left = listTask2.begin();
  auto right = --listTask2.end();
  bool wasEqual = false;
  while (left != right && !wasEqual)
  {
    std::cout << *left << ' ' << *right << ' ';
    ++left;
    wasEqual |= (left == right);
    --right;
  }
  if (left == right)
  {
    std::cout << *left;
  }
  std::cout << '\n';
}
