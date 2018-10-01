#include "Triangle.hpp"
#include <cmath>
namespace myPolygons {
  Triangle::Triangle(const myPoint::Point a, const myPoint::Point b, const myPoint::Point c) : Polygon() {
    vecCoordinates.push_back(a);
    vecCoordinates.push_back(b);
    vecCoordinates.push_back(c);
  }
  double Triangle::getArea() const {
    double area;
    area = ((vecCoordinates[0].x - vecCoordinates[2].x)*(vecCoordinates[1].y - vecCoordinates[2].y));
    area -= ((vecCoordinates[1].x - vecCoordinates[2].x)*(vecCoordinates[0].y - vecCoordinates[3].y));
    area /= 2;
	if(area > 0) {
	  return area;
	} else {
	  return -area;
	}
  }
  std::string Triangle::getFigureType() const {
    return "Triangle";
  }
  myPoint::Point Triangle::getMediansXingPoint() const {
	myPoint::Point tempPoint;
	tempPoint.x = (vecCoordinates[0].x + vecCoordinates[1].x + vecCoordinates[2].x) / 3;
	tempPoint.y = (vecCoordinates[0].y + vecCoordinates[1].y + vecCoordinates[2].y) / 3;
	return tempPoint;
  }
  double Triangle::getMedianLength(const unsigned medNumber) const {
	double xm, ym;
	switch(medNumber) {
	case 0:
	  xm = (vecCoordinates[1].x + vecCoordinates[2].x) / 2;
	  ym = (vecCoordinates[1].y + vecCoordinates[2].y) / 2;
	  return hypot(xm - vecCoordinates[0].x, ym - vecCoordinates[0].y);
	break;
	case 1:
	  xm = (vecCoordinates[0].x + vecCoordinates[2].x) / 2;
	  ym = (vecCoordinates[0].y + vecCoordinates[2].y) / 2;
	  return hypot(xm - vecCoordinates[1].x, ym - vecCoordinates[1].y);
	break;
	case 2:
	  xm = (vecCoordinates[1].x + vecCoordinates[0].x) / 2;
	  ym = (vecCoordinates[1].y + vecCoordinates[0].y) / 2;
	  return hypot(xm - vecCoordinates[2].x, ym - vecCoordinates[2].y);
	break;
	default:
	  std::cout << "Error: median's number must be between 0 and 2\n";
	  return -1;
	break;
	}
	
  }
  myPoint::Point Triangle::getBisectorsXingPoint() const {
	myPoint::Point tempPoint;
	tempPoint.x = 0;
	tempPoint.y = 0;
	return tempPoint; //TODO
  }
  double Triangle::getBisectorLength(const unsigned bisNumber) const {
	return 0; //TODO
  }
  myPoint::Point Triangle::getPerpendicularsXingPoint() const {
	myPoint::Point tempPoint;
	tempPoint.x = 0;
	tempPoint.y = 0;
	return tempPoint; //TODO
  }
}