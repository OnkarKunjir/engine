#pragma once

class Buffer {
  unsigned int _id;
  unsigned int _buffer_type;
  unsigned int _usage;

public:
  /**Creates new buffer
   *@param buffer_type type of buffer eg. GL_ARRAY_BUFFER
   *@param usage use of the buffer eg. GL_STATIC_DRAW
   *@param size size of buffer in bytes
   *@param data data to be stored in buffer
   */
  Buffer(unsigned int buffer_type, unsigned int usage, unsigned int size,
         void *data);
  ~Buffer();

  /**Binds current buffer*/
  void bind() const;
};
