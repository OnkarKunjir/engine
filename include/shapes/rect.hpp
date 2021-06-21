#pragma once

#include "render/buffer.hpp"
#include "render/bufferlayout.hpp"
#include "render/vertexarray.hpp"

class Rect {

private:
  Buffer _vertex;
  Buffer _index;
  BufferLayout _layout;
  VertexArray _vao;

public:
  Rect(float x, float y, float width, float height, float z = 0.0f);
  void draw();
};
