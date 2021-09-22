#include "functor.hpp"

#include <algorithm>

void Functor::operator()(long long elem) noexcept
{
  if (!isWasData_)
  {
    isWasData_ = true;
    max_ = elem;
    min_ = elem;
    firstElem_ = elem;
  }
  else
  {
    max_ = std::max(max_, elem);
    min_ = std::min(min_, elem);
  }
  ++cntAll_;
  cntPositive_ += (elem > 0 ? 1 : 0);
  cntNegative_ += (elem < 0 ? 1 : 0);
  (elem % 2 != 0 ? oddSum_ : evenSum_) += elem;
  firstAndLastEqual_ = firstElem_ == elem;
}

void Functor::printInfo(std::ostream& outStream) const noexcept
{
  if (!isWasData_)
  {
    outStream << "No Data\n";
  }
  else
  {
    outStream << "Max: " << max_ << '\n';
    outStream << "Min: " << min_ << '\n';
    outStream << "Mean: " << static_cast<double>(oddSum_ + evenSum_) / static_cast<double>(cntAll_) << '\n';
    outStream << "Positive: " << cntPositive_ << '\n';
    outStream << "Negative: " << cntNegative_ << '\n';
    outStream << "Odd Sum: " << oddSum_ << '\n';
    outStream << "Even Sum: " << evenSum_ << '\n';
    outStream << "First/Last Equal: " << (firstAndLastEqual_ ? "yes" : "no") << '\n';
  }
}
