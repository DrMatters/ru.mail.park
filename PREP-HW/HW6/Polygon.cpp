#include "Polygon.hpp"
#include <cmath>
namespace myPolygons {
  const double Polygon::getPerimeter() const {
	double temp = 0;
	for(size_t i = 0; i < vecCoordinates.size() - 1; i++) {
	  temp += hypot(vecCoordinates[i].x - vecCoordinates[i + 1].x,
			vecCoordinates[i].y - vecCoordinates[i + 1].y);
	}
	//нет проверок на переполнение, но в C++11 они есть
	return temp;
  }
  void Polygon::showCoordinates(std::ostream& stream) const {
	for(size_t i = 0; i < vecCoordinates.size(); i++) {
	  stream << vecCoordinates[i] << "\n";
	}
  }
}