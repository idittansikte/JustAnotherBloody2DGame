#ifndef RECT_H
#define RECT_H

struct Rect
{
  
  Rect()
  {
    x = y = w = h = 0;
  }
  
  Rect(int _x, int _y)
  {
    x = _x;
    y = _y;
    w = h = 0;
  }
  
  Rect( int _x, int _y, int _w, int _h )
  {
    x = _x;
    y = _y;
    w = _w;
    h = _h;
  }
  
  int x, y, w, h;
  
};

#endif