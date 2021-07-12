#define __FILENAME__ "BufferLayout"

#include "render/bufferlayout.hpp"
#include "utils/log.hpp"

#include <glad/gl.h>
#include <vector>

BufferLayout::BufferLayout() : _stride(0) {}
BufferLayout::~BufferLayout() {}

void BufferLayout::push_float(int count, bool normalized) {
  if (count < 0 || count > 4)
    Log::error(__FILENAME__, "Invalid number of count");

  // adds float attribute to the layout.
  _attributes.push_back({static_cast<int>(_attributes.size()), count, GL_FLOAT,
                         normalized, _stride});
  _stride += sizeof(float) * count;
}

void BufferLayout::bind() const {
  // defines and activates all the attributes.
  for (auto &a : _attributes) {
    glad_glEnableVertexAttribArray(a.index);
    glad_glVertexAttribPointer(a.index, a.size, a.type, a.normalized, _stride,
                               (void *)(a.pointer));
  }
}
