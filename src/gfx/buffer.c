#include "buffer.h"

Buffer bufferCreate(GLenum target, GLenum usage) {
  Buffer buffer;
  buffer.target = target;
  buffer.usage = usage;
  glad_glGenBuffers(1, &buffer.id);
  glad_glBindBuffer(target, buffer.id);
  return buffer;
}

void bufferData(Buffer *buffer, GLsizeiptr size, const GLvoid *data) {
  glad_glBindBuffer(buffer->target, buffer->id);
  glad_glBufferData(buffer->target, size, data, buffer->usage);
}

void bufferDestroy(Buffer *buffer) { glad_glDeleteBuffers(1, &buffer->id); }
