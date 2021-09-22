#include "tasks.hpp"

#include <fstream>
#include <stdexcept>
#include <memory>

#include "helpfulFunctions.hpp"

void nigmatullin::task2(int nArgs, char* args[])
{
  if (nArgs != 3)
  {
    throw std::invalid_argument("Invalid number of arguments.");
  }

  std::ifstream file(args[2]);

  if (!file.is_open())
  {
    throw std::runtime_error("Couldn't open file.");
  }

  size_t fileAlloc = 15;
  size_t fileSize = 0;
  std::unique_ptr<char[]> arr = std::make_unique<char[]>(fileAlloc);

  while (!file.eof())
  {
    if (fileSize == fileAlloc)
    {
      std::unique_ptr<char[]> newArr = std::make_unique<char[]>(2 * fileAlloc);
      for (size_t i = 0; i < fileSize; ++i)
      {
        newArr[i] = arr[i];
      }
      fileAlloc *= 2;
      arr.swap(newArr);
    }
    arr[fileSize] = file.get();
    fileSize++;
  }

  if (!fileSize)
  {
    return;
  }

  file.close();
  std::vector<char> vec(arr.get(), arr.get() + fileSize - 1);
  print(vec, "", "");
}
