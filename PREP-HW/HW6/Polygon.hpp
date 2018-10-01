#ifndef _POLYGON_HPP_
#define _POLYGON_HPP_ //нужна ли эта проверка, если есть namespace
#include <iostream>
#include <vector>
#include <string>
#include "Point.hpp"

namespace myPolygons {
  class Polygon {
  public:
	Polygon() {};
    virtual ~Polygon() {
      //std::cout << "Calling virtual ~Polygon" << std::endl;
      };
	virtual double getArea() const = 0;
	virtual std::string getFigureType() const = 0;
	const double getPerimeter() const;
	void showCoordinates(std::ostream& stream) const;
	//friend virtual? нельзя перегрузить оператор вывода стандартными методами
  protected:
	std::vector<myPoint::Point> vecCoordinates;
	//как подписывать тип контейнера?  /|\;
  };
}
#endif //#IFNDEF _POLYGON_HPP_
