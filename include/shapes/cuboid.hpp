#pragma once
#include "render/buffer.hpp"
#include "render/bufferlayout.hpp"
#include "render/vertexarray.hpp"

class Cuboid {
  Buffer _vertex;
  Buffer _index;
  BufferLayout _layout;
  VertexArray _vao;

public:
  Cuboid(float x, float y, float z, float length, float width, float height);

  void draw();
};
