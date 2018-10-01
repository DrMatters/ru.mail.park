#ifndef _TRIANGLE_HPP_
#define _TRIANGLE_HPP_
#include "Polygon.hpp"


namespace myPolygons {
  class Triangle : public Polygon {
  public:
    Triangle(const myPoint::Point a, const myPoint::Point b, const myPoint::Point c);
    ~Triangle() {
      //std::cout << "Calling ~Triangle()" << std::endl;
	  }
    double getArea() const;
    std::string getFigureType() const;
	myPoint::Point getMediansXingPoint() const;
	double getMedianLength(const unsigned medNumber) const;
	myPoint::Point getBisectorsXingPoint() const;
	double getBisectorLength(const unsigned bisNumber) const;
	myPoint::Point getPerpendicularsXingPoint() const;
  private:
    
  };
}



#endif // #ifndef _TRIANGLE_HPP_
