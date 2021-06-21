#include "render/bufferlayout.hpp"
#include "shapes/rect.hpp"

Rect::Rect(float x, float y, float width, float height, float z)
    : _vertex(Buffer(GL_ARRAY_BUFFER, GL_STATIC_DRAW)), _layout(BufferLayout()),
      _index(Buffer(GL_ELEMENT_ARRAY_BUFFER, GL_STATIC_DRAW)),
      _vao(_vertex, _index, _layout) {

  _vao.bind();

  float vertex[] = {
      x,         y,          z, 1.0f, 1.0f, 1.0f, // 0
      x + width, y,          z, 1.0f, 1.0f, 1.0f, // 1
      x + width, y - height, z, 1.0f, 1.0f, 1.0f, // 2
      x,         y - height, z, 1.0f, 1.0f, 1.0f, // 3
  };
  unsigned int index[] = {0, 1, 2, 2, 3, 0};

  _vertex.data(sizeof(vertex), vertex);
  _index.data(sizeof(index), index);

  _layout.push_float(3);
  _layout.push_float(3);
  _layout.bind();

  _vao.unbind();
}

void Rect::draw() {
  _vao.bind();
  glad_glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
  _vao.unbind();
}
