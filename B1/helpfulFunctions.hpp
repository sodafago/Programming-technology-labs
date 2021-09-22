#ifndef __HELPFUL_FUNCTIONS_HPP__
#define __HELPFUL_FUNCTIONS_HPP__

#include <functional>
#include <cstring>
#include <stdexcept>
#include <iostream>
#include <type_traits>
#include <vector>

#include "accesses.hpp"

namespace nigmatullin
{
  template <class T>
  std::function<bool(const T&, const T&)> getComparator(const char* direction)
  {
    static const char* GREATER = "ascending";
    static const char* LESS = "descending";

    if (!strcmp(direction, GREATER))
    {
      return std::greater<T>();
    }
    else if (!strcmp(direction, LESS))
    {
      return std::less<T>();
    }
    else
    {
      throw std::invalid_argument("Invalid direction for sorting.");
    }
  }

  template <template <class Container> class Access, class Container, class Comparator>
  void sort(Container& container, const Comparator& comparator)
  {
    using access = Access<Container>;
    for (auto i = access::begin(container); i != access::end(container); access::advance(i))
    {
      for (auto j = i; j != access::end(container); access::advance(j))
      {
        auto& left = access::getReference(container, i);
        auto& right = access::getReference(container, j);
        if (comparator(left, right))
        {
          std::swap(left, right);
        }
      }
    }
  }

  template <class Iterator>
  void print(std::ostream& out, Iterator left, const Iterator& right,
      const std::string& sep = " ", const std::string& end = "\n")
  {
    if (left == right)
    {
      return;
    }
    out << *left;
    ++left;
    while (left != right)
    {
      out << sep << *left;
      ++left;
    }
    out << end;
  }

  template <class Container>
  void print(const Container& container, const std::string& sep = " ", const std::string& end = "\n")
  {
    print(std::cout, container.begin(), container.end(), sep, end);
  }

  template <class T, class Check>
  void deleteIf(std::vector<T>& arr, const Check& check)
  {
    auto left = arr.begin();
    auto right = arr.begin();
    while (right != arr.end())
    {
      if (!check(*right))
      {
        *left = *right;
        ++left;
      }
      ++right;
    }
    arr.resize(left - arr.begin());
  }

  template <class T, class Check>
  void insertAfterIf(std::vector<T>& arr, const Check& check, const T& elem, size_t count = 1)
  {
    size_t addSize = 0;

    for (auto& it : arr)
    {
      if (check(it))
      {
        addSize += count;
      }
    }

    arr.resize(arr.size() + addSize);
    auto left = arr.rbegin();
    auto right = arr.rbegin() + addSize;

    while (right != arr.rend())
    {
      if (check(*right))
      {
        for (size_t i = 0; i < count; ++i)
        {
          *left = elem;
          ++left;
        }
      }
      *left = *right;
      ++left;
      ++right;
    }
  }

  void fillRandom(double* array, size_t size);
}

#endif
