
#include "Polygon.hpp"
#include "Triangle.hpp"
#include "Rectangle.hpp"
#include <ctime>
#include <cstdlib>
#include <algorithm>

myPolygons::Polygon* polygonDerivedsFactory();
myPolygons::Triangle* trianglesFactory();
myPolygons::Rectangle* rectanglesFactory();
myPoint::Point randPoint();
using std::cout;
using std::endl;
int main(int argc, char **argv)
{
    srand(time(NULL));
	std::vector<myPolygons::Polygon*> vecPoiPoly;
	for(int i = 0; i < 10; i++) {
	  vecPoiPoly.push_back(polygonDerivedsFactory());
	}
	
	for(size_t i = 0; i < vecPoiPoly.size(); ++i) {
	  cout << vecPoiPoly[i]->getFigureType() << " #" << i << endl;
	  cout << "Area = " << vecPoiPoly[i]->getArea() << endl;
	}
	
	for(size_t i = 0; i < vecPoiPoly.size(); ++i) {
	  if(vecPoiPoly[i]->getFigureType() == "Rectangle") {
		myPolygons::Rectangle* pRec = dynamic_cast<myPolygons::Rectangle*> (vecPoiPoly[i]);
		cout << pRec->getDiagLength() << endl;
	  } else if(vecPoiPoly[i]->getFigureType() == "Triangle") {
		myPolygons::Triangle* pTri = dynamic_cast<myPolygons::Triangle*> (vecPoiPoly[i]);
		cout << pTri->getMediansXingPoint() << endl;
	  }
	}
	for(size_t i = 0; i < vecPoiPoly.size(); ++i) {
	  delete vecPoiPoly[i];
	}
	
	return 0;
}
myPolygons::Polygon* polygonDerivedsFactory() {
  unsigned sClass;
  sClass = rand() % 2;
  switch(sClass) {
  case 0:
	return trianglesFactory();
	break;
  case 1:
	return rectanglesFactory();
	break;
  default: 
	cout << "This point of code must not be reached\n";
	exit(EXIT_FAILURE);
  }
}
myPoint::Point randPoint() {
  myPoint::Point toReturn;
  toReturn.x = rand() % 255;
  toReturn.y = rand() % 255;
  return toReturn;
}
myPolygons::Triangle* trianglesFactory() {
  myPolygons::Triangle* toReturn = new myPolygons::Triangle(randPoint(), randPoint(), randPoint());
  return toReturn;
}
myPolygons::Rectangle* rectanglesFactory() {
  myPolygons::Rectangle* toReturn = new myPolygons::Rectangle(randPoint(), randPoint());
  return toReturn;
}