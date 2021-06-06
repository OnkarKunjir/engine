#include "render/buffer.hpp"
#include "render/bufferlayout.hpp"
#include "render/shader.hpp"
#include "render/window.hpp"
#include "utils/log.hpp"
#include <glad/gl.h>
#include <iostream>

int main() {
  Window window("title", 300, 300);

  float vertices[] = {
      // X, Y
      0.0f,  0.5f,  1.0, 0.0, 0.0, // Vertex 1
      0.5f,  -0.5f, 0.0, 1.0, 0.0, // Vertex 2
      -0.5f, -0.5f, 0.0, 0.0, 1.0, // Vertex 3
  };

  Buffer vertex_buffer(GL_ARRAY_BUFFER, GL_STATIC_DRAW, sizeof(vertices),
                       vertices);

  BufferLayout layout;
  layout.push_float(2);
  layout.push_float(3);
  layout.bind();

  Shader s("assets/shader/vertex.glsl", "assets/shader/fragment.glsl",
           "out_color");

  while (window.is_active()) {
    glad_glDrawArrays(GL_TRIANGLES, 0, 3);
    window.update();
    window.poll_events();
  }

  return 0;
}
