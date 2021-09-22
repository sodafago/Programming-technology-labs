#ifndef __ACCESSES_HPP__
#define __ACCESSES_HPP__

#include <cstddef>
#include <iterator>

namespace nigmatullin
{
  template <class Container>
  class AccessByBrackets
  {
  public:

    static typename Container::reference getReference(Container& container, size_t index)
    {
      return container[index];
    }

    static size_t begin(const Container&) noexcept
    {
      return 0;
    }

    static size_t end(const Container& container) noexcept
    {
      return container.size();
    }

    static void advance(size_t& index, size_t shift = 1) noexcept
    {
      index += shift;
    }

    static typename Container::reference getElementByIndex(Container& container, size_t index)
    {
      return container[index];
    }
  };

  template <class Container>
  class AccessByAt
  {
  public:

    static typename Container::reference getReference(Container& container, size_t index)
    {
      return container.at(index);
    }

    static size_t begin(const Container&) noexcept
    {
      return 0;
    }

    static size_t end(const Container& container) noexcept
    {
      return container.size();
    }

    static void advance(size_t& index, size_t shift = 1) noexcept
    {
      index += shift;
    }

    static typename Container::reference getElementByIndex(Container& container, size_t index)
    {
      return container.at(index);
    }
  };

  template <class Container>
  class AccessByIterator
  {
  public:

    static typename Container::reference getReference(Container&, const typename Container::iterator& it)
    {
      return *it;
    }

    static typename Container::iterator begin(Container& container) noexcept
    {
      return container.begin();
    }

    static typename Container::iterator end(Container& container) noexcept
    {
      return container.end();
    }

    static void advance(typename Container::iterator& it, size_t shift = 1)
    {
      std::advance(it, shift);
    }

    static typename Container::reference getElementByIndex(Container& container, size_t index)
    {
      auto it = container.begin();
      std::advance(it, index);

      return *it;
    }
  };
}

#endif
