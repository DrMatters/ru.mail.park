#include "Point.hpp"

namespace myPoint {
  Point& Point::operator=(const Point& other) {
    x = other.x;
    y = other.y;
    return *this;
  }
  std::ostream& operator<<(std::ostream& stream, Point obj) {
    stream << "[" << obj.x << "]";
    stream << " [" << obj.y << "]";
    return stream;
  }
}