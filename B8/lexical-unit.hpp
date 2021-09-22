#ifndef __LEXICAL_UNIT_HPP__
#define __LEXICAL_UNIT_HPP__

#include <iostream>
#include <string>

namespace text
{
  class LexicalUnit;
}

class text::LexicalUnit
{
public:
  class ValidateFunctor;

  enum type
  {
    WORD,
    PUNCTUATION,
    DASH,
    NUMBER,
    EMPTY,
    SPACE,
    INVALID
  };

  LexicalUnit();

  LexicalUnit(std::string data, type type);

  LexicalUnit(type type);

  friend std::istream& operator>>(std::istream& inStream, LexicalUnit& lexicalUnit);

  friend std::ostream& operator<<(std::ostream& outStream, const LexicalUnit& lexicalUnit);

  size_t getSize() const noexcept;

  type getType() const noexcept;

  const std::string& getData() const noexcept;

private:
  std::string data_;
  type type_;
};

class text::LexicalUnit::ValidateFunctor
{
public:
  ValidateFunctor();

  const LexicalUnit& operator()(const LexicalUnit& lexicalUnit);

private:
  bool isFirstLexicalUnit_;
  LexicalUnit last_;
};

#endif
