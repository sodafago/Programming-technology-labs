#ifndef __BASE_TYPES_HPP__
#define __BASE_TYPES_HPP__

namespace nigmatullin
{
  struct point_t
  {
    double x;
    double y;
  };

  struct rectangle_t
  {
    point_t pos;
    double width;
    double height;
  };
}

#endif // !__BASE_TYPES_HPP__
