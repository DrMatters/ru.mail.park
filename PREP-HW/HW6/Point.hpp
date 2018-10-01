#ifndef _POINT_HPP_
#define _POINT_HPP_
#include <iostream>

namespace myPoint {
  class Point {
  public:
    double x;
    double y;
    //copy constructor is not requred, because
    //Point is copyConstructable according to implementation
    Point& operator=(const Point& other);
    friend std::ostream& operator<<(std::ostream &stream, Point obj);
  };
  
}



#endif //#IFNDEF _Point_HPP_