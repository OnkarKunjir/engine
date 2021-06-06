#include "render/buffer.hpp"
#include "render/bufferlayout.hpp"
#include "render/window.hpp"
#include "utils/log.hpp"
#include <glad/gl.h>
#include <iostream>

int main() {
  Window window("title", 300, 300);

  float vertices[] = {
      // X, Y
      0.0f,  0.5f,  // Vertex 1
      0.5f,  -0.5f, // Vertex 2
      -0.5f, -0.5f  // Vertex 3
  };

  Buffer vertex_buffer(GL_ARRAY_BUFFER, GL_STATIC_DRAW, sizeof(vertices),
                       vertices);

  BufferLayout layout;
  layout.push_float(2);
  layout.bind();

  while (window.is_active()) {
    glad_glDrawArrays(GL_TRIANGLES, 0, 3);
    window.update();
    window.poll_events();
  }

  return 0;
}
