#ifndef _RECTANGLE_HPP_
#define _RECTANGLE_HPP_
#include "Polygon.hpp"

namespace myPolygons {
  class Rectangle : public Polygon {
  public:
    Rectangle(const myPoint::Point a, const myPoint::Point b);
    ~Rectangle() {
      //std::cout << "Calling ~Rectangle()" << std::endl;
      }
    double getArea() const;
    std::string getFigureType() const;
    double getDiagLength() const;
    
  private:
    
  };
}



#endif //#ifndef _RECTANGLE_HPP_
