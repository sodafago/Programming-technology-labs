#include "data-struct.hpp"

#include <iostream>

namespace detail
{
  bool isKeyCorrect(int key)
  {
    static const int MIN_VALUE = -5;
    static const int MAX_VALUE = 5;

    return MIN_VALUE <= key && key <= MAX_VALUE;
  }

  std::istream& ignoreLine(std::istream& inStream)
  {
    while (!inStream.eof() && inStream.peek() != '\n')
    {
      inStream.ignore();
    }

    if (!inStream.eof())
    {
      inStream.ignore();
    }

    return inStream;
  }

  std::istream& ignoreSpacesAndTabs(std::istream& inStream)
  {
    while (!inStream.eof() && (inStream.peek() == ' ' || inStream.peek() == '\t'))
    {
      inStream.ignore();
    }

    return inStream;
  }

  bool isReadKey(std::istream& inStream, int& key)
  {
    inStream >> ignoreSpacesAndTabs;

    if (inStream.eof() || inStream.peek() == '\n')
    {
      inStream >> ignoreLine;
      inStream.setstate(std::ios::failbit);

      return false;
    }

    inStream >> key;

    if (inStream.fail())
    {
      inStream >> ignoreLine;

      return false;
    }

    if (!isKeyCorrect(key))
    {
      inStream >> ignoreLine;
      inStream.setstate(std::ios::failbit);

      return false;
    }

    if (inStream.peek() != ',')
    {
      inStream >> ignoreLine;
      inStream.setstate(std::ios::failbit);

      return false;
    }
    inStream.ignore();

    return true;
  }
}

bool DataStruct::Comparator::operator()(const DataStruct& first, const DataStruct& second) const noexcept
{
  if (first.key1 != second.key1)
  {
    return first.key1 < second.key1;
  }
  if (first.key2 != second.key2)
  {
    return first.key2 < second.key2;
  }
  return first.str.size() < second.str.size();
}

std::istream& operator>>(std::istream& inStream, DataStruct& data)
{
  int key1;
  int key2;
  std::string str;

  inStream >> std::ws;

  if (inStream.eof())
  {
    inStream.setstate(std::ios::failbit);

    return inStream;
  }

  if (!detail::isReadKey(inStream, key1) || !detail::isReadKey(inStream, key2))
  {
    return inStream;
  }

  inStream >> detail::ignoreSpacesAndTabs;

  if (inStream.eof() || inStream.peek() == '\n')
  {
    inStream >> detail::ignoreLine;
    inStream.setstate(std::ios::failbit);

    return inStream;
  }

  std::getline(inStream, str);

  if (inStream.fail())
  {
    return inStream;
  }

  data.key1 = key1;
  data.key2 = key2;
  data.str = std::move(str);

  return inStream;
}

std::ostream& operator<<(std::ostream& outStream, const DataStruct& data)
{
  outStream << data.key1 << ", " << data.key2 << ", " << data.str;

  return outStream;
}
