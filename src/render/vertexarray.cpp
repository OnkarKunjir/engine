#include "render/buffer.hpp"
#include "render/bufferlayout.hpp"
#include "render/vertexarray.hpp"

#include <glad/gl.h>

VertexArray::VertexArray(Buffer &buffer, BufferLayout &layout) {
  glad_glGenVertexArrays(1, &_id);
  bind();
  buffer.bind();
  layout.bind();
}

VertexArray::~VertexArray() { glad_glDeleteVertexArrays(1, &_id); }

// public functions
void VertexArray::bind() const { glad_glBindVertexArray(_id); }
