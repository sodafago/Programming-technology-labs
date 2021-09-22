#ifndef __PERSON_HPP__
#define __PERSON_HPP__

#include <string>
#include <set>

class Person
{
public:
  using LinksToPersons = std::set<const std::string*>;
  using SetIterator = LinksToPersons::iterator;
  using ConstSetIterator = LinksToPersons::const_iterator;

  Person(std::string number, std::string name);

  const std::string& getNumber() const noexcept;

  const std::string& getName() const noexcept;

  void emplaceBackLinkToPerson(const std::string& markNamePointer);

  void eraseLinkFromPerson(const std::string* markNamePointer);

  SetIterator begin() noexcept;

  SetIterator end() noexcept;

  ConstSetIterator cbegin() const noexcept;

  ConstSetIterator cend() const noexcept;

private:
  std::string number_;
  std::string name_;
  std::set<const std::string*> linksToPerson_;
};

#endif
