#ifndef __PHONEBOOK_HPP__
#define __PHONEBOOK_HPP__

#include <string>
#include <map>
#include <list>

#include "person.hpp"

class PhoneBook
{
public:
  PhoneBook();

  PhoneBook(const PhoneBook& copy) = delete;

  PhoneBook(PhoneBook&& move) noexcept = default;

  ~PhoneBook() = default;

  PhoneBook& operator=(const PhoneBook& copy) = delete;

  PhoneBook& operator=(PhoneBook&& move) noexcept = default;

  void emplaceBack(std::string number, std::string name);

  void emplaceMark(const std::string& markName, std::string newMarkName);

  void emplaceBeforeMarkName(const std::string& markName, std::string number, std::string name);

  void emplaceAfterMarkName(const std::string& markName, std::string number, std::string name);

  void deleteMarkName(const std::string& markName);

  void showRecordByMarkName(std::ostream& outStream, const std::string& markName);

  void moveMarkName(const std::string& markName, long long steps);

  void moveMarkName(const std::string& markName, const std::string& pos);

  void moveMarkNameToNext(const std::string& markName);

  void moveMarkNameToPrev(const std::string& markName);

  bool isMarkExist(const std::string& markName) const noexcept;

  bool isMarkValid(const std::string& markName) const noexcept;

private:
  using ListIterator = std::list<Person>::iterator;

  std::list<Person> persons_;
  std::map<std::string, ListIterator> markNames_;
  static const char* CURRENT_;

  void emplaceBeforeIterator_(ListIterator iter, std::string number, std::string name);

  void moveMarkName_(const std::string& markName, ListIterator where);

  void throwExceptionIfMarkNotExist_(const std::string& markName) const;

  ListIterator tryGetListIteratorByMarkName_(const std::string& markName);

  ListIterator getAdvancedIterator_(ListIterator it, long long shift) noexcept;

  ListIterator getNextValidIterator_(ListIterator it) noexcept;

  ListIterator getFirstIterator_() noexcept;

  ListIterator getLastIterator_() noexcept;
};

#endif
