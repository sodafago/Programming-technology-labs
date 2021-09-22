#ifndef __DATA_STRUCT_HPP__
#define __DATA_STRUCT_HPP__

#include <string>

struct DataStruct
{
  int key1;
  int key2;
  std::string str;

  class Comparator;
};

class DataStruct::Comparator
{
public:
  bool operator()(const DataStruct& first, const DataStruct& second) const noexcept;
};

std::istream& operator>>(std::istream& inStream, DataStruct& data);

std::ostream& operator<<(std::ostream& outStream, const DataStruct& data);

#endif
