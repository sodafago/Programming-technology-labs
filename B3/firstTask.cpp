#include "firstTask.hpp"

#include "user-interface.hpp"
#include "phone-book.hpp"

void runFirstTask()
{
  PhoneBook phoneBook;
  UserInterface anInterface(std::cin, std::cout, phoneBook);
  while (anInterface.isNextCommandExist())
  {
    anInterface.runNextCommand();
  }
}
