#define __FILENAME__ "Rect"

#include <string>

#include "shapes/rect.hpp"
#include "utils/log.hpp"

Rect::Rect(float x, float y, float width, float height)
    : _x(x), _y(y), _width(width), _height(height) {}

float Rect::operator[](unsigned int n) const {
  switch (n) {
  case 0:
    return _x;
  case 1:
    return _y;
  case 2:
    return _width;
  case 3:
    return _height;
  default:
    Log::error(__FILENAME__, "Index out of bound " + std::to_string(n));
    return 0;
  }
}
