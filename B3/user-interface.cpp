#include "user-interface.hpp"

#include <sstream>
#include <string>
#include <regex>
#include <map>

#include "phone-book.hpp"

UserInterface::UserInterface(std::istream& in, std::ostream& out, PhoneBook& phoneBook) :
  inStream_(in),
  outStream_(out),
  phoneBook_(phoneBook)
{}

bool UserInterface::isNextCommandExist()
{
  inStream_ >> std::ws;

  return !inStream_.eof();
}

void UserInterface::runNextCommand()
{
  static std::map<std::string, void(UserInterface::*)(std::stringstream&)> commands =
  {
    { "add", &UserInterface::runCommandAdd_ },
    { "store", &UserInterface::runCommandStore_ },
    { "insert", &UserInterface::runCommandInsert_ },
    { "delete", &UserInterface::runCommandDelete_ },
    { "show", &UserInterface::runCommandShow_ },
    { "move", &UserInterface::runCommandMove_ }
  };

  std::string line;
  std::getline(inStream_, line);
  std::stringstream stream(line);
  auto command = readNextBlockSymbols_(stream);
  if (!command.second || !commands.count(command.first))
  {
    printInvalidCommand_();
  }
  else
  {
    (this->*commands[command.first])(stream);
  }
}

void UserInterface::runCommandAdd_(std::stringstream& stream)
{
  auto number = readNumber_(stream);
  auto name = readName_(stream);
  if (!number.second || !name.second)
  {
    printInvalidCommand_();
  }
  else
  {
    phoneBook_.emplaceBack(number.first, name.first);
  }
}

void UserInterface::runCommandStore_(std::stringstream& stream)
{
  auto markName = readExistMarkName_(stream);
  auto newMarkName = readMarkName_(stream);
  if (!markName.second || !newMarkName.second)
  {
    printInvalidCommandOrInvalidBookMark_(markName.first);
  }
  else
  {
    phoneBook_.emplaceMark(markName.first, newMarkName.first);
  }
}

void UserInterface::runCommandInsert_(std::stringstream& stream)
{
  auto where = readNextBlockSymbols_(stream);
  auto markName = readExistMarkName_(stream);
  auto number = readNumber_(stream);
  auto name = readName_(stream);
  if (!where.second || !markName.second || !number.second || !name.second)
  {
    printInvalidCommandOrInvalidBookMark_(markName.first);
  }
  else if (where.first == "before")
  {
    phoneBook_.emplaceBeforeMarkName(markName.first, number.first, name.first);
  }
  else if (where.first == "after")
  {
    phoneBook_.emplaceAfterMarkName(markName.first, number.first, name.first);
  }
  else
  {
    printInvalidCommand_();
  }
}

void UserInterface::runCommandDelete_(std::stringstream& stream)
{
  auto markName = readExistMarkName_(stream);
  if (!markName.second)
  {
    printInvalidCommandOrInvalidBookMark_(markName.first);
  }
  else
  {
    phoneBook_.deleteMarkName(markName.first);
  }
}

void UserInterface::runCommandShow_(std::stringstream& stream)
{
  auto markName = readExistMarkName_(stream);
  if (!markName.second)
  {
    printInvalidCommandOrInvalidBookMark_(markName.first);
  }
  else if (phoneBook_.isMarkValid(markName.first))
  {
    phoneBook_.showRecordByMarkName(outStream_, markName.first);
  }
  else
  {
    outStream_ << "<EMPTY>\n";
  }
}

void UserInterface::runCommandMove_(std::stringstream& stream)
{
  auto markName = readExistMarkName_(stream);
  auto steps = readNextBlockSymbols_(stream);
  if (!markName.second || !steps.second)
  {
    printInvalidCommandOrInvalidBookMark_(markName.first);
  }
  else if (steps.first == "first" || steps.first == "last")
  {
    phoneBook_.moveMarkName(markName.first, steps.first);
  }
  else if (isNumericStepsCorrect_(steps.first))
  {
    phoneBook_.moveMarkName(markName.first, std::stoll(steps.first));
  }
  else
  {
    outStream_ << "<INVALID STEP>\n";
  }
}

void UserInterface::printInvalidCommand_()
{
  outStream_ << "<INVALID COMMAND>\n";
}

void UserInterface::printInvalidCommandOrInvalidBookMark_(const std::string& markName)
{
  if (phoneBook_.isMarkExist(markName))
  {
    printInvalidCommand_();
  }
  else
  {
    outStream_ << "<INVALID BOOKMARK>\n";
  }
}

std::pair<std::string, bool> UserInterface::readExistMarkName_(std::stringstream& stream)
{
  auto res = readMarkName_(stream);
  if (!phoneBook_.isMarkExist(res.first))
  {
    res.second = false;
  }

  return res;
}

std::pair<std::string, bool> UserInterface::readMarkName_(std::stringstream& stream)
{
  auto res = readNextBlockSymbols_(stream);
  if (!isMarkNameCorrect_(res.first))
  {
    res.second = false;
  }

  return res;
}

std::pair<std::string, bool> UserInterface::readNextBlockSymbols_(std::stringstream& stream)
{
  std::pair<std::string, bool> res(std::string(), false);
  stream >> std::ws;
  if (stream.eof())
  {
    return res;
  }
  stream >> res.first;
  res.second = true;

  return res;
}

std::pair<std::string, bool> UserInterface::readName_(std::stringstream& stream)
{
  std::pair<std::string, bool> res(std::string(), false);
  stream >> std::ws;
  if (stream.eof())
  {
    return res;
  }
  std::getline(stream, res.first);
  if (isNameCorrect_(res.first))
  {
    reformatName_(res.first);
    res.second = true;
  }

  return res;
}

std::pair<std::string, bool> UserInterface::readNumber_(std::stringstream& stream)
{
  auto res = readNextBlockSymbols_(stream);
  if (!isNumberCorrect_(res.first))
  {
    res.second = false;
  }

  return res;
}

bool UserInterface::isNameCorrect_(const std::string& name)
{
  static std::regex goodName(R"("([^\\]*(\\")*[^\\]*)+")");
  static const int MIN_SYMBOLS_IN_NAME = 3;

  return std::regex_match(name, goodName) && name.size() >= MIN_SYMBOLS_IN_NAME;
}

bool UserInterface::isNumberCorrect_(const std::string& number)
{
  return std::all_of(number.begin(), number.end(), [](char c)
  {
    return isdigit(c);
  });
}

bool UserInterface::isMarkNameCorrect_(const std::string& markName)
{
  static std::regex goodMarkName(R"([\d\-a-zA-Z]+)");
  return std::regex_match(markName, goodMarkName);
}

bool UserInterface::isNumericStepsCorrect_(const std::string& steps)
{
  static std::regex goodSteps(R"([-+]?\d+)");

  return std::regex_match(steps, goodSteps);
}

void UserInterface::reformatName_(std::string& name)
{
  name = name.substr(1, name.size() - 2);
  static std::regex backSlashBeforeQuotes(R"(\\")");
  name = std::regex_replace(name, backSlashBeforeQuotes, "\"");
}
