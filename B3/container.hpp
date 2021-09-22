#ifndef __CONTAINER_HPP__
#define __CONTAINER_HPP__

#include <iterator>

class Container
{
public:
  class Iterator;

  static Iterator begin() noexcept;

  static Iterator end() noexcept;

private:
  static size_t BEGIN_VAL;
  static size_t END_VAL;
};

class Container::Iterator : public std::iterator<std::bidirectional_iterator_tag, size_t>
{
public:

  size_t& operator*() const noexcept;

  size_t* operator->() const noexcept;

  Iterator& operator++() noexcept;

  Iterator operator++(int) & noexcept;

  Iterator& operator--() noexcept;

  Iterator operator--(int) & noexcept;

  bool operator==(const Iterator& right) const noexcept;

  bool operator!=(const Iterator& right) const noexcept;

private:
  friend Iterator Container::begin() noexcept;
  friend Iterator Container::end() noexcept;

  size_t nFactNow_;
  size_t valFactNow_;

  explicit Iterator(size_t nFact) noexcept;

  Iterator(size_t nFactNow, size_t valFactNow);

  static size_t getFact_(size_t nFact) noexcept;
};

#endif
