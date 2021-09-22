#include "person.hpp"

Person::Person(std::string number, std::string name) :
  number_(std::move(number)),
  name_(std::move(name))
{}

const std::string& Person::getNumber() const noexcept
{
  return number_;
}

const std::string& Person::getName() const noexcept
{
  return name_;
}

void Person::emplaceBackLinkToPerson(const std::string& markNamePointer)
{
  linksToPerson_.emplace(&markNamePointer);
}

void Person::eraseLinkFromPerson(const std::string* markNamePointer)
{
  linksToPerson_.erase(markNamePointer);
}

Person::SetIterator Person::begin() noexcept
{
  return linksToPerson_.begin();
}

Person::SetIterator Person::end() noexcept
{
  return linksToPerson_.end();
}

Person::ConstSetIterator Person::cbegin() const noexcept
{
  return linksToPerson_.cbegin();
}

Person::ConstSetIterator Person::cend() const noexcept
{
  return linksToPerson_.cend();
}
