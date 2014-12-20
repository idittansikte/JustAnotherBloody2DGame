#ifndef POINT_H
#define POINT_H

struct Point
{
  
  Point()
  {
    x = y = 0;
  }
  
  Point(int _x, int _y)
  {
    x = _x;
    y = _y;
  }
  
  int x, y;
  
};

#endif