#pragma once

#include "render/buffer.hpp"
#include "render/bufferlayout.hpp"

class VertexArray {
private:
  unsigned int _id;

public:
  /**
   *Creates vertex array object
   *@param buffer Vertex buffer to be bound to vertexarray
   *@param index Index buffer for buffer.
   *@param layout layout of parameters in vertices of buffer
   */
  VertexArray(const Buffer &buffer, const Buffer &index,
              const BufferLayout &layout);
  ~VertexArray();

  /**Binds the vertex array object*/
  void bind() const;

  void unbind() const;
};
