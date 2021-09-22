#include "lexical-unit.hpp"

#include <stdexcept>
#include <algorithm>

const size_t MAX_SIZE_UNIT = 20;

std::string punctuationList = ".,!?:;";

class LexicalUnitReader
{
public:
  explicit LexicalUnitReader(std::istream& inStream);

  text::LexicalUnit getReadLexicalUnit();

private:
  std::istream& inStream_;

  void readWord_(std::string& word);

  void readNumber_(std::string& number);

  void readDash_(std::string& dash);
};

LexicalUnitReader::LexicalUnitReader(std::istream& inStream) :
  inStream_(inStream)
{}

text::LexicalUnit LexicalUnitReader::getReadLexicalUnit()
{
  if (inStream_.fail())
  {
    return text::LexicalUnit(text::LexicalUnit::INVALID);
  }
  inStream_ >> std::ws;
  if (inStream_.eof())
  {
    inStream_.setstate(std::ios::failbit);

    return text::LexicalUnit(text::LexicalUnit::INVALID);
  }
  std::string tempData;
  text::LexicalUnit::type tempType;
  tempData += static_cast<char>(inStream_.get());
  if (std::isalpha(tempData.back()))
  {
    readWord_(tempData);
    tempType = text::LexicalUnit::WORD;
  }
  else if (tempData.back() == '-' || tempData.back() == '+')
  {
    char nextChar = static_cast<char>(inStream_.get());
    if (inStream_.eof())
    {
      inStream_.setstate(std::ios::failbit);

      return text::LexicalUnit(text::LexicalUnit::INVALID);
    }
    tempData += nextChar;
    if (std::isdigit(tempData.back()))
    {
      readNumber_(tempData);
      tempType = text::LexicalUnit::NUMBER;
    }
    else if (tempData[0] == '-' && tempData.back() == '-')
    {
      readDash_(tempData);
      tempType = text::LexicalUnit::DASH;
    }
    else
    {
      return text::LexicalUnit(text::LexicalUnit::INVALID);
    }
  }
  else if (std::isdigit(tempData.back()))
  {
    readNumber_(tempData);
    tempType = text::LexicalUnit::NUMBER;
  }
  else if (std::find(punctuationList.begin(), punctuationList.end(), tempData.back()) != punctuationList.end())
  {
    tempType = text::LexicalUnit::PUNCTUATION;
  }
  else
  {
    return text::LexicalUnit(text::LexicalUnit::INVALID);
  }

  return text::LexicalUnit(std::move(tempData), tempType);
}

void LexicalUnitReader::readWord_(std::string& word)
{
  char nextChar = inStream_.peek();
  while (!inStream_.eof() && (std::isalpha(nextChar) || (nextChar == '-' && word.back() != '-')))
  {
    word += static_cast<char>(inStream_.get());
    nextChar = inStream_.peek();
  }
}

void LexicalUnitReader::readNumber_(std::string& number)
{
  bool isPointRead = false;
  char nextChar = inStream_.peek();
  while (!inStream_.eof() && (std::isdigit(nextChar) || (!isPointRead && nextChar == '.')))
  {
    number += static_cast<char>(inStream_.get());
    if (number.back() == '.')
    {
      isPointRead = true;
    }
    nextChar = inStream_.peek();
  }
}

void LexicalUnitReader::readDash_(std::string& dash)
{
  char nextChar = inStream_.peek();
  while (!inStream_.eof() && nextChar == '-')
  {
    dash += static_cast<char>(inStream_.get());
    nextChar = inStream_.peek();
  }
}

text::LexicalUnit::LexicalUnit() :
  type_(EMPTY)
{}

text::LexicalUnit::LexicalUnit(std::string data, text::LexicalUnit::type type) :
  data_(std::move(data)),
  type_(type)
{}

text::LexicalUnit::LexicalUnit(text::LexicalUnit::type type) :
  type_(type)
{}

namespace text
{
  std::istream& operator>>(std::istream& inStream, text::LexicalUnit& lexicalUnit)
  {
    LexicalUnitReader reader(inStream);
    lexicalUnit = reader.getReadLexicalUnit();

    return inStream;
  }

  std::ostream& operator<<(std::ostream& outStream, const text::LexicalUnit& lexicalUnit)
  {
    outStream << lexicalUnit.data_;

    return outStream;
  }
}

size_t text::LexicalUnit::getSize() const noexcept
{
  return data_.size();
}

text::LexicalUnit::type text::LexicalUnit::getType() const noexcept
{
  return type_;
}

const std::string& text::LexicalUnit::getData() const noexcept
{
  return data_;
}

text::LexicalUnit::ValidateFunctor::ValidateFunctor() :
  isFirstLexicalUnit_(true)
{}

const text::LexicalUnit& text::LexicalUnit::ValidateFunctor::operator()(const text::LexicalUnit& lexicalUnit)
{
  static const size_t DASH_SIZE = 3;
  if (isFirstLexicalUnit_)
  {
    isFirstLexicalUnit_ = false;
    if (lexicalUnit.getType() == PUNCTUATION || lexicalUnit.getType() == DASH)
    {
      throw std::invalid_argument("Text mustn't start with punctuation!");
    }
  }

  if (lexicalUnit.getType() == INVALID)
  {
    throw std::invalid_argument("Lexical unit is invalid!");
  }
  else if (lexicalUnit.getType() == EMPTY)
  {
    throw std::invalid_argument("Lexical unit is empty!");
  }
  else if (lexicalUnit.getSize() > MAX_SIZE_UNIT)
  {
    throw std::invalid_argument("Invalid size of lexical unit!");
  }
  else if (lexicalUnit.getType() == PUNCTUATION && (last_.getType() == PUNCTUATION || last_.getType() == DASH))
  {
    throw std::invalid_argument("Double punctuation!");
  }
  else if (lexicalUnit.getType() == DASH)
  {
    if ((last_.getType() == PUNCTUATION && last_.getData() != ",") || last_.getType() == DASH)
    {
      throw std::invalid_argument("Invalid punctuation before dash!");
    }
    else if (lexicalUnit.getSize() != DASH_SIZE)
    {
      throw std::invalid_argument("Invalid dash size!");
    }
  }
  last_ = lexicalUnit;

  return lexicalUnit;
}
