#ifndef __USER_INTERFACE_HPP__
#define __USER_INTERFACE_HPP__

#include <iostream>

class PhoneBook;

class UserInterface
{
public:
  UserInterface(std::istream& in, std::ostream& out, PhoneBook& phoneBook);

  bool isNextCommandExist();

  void runNextCommand();

private:
  std::istream& inStream_;
  std::ostream& outStream_;
  PhoneBook& phoneBook_;

  void runCommandAdd_(std::stringstream& stream);

  void runCommandStore_(std::stringstream& stream);

  void runCommandInsert_(std::stringstream& stream);

  void runCommandDelete_(std::stringstream& stream);

  void runCommandShow_(std::stringstream& stream);

  void runCommandMove_(std::stringstream& stream);

  void printInvalidCommand_();

  void printInvalidCommandOrInvalidBookMark_(const std::string& markName);

  std::pair<std::string, bool> readExistMarkName_(std::stringstream& stream);

  static std::pair<std::string, bool> readMarkName_(std::stringstream& stream);

  static std::pair<std::string, bool> readNextBlockSymbols_(std::stringstream& stream);

  static std::pair<std::string, bool> readName_(std::stringstream& stream);

  static std::pair<std::string, bool> readNumber_(std::stringstream& stream);

  static bool isNameCorrect_(const std::string& name);

  static bool isNumberCorrect_(const std::string& number);

  static bool isMarkNameCorrect_(const std::string& markName);

  static bool isNumericStepsCorrect_(const std::string& steps);

  static void reformatName_(std::string& name);
};

#endif
