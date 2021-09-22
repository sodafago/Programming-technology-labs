#include "ostream-iterator.hpp"

text::OstreamIterator::OstreamIterator(std::ostream& outStream, size_t lineWidth) :
  data_(std::make_shared<Data>(outStream, lineWidth))
{
  if (lineWidth == 0)
  {
    throw std::invalid_argument("Invalid field \"lineWidth\"");
  }
}

text::OstreamIterator::~OstreamIterator() noexcept
{
  flushLine_();
}

text::OstreamIterator& text::OstreamIterator::operator=(text::LexicalUnit lexicalUnit)
{
  static size_t SPACE_LENGTH = 1;
  if (data_->curLine_.empty())
  {
    if (data_->lineWidth_ < lexicalUnit.getSize())
    {
      throwExceptionLineWidth_();
    }
    data_->curLine_.emplace_back(std::move(lexicalUnit));
    data_->curLineSumWidth_ += data_->curLine_.back().getSize();
  }
  else
  {
    if (lexicalUnit.getType() == LexicalUnit::PUNCTUATION)
    {
      if (data_->curLineSumWidth_ + lexicalUnit.getSize() <= data_->lineWidth_)
      {
        data_->curLine_.emplace_back(std::move(lexicalUnit));
        data_->curLineSumWidth_ += data_->curLine_.back().getSize();
      }
      else
      {
        decltype(data_->curLine_) newCurLine;
        size_t newCurLineSumWidth = 0;
        newCurLine.emplace_back(data_->curLine_.back());
        newCurLineSumWidth += newCurLine.back().getSize();
        newCurLine.emplace_back(std::move(lexicalUnit));
        newCurLineSumWidth += newCurLine.back().getSize();
        if (newCurLineSumWidth > data_->lineWidth_)
        {
          throwExceptionLineWidth_();
        }
        data_->curLine_.pop_back();
        flushLine_();
        data_->curLine_ = std::move(newCurLine);
        data_->curLineSumWidth_ = newCurLineSumWidth;
      }
    }
    else if (lexicalUnit.getType() == LexicalUnit::DASH)
    {
      if (data_->curLineSumWidth_ + SPACE_LENGTH + lexicalUnit.getSize() <= data_->lineWidth_)
      {
        data_->curLine_.emplace_back(LexicalUnit(" ", LexicalUnit::SPACE));
        data_->curLine_.emplace_back(std::move(lexicalUnit));
        data_->curLineSumWidth_ += SPACE_LENGTH + data_->curLine_.back().getSize();
      }
      else
      {
        decltype(data_->curLine_) newCurLine;
        size_t newCurLineSumWidth = 0;
        auto itEnd = std::prev(data_->curLine_.end());
        newCurLine.emplace_front(*itEnd);
        newCurLineSumWidth += itEnd->getSize();
        if (itEnd->getType() == LexicalUnit::PUNCTUATION)
        {
          --itEnd;
          newCurLine.emplace_front(*itEnd);
          newCurLineSumWidth += itEnd->getSize();
        }
        newCurLine.emplace_back(LexicalUnit(" ", LexicalUnit::SPACE));
        newCurLineSumWidth += newCurLine.back().getSize();
        newCurLine.emplace_back(std::move(lexicalUnit));
        newCurLineSumWidth += newCurLine.back().getSize();
        if (newCurLineSumWidth > data_->lineWidth_)
        {
          throwExceptionLineWidth_();
        }
        for (auto it = itEnd; it != data_->curLine_.end(); it = data_->curLine_.erase(it))
        {}
        flushLine_();
        data_->curLine_ = std::move(newCurLine);
        data_->curLineSumWidth_ = newCurLineSumWidth;
      }
    }
    else
    {
      if (data_->curLineSumWidth_ + SPACE_LENGTH + lexicalUnit.getSize() <= data_->lineWidth_)
      {
        data_->curLine_.emplace_back(LexicalUnit(" ", LexicalUnit::SPACE));
        data_->curLine_.emplace_back(std::move(lexicalUnit));
        data_->curLineSumWidth_ += SPACE_LENGTH + data_->curLine_.back().getSize();
      }
      else
      {
        decltype(data_->curLine_) newCurLine;
        size_t newCurLineSumWidth = 0;
        newCurLine.emplace_back(std::move(lexicalUnit));
        newCurLineSumWidth += newCurLine.back().getSize();
        flushLine_();
        data_->curLine_ = std::move(newCurLine);
        data_->curLineSumWidth_ = newCurLineSumWidth;
      }
    }
  }

  return *this;
}

text::OstreamIterator& text::OstreamIterator::operator*() noexcept
{
  return *this;
}

text::OstreamIterator& text::OstreamIterator::operator++() noexcept
{
  return *this;
}

text::OstreamIterator& text::OstreamIterator::operator++(int) noexcept
{
  return *this;
}

text::OstreamIterator::Data::Data(std::ostream& outStream, size_t lineWidth) :
  outStream_(outStream),
  lineWidth_(lineWidth),
  curLineSumWidth_(0)
{}

void text::OstreamIterator::flushLine_() noexcept
{
  while (!data_->curLine_.empty() && data_->curLine_.back().getType() == LexicalUnit::SPACE)
  {
    data_->curLine_.pop_back();
  }
  if (data_->curLine_.empty())
  {
    return;
  }
  for (auto it = data_->curLine_.begin(); it != data_->curLine_.end(); it = data_->curLine_.erase(it))
  {
    data_->outStream_ << *it;
  }
  data_->outStream_ << '\n';
  data_->outStream_.flush();
  data_->curLineSumWidth_ = 0;
}

void text::OstreamIterator::throwExceptionLineWidth_()
{
  throw std::logic_error("Impossible print text with current \"lineWidth\"");
}
