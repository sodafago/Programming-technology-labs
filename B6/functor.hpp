#ifndef __FUNCTOR_HPP__
#define __FUNCTOR_HPP__

#include <cstddef>
#include <iostream>

class Functor
{
public:
  void operator()(long long elem) noexcept;

  void printInfo(std::ostream& outStream) const noexcept;

private:
  bool isWasData_ = false;
  long long max_;
  long long min_;
  size_t cntAll_ = 0;
  size_t cntPositive_ = 0;
  size_t cntNegative_ = 0;
  long long oddSum_ = 0;
  long long evenSum_ = 0;
  long long firstElem_;
  bool firstAndLastEqual_;
};

#endif
