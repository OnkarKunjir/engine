#pragma once

class Buffer {
  unsigned int _id;
  unsigned int _buffer_type;
  unsigned int _usage;

public:
  /*
   * buffer_type : type of buffer (GL_ARRAY_BUFFER, ...).
   * usage : usage of the buffer (GL_STATIC_DRAW, ...).
   * size : number of bytes in data
   * data : data to be transferd in buffer.
   */
  Buffer(unsigned int buffer_type, unsigned int usage, unsigned int size,
         void *data);
  ~Buffer();

  void bind();
};
