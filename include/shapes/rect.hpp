#pragma once

class Rect {

private:
  float _x;
  float _y;
  float _width;
  float _height;

public:
  Rect(float x, float y, float width, float height);

  /**
   *  @brief Function to read rect properties.
   *  @return value at index n in tuple (x, y, width, height)
   */
  float operator[](unsigned int n) const;
};
