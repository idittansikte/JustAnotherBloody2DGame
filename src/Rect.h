#ifndef RECT_H
#define RECT_H

template<typename T>
struct Rect
{
  
  Rect()
  {
    x = y = w = h = 0;
  }
  
  Rect(T _x, T _y)
  {
    x = _x;
    y = _y;
    w = h = 0;
  }
  
  Rect( T _x, T _y, T _w, T _h )
  {
    x = _x;
    y = _y;
    w = _w;
    h = _h;
  }
  
  T x, y, w, h;
  
  T top = y;
  T bottom = y + h;
  T left = x;
  T right = x + w;
  
  bool operator==(const Rect<T> &other) const {
    if(this->x == other.x && this->y == other.y && this->w == other.w && this->h == other.h){
      return true;
    }
    return false;
  }
  
  Rect operator*(float x){
    Rect tmp;
    tmp.x = this->x + this->w * ( 1.0 - x );
    tmp.y = this->y + this->h * ( 1.0 - x );
    tmp.w = (this->w * x) - this->w * ( 1.0 - x );
    tmp.h = (this->h * x) - this->h * ( 1.0 - x );
    return tmp;
  }
  
  Rect operator=(const Rect<T> &other){
    this->x = other.x;
    this->y = other.y;
    this->w = other.w;
    this->h = other.h;
  }
  
};

#endif