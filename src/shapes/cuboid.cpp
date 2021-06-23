#include "shapes/cuboid.hpp"

Cuboid::Cuboid(float x, float y, float z, float length, float width,
               float height)
    : _vertex(Buffer(GL_ARRAY_BUFFER, GL_STATIC_DRAW)),
      _index(Buffer(GL_ELEMENT_ARRAY_BUFFER, GL_STATIC_DRAW)),
      _vao(VertexArray(_vertex, _index, _layout)) {

  float vertex[] = {
      //          CO-ORDINATES           /     COLOR
      x,          y,          z,         1.0f, 1.0f, 1.0f, // 0
      x + length, y,          z,         1.0f, 1.0f, 1.0f, // 1
      x + length, y - height, z,         1.0f, 1.0f, 1.0f, // 2
      x,          y - height, z,         1.0f, 1.0f, 1.0f, // 3

      x,          y,          z + width, 1.0f, 1.0f, 1.0f, // 4
      x + length, y,          z + width, 1.0f, 1.0f, 1.0f, // 5
      x + length, y - height, z + width, 1.0f, 1.0f, 1.0f, // 6
      x,          y - height, z + width, 1.0f, 1.0f, 1.0f, // 7

  };

  unsigned int index[] = {
      0, 1, 2, 2, 3, 0, // front
      4, 5, 6, 6, 7, 4, // back
      0, 4, 7, 7, 3, 0, // left
      1, 5, 6, 6, 2, 1, // right
      0, 1, 5, 5, 4, 0, // top
      2, 3, 7, 7, 6, 2, // bottom
  };

  _vao.bind();

  _vertex.data(sizeof(vertex), vertex);
  _index.data(sizeof(index), index);

  _layout.push_float(3);
  _layout.push_float(3);
  _layout.bind();

  _vao.unbind();
}

void Cuboid::draw() {
  _vao.bind();
  glad_glDrawElements(GL_TRIANGLES, 6 * 6, GL_UNSIGNED_INT, nullptr);
  _vao.unbind();
}
