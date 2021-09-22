#ifndef __TASKS_HPP__
#define __TASKS_HPP__

#include <iostream>
#include <vector>
#include <forward_list>
#include <type_traits>
#include <iterator>

#include "helpfulFunctions.hpp"

namespace nigmatullin
{
  template <class T>
  void task1(int nArgs, char* args[])
  {
    if (nArgs != 3)
    {
      throw std::invalid_argument("Invalid number of arguments.");
    }

    std::function<bool(const T&, const T&)> comparator = getComparator<T>(args[2]);
    std::vector<T> vecForAccessByBrackets(std::istream_iterator<T>(std::cin), std::istream_iterator<T>());

    if (!std::cin.eof())
    {
      throw std::ios::failure("Invalid input data.");
    }

    std::vector<T> vecForAccessByAt = vecForAccessByBrackets;
    std::forward_list<T> listForAccessByIterator(vecForAccessByAt.begin(), vecForAccessByAt.end());

    sort<AccessByBrackets>(vecForAccessByBrackets, comparator);
    sort<AccessByAt>(vecForAccessByAt, comparator);
    sort<AccessByIterator>(listForAccessByIterator, comparator);

    print(vecForAccessByBrackets);
    print(vecForAccessByAt);
    print(listForAccessByIterator);
  }

  void task2(int nArg, char* args[]);

  template <class T>
  void task3(int, char**)
  {
    static_assert(std::is_integral<T>::value, "Type must be integral.");

    std::vector<T> arr;
    static const int END_SIGN = 0;

    std::cin >> std::ws;
    if (std::cin.eof())
    {
      return;
    }

    T elem;
    std::cin >> elem;

    while (std::cin && elem != END_SIGN)
    {
      arr.push_back(elem);
      std::cin >> elem;
    }

    if (!std::cin)
    {
      throw std::ios::failure("Invalid input data.");
    }

    if (arr.empty())
    {
      return;
    }

    static const int FIRST_END = 1;
    static const int SECOND_END = 2;

    if (*arr.rbegin() == FIRST_END)
    {
      static const T SHOULD_DIVIDE = 2;
      deleteIf(arr, [&](const T& elem)
      {
        return (elem % SHOULD_DIVIDE == 0);
      });
    }
    else if (*arr.rbegin() == SECOND_END)
    {
      static const T SHOULD_DIVIDE = 3;
      static const T ADDED_ELEMENT = 1;
      static const size_t COUNT_ADDED_ELEMENT = 3;
      insertAfterIf(arr, [&](const T& elem)
      {
        return (elem % SHOULD_DIVIDE == 0);
      }, ADDED_ELEMENT, COUNT_ADDED_ELEMENT);
    }

    print(arr);
  }

  void task4(int nArg, char* args[]);
}

#endif
