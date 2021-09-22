#ifndef __BASE_TYPES_HPP__
#define __BASE_TYPES_HPP__

struct point_t
{
  double x = 0.0;
  double y = 0.0;
};

struct rectangle_t
{
  point_t pos;
  double width;
  double height;
};

#endif // !__BASE_TYPES_HPP__
