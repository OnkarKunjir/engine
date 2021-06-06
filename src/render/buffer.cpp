#include "render/buffer.hpp"
#include <glad/gl.h>

Buffer::Buffer(unsigned int buffer_type, unsigned int usage, unsigned int size,
               void *data)
    : _buffer_type(buffer_type), _usage(usage) {
  glad_glGenBuffers(1, &_id);
  bind();
  glad_glBufferData(_buffer_type, size, data, _usage);
}

Buffer::~Buffer() { glad_glDeleteBuffers(1, &_id); }

void Buffer::bind() { glad_glBindBuffer(_buffer_type, _id); }
