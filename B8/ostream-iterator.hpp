#ifndef __OSTREAM_ITERATOR_HPP__
#define __OSTREAM_ITERATOR_HPP__

#include <iterator>
#include <list>
#include <memory>

#include "lexical-unit.hpp"

namespace text
{
  class OstreamIterator;
}

class text::OstreamIterator : public std::iterator<std::output_iterator_tag, LexicalUnit>
{
public:
  OstreamIterator(std::ostream& outStream, size_t lineWidth);

  ~OstreamIterator() noexcept;

  OstreamIterator& operator=(LexicalUnit lexicalUnit);

  OstreamIterator& operator*() noexcept;

  OstreamIterator& operator++() noexcept;

  OstreamIterator& operator++(int) noexcept;

private:
  struct Data
  {
    std::ostream& outStream_;
    size_t lineWidth_;
    size_t curLineSumWidth_;
    std::list<LexicalUnit> curLine_;

    Data(std::ostream& outStream, size_t lineWidth);
  };

  std::shared_ptr<Data> data_;

  void flushLine_() noexcept;

  static void throwExceptionLineWidth_();
};

#endif
