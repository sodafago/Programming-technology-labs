#include <iostream>
#include <exception>
#include <vector>
#include <algorithm>
#include <iterator>

#include "data-struct.hpp"

int main()
{
  try
  {
    std::vector<DataStruct> dataStructs((std::istream_iterator<DataStruct>(std::cin)), std::istream_iterator<DataStruct>());
    if (!std::cin.eof())
    {
      throw std::ios_base::failure("Input error!");
    }
    std::sort(dataStructs.begin(), dataStructs.end(), DataStruct::Comparator());
    std::copy(dataStructs.begin(), dataStructs.end(), std::ostream_iterator<DataStruct>(std::cout, "\n"));
  }
  catch (const std::exception& err)
  {
    std::cerr << err.what() << '\n';

    return 1;
  }
}
