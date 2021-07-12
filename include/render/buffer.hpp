#pragma once

class Buffer {
  unsigned int _id;
  unsigned int _buffer_type;
  unsigned int _usage;

public:
  /**
   *  Creates buffer of type buffer_type.
   *  @param buffer_type Specify type of buffer eg. GL_ARRAY_BUFFER
   *  @param usage Specify use of the buffer eg. GL_STATIC_DRAW
   *  @param size Specify size of buffer in bytes.
   *  @param data array of data to store in buffer.
   */
  Buffer(unsigned int buffer_type, unsigned int usage, unsigned int size = 0,
         void *data = nullptr);

  /**Deletes opengl buffer*/
  ~Buffer();

  /**Binds current buffer*/
  void bind() const;

  /**
   *  Copy new data to the buffer.
   *  @param size Specify the size of data in bytes.
   *  @param data Specify the data to be copied into buffer.
   */
  void data(unsigned int size, void *data) const;
};
