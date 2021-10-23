#ifndef BUFFER_H
#define BUFFER_H

#include <glad/gl.h>

typedef struct Buffer {
  GLuint id;
  GLenum target;
  GLenum usage;
} Buffer;

/**
 * Create new buffer.
 * @return Buffer struct.
 */
Buffer bufferCreate(GLenum target, GLenum usage);

void bufferData(Buffer *buffer, GLsizeiptr size, const GLvoid *data);

/**
 * Delete the buffer.
 */
void bufferDestroy(Buffer *buffer);

#endif /* BUFFER_H */
