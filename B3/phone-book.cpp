#include "phone-book.hpp"

#include <iostream>
#include <stdexcept>

const char* PhoneBook::CURRENT_ = "current";

PhoneBook::PhoneBook()
{
  markNames_[CURRENT_] = persons_.end();
}

void PhoneBook::emplaceBack(std::string number, std::string name)
{
  emplaceBeforeIterator_(persons_.end(), std::move(number), std::move(name));
}

void PhoneBook::emplaceMark(const std::string& markName, std::string newMarkName)
{
  auto listIt = tryGetListIteratorByMarkName_(markName);
  auto info = markNames_.emplace(std::move(newMarkName), listIt);
  if (info.second)
  {
    try
    {
      listIt->emplaceBackLinkToPerson(info.first->first);
    }
    catch (...)
    {
      markNames_.erase(info.first);
      throw;
    }
  }
}

void PhoneBook::emplaceBeforeMarkName(const std::string& markName, std::string number, std::string name)
{
  auto listIt = tryGetListIteratorByMarkName_(markName);
  emplaceBeforeIterator_(listIt, std::move(number), std::move(name));
}

void PhoneBook::emplaceAfterMarkName(const std::string& markName, std::string number, std::string name)
{
  auto listIt = getAdvancedIterator_(tryGetListIteratorByMarkName_(markName), 1);
  emplaceBeforeIterator_(listIt, std::move(number), std::move(name));
}

void PhoneBook::deleteMarkName(const std::string& markName)
{
  auto listIt = tryGetListIteratorByMarkName_(markName);
  if (listIt != persons_.end())
  {
    auto nextValid = getNextValidIterator_(listIt);
    if (nextValid != persons_.end())
    {
      Person temp(*nextValid);
      for (auto el : *listIt)
      {
        temp.emplaceBackLinkToPerson(*el);
      }
      *nextValid = std::move(temp);
    }
    for (auto& el : *listIt)
    {
      markNames_[*el] = nextValid;
    }
    persons_.erase(listIt);
  }
}

void PhoneBook::showRecordByMarkName(std::ostream& outStream, const std::string& markName)
{
  auto listIt = tryGetListIteratorByMarkName_(markName);
  if (listIt == persons_.end())
  {
    throw std::logic_error("mark-name \"" + markName + "\" point to end-iterator!");
  }
  else
  {
    outStream << listIt->getNumber() << ' ' << listIt->getName() << '\n';
  }
}

void PhoneBook::moveMarkName(const std::string& markName, long long steps)
{
  auto listIt = tryGetListIteratorByMarkName_(markName);
  moveMarkName_(markName, getAdvancedIterator_(listIt, steps));
}

void PhoneBook::moveMarkName(const std::string& markName, const std::string& pos)
{
  if (pos == "first")
  {
    moveMarkName_(markName, getFirstIterator_());
  }
  else if (pos == "last")
  {
    moveMarkName_(markName, getLastIterator_());
  }
  else
  {
    throw std::invalid_argument(R"(The pos must be "first" or "last"!)");
  }
}

void PhoneBook::moveMarkNameToNext(const std::string& markName)
{
  moveMarkName(markName, 1);
}

void PhoneBook::moveMarkNameToPrev(const std::string& markName)
{
  moveMarkName(markName, -1);
}

bool PhoneBook::isMarkExist(const std::string& markName) const noexcept
{
  return markNames_.count(markName) > 0;
}

bool PhoneBook::isMarkValid(const std::string& markName) const noexcept
{
  return isMarkExist(markName) && markNames_.at(markName) != persons_.end();
}

void PhoneBook::emplaceBeforeIterator_(PhoneBook::ListIterator iter, std::string number, std::string name)
{
  bool isEmpty = persons_.empty();
  Person temp(std::move(number), std::move(name));
  if (isEmpty)
  {
    temp.emplaceBackLinkToPerson(markNames_.find(CURRENT_)->first);
  }
  persons_.emplace(iter, std::move(temp));
  if (isEmpty)
  {
    markNames_[CURRENT_] = persons_.begin();
  }
}

void PhoneBook::moveMarkName_(const std::string& markName, PhoneBook::ListIterator where)
{
  throwExceptionIfMarkNotExist_(markName);
  auto markIt = markNames_.find(markName);
  auto linkToMarkName = &markIt->first;
  auto listIt = markIt->second;
  if (listIt != persons_.end())
  {
    listIt->eraseLinkFromPerson(linkToMarkName);
  }
  if (where != persons_.end())
  {
    where->emplaceBackLinkToPerson(*linkToMarkName);
  }
  markIt->second = where;
}

void PhoneBook::throwExceptionIfMarkNotExist_(const std::string& markName) const
{
  if (!isMarkExist(markName))
  {
    throw std::invalid_argument("Mark-name \"" + markName + "\" isn't exist!");
  }
}

std::list<Person>::iterator PhoneBook::tryGetListIteratorByMarkName_(const std::string& markName)
{
  throwExceptionIfMarkNotExist_(markName);

  return markNames_.at(markName);
}

PhoneBook::ListIterator PhoneBook::getAdvancedIterator_(PhoneBook::ListIterator it, long long shift) noexcept
{
  bool isNegDir = shift < 0;
  shift = std::abs(shift);
  while (shift > 0 && (isNegDir || it != persons_.end()) && (!isNegDir || it != persons_.begin()))
  {
    --shift;
    if (isNegDir)
    {
      --it;
    }
    else
    {
      ++it;
    }
  }
  if (shift > 0)
  {
    it = persons_.end();
  }
  return it;
}

PhoneBook::ListIterator PhoneBook::getNextValidIterator_(PhoneBook::ListIterator it) noexcept
{
  if (persons_.size() == 1)
  {
    return persons_.end();
  }
  auto next = getAdvancedIterator_(it, 1);
  if (next == persons_.end())
  {
    return getAdvancedIterator_(it, -1);
  }
  else
  {
    return next;
  }
}

PhoneBook::ListIterator PhoneBook::getFirstIterator_() noexcept
{
  if (persons_.empty())
  {
    return persons_.end();
  }
  else
  {
    return persons_.begin();
  }
}

PhoneBook::ListIterator PhoneBook::getLastIterator_() noexcept
{
  if (persons_.empty())
  {
    return persons_.end();
  }
  else
  {
    return std::prev(persons_.end());
  }
}
