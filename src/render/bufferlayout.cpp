#include "render/bufferlayout.hpp"
#include "utils/log.hpp"
#include <glad/gl.h>
#include <iostream>
#include <string>
#include <vector>

void print_attribute(Attribute &a) {
  std::cout << "Index: " << a.index << std::endl;
  std::cout << "size: " << a.size << std::endl;
  std::cout << "type: " << a.type << std::endl;
  std::cout << "normalized: " << a.normalized << std::endl;
  std::cout << "pointer: " << a.pointer << std::endl;
}

BufferLayout::BufferLayout() : _stride(0) {}
BufferLayout::~BufferLayout() {}

void BufferLayout::push_float(int count, bool normalized) {
  // adds float attribute to the layout.
  Attribute a = {static_cast<int>(_attributes.size()), count, GL_FLOAT,
                 normalized, _stride};

  _attributes.push_back(a);
  _stride += sizeof(float) * count;
}

void BufferLayout::bind() {
  // defines and activates all the attributes.
  for (int i = 0; i < _attributes.size(); i++) {
    Attribute &a = _attributes[i];
    glad_glEnableVertexAttribArray(i);
    glad_glVertexAttribPointer(a.index, a.size, a.type, a.normalized, _stride,
                               (void *)(a.pointer));
  }
}
