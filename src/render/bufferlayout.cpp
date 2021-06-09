#include "render/bufferlayout.hpp"
#include "utils/log.hpp"

#include <glad/gl.h>
#include <vector>

BufferLayout::BufferLayout() : _stride(0) {}
BufferLayout::~BufferLayout() {}

void BufferLayout::push_float(int count, bool normalized) {
  // adds float attribute to the layout.
  Attribute a = {static_cast<int>(_attributes.size()), count, GL_FLOAT,
                 normalized, _stride};

  _attributes.push_back(a);
  _stride += sizeof(float) * count;
}

void BufferLayout::bind() const {
  // defines and activates all the attributes.
  for (int i = 0; i < _attributes.size(); i++) {
    const Attribute &a = _attributes[i];
    glad_glEnableVertexAttribArray(i);
    glad_glVertexAttribPointer(a.index, a.size, a.type, a.normalized, _stride,
                               (void *)(a.pointer));
  }
}
