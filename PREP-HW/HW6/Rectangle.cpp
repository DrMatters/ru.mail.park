#include "Rectangle.hpp"
#include <cmath>
namespace myPolygons {
  Rectangle::Rectangle(const myPoint::Point a, const myPoint::Point b)
                  : Polygon() {
    vecCoordinates.push_back(a);
    vecCoordinates.push_back(b);
  }
  double Rectangle::getArea() const {
    double temp;
    temp = (vecCoordinates[0].x - vecCoordinates[1].x)*(vecCoordinates[0].y - vecCoordinates[1].y);
    if(temp >= 0) {
      return temp;
    } else {
      return -temp;
    }
  }
  std::string Rectangle::getFigureType() const {
    return "Rectangle";
  }
  double Rectangle::getDiagLength() const {
    return hypot(vecCoordinates[0].x - vecCoordinates[1].x, vecCoordinates[0].y - vecCoordinates[2].y);
  }
  
}