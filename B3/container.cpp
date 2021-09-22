#include "container.hpp"

#include <utility>

size_t Container::BEGIN_VAL = 1;
size_t Container::END_VAL = 11;

Container::Iterator Container::begin() noexcept
{
  return Container::Iterator(BEGIN_VAL);
}

Container::Iterator Container::end() noexcept
{
  return Container::Iterator(END_VAL);
}

Container::Iterator::Iterator(size_t nFact) noexcept :
  nFactNow_(nFact),
  valFactNow_(getFact_(nFact))
{
}

size_t& Container::Iterator::operator*() const noexcept
{
  static size_t temp;
  temp = valFactNow_;
  return temp;
}

size_t* Container::Iterator::operator->() const noexcept
{
  static size_t temp;
  temp = valFactNow_;

  return &temp;
}

Container::Iterator& Container::Iterator::operator++() noexcept
{
  ++nFactNow_;
  valFactNow_ *= nFactNow_;

  return *this;
}

Container::Iterator Container::Iterator::operator++(int) & noexcept
{
  return std::exchange(*this, Iterator(nFactNow_ + 1, valFactNow_ * (nFactNow_ + 1)));
}

Container::Iterator& Container::Iterator::operator--() noexcept
{
  valFactNow_ /= nFactNow_;
  --nFactNow_;

  return *this;
}

Container::Iterator Container::Iterator::operator--(int) & noexcept
{
  return std::exchange(*this, Iterator(nFactNow_ - 1, valFactNow_ / nFactNow_));
}

bool Container::Iterator::operator==(const Container::Iterator& right) const noexcept
{
  return nFactNow_ == right.nFactNow_;
}

bool Container::Iterator::operator!=(const Container::Iterator& right) const noexcept
{
  return nFactNow_ != right.nFactNow_;
}

Container::Iterator::Iterator(size_t nFactNow, size_t valFactNow) :
  nFactNow_(nFactNow),
  valFactNow_(valFactNow)
{}

size_t Container::Iterator::getFact_(size_t nFact) noexcept
{
  size_t res = 1;
  for (size_t i = 1; i <= nFact; ++i)
  {
    res *= i;
  }

  return res;
}
