#pragma once

class Rect {

private:
  float _x;
  float _y;
  float _width;
  float _height;

public:
  Rect(float x, float y, float width, float height);

  float operator[](unsigned int n) const;
};
