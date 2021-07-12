#pragma once

#include "render/buffer.hpp"
#include "render/bufferlayout.hpp"

class VertexArray {
private:
  unsigned int _id;

public:
  /**
   *  Creates vertex array object
   *  @param buffer Specify vertex buffer.
   *  @param index Specify index buffer.
   *  @param layout Specify vertex buffer layout.
   */
  VertexArray(const Buffer &buffer, const Buffer &index,
              const BufferLayout &layout);
  ~VertexArray();

  /**Binds the vertex array object*/
  void bind() const;

  void unbind() const;
};
