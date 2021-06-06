#include "render/buffer.hpp"
#include "render/bufferlayout.hpp"
#include "render/shader.hpp"
#include "render/vertexarray.hpp"
#include "render/window.hpp"
#include <glad/gl.h>
#include <iostream>

int main() {
  Window window("title", 300, 300);

  float vertices[] = {
      -0.5f, 0.5f,  1.0f, 0.0f, 0.0f, // Top-left
      0.5f,  0.5f,  0.0f, 1.0f, 0.0f, // Top-right
      0.5f,  -0.5f, 0.0f, 0.0f, 1.0f, // Bottom-right
      0.5f,  -0.5f, 0.0f, 0.0f, 1.0f, // Bottom-right
      -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, // Bottom-left
      -0.5f, 0.5f,  1.0f, 0.0f, 0.0f  // Top-left
  };

  Buffer buffer(GL_ARRAY_BUFFER, GL_STATIC_DRAW, sizeof(vertices), vertices);
  BufferLayout layout;
  layout.push_float(2);
  layout.push_float(3);
  VertexArray square(buffer, layout);

  Shader s("assets/shader/vertex.glsl", "assets/shader/fragment.glsl",
           "out_color");

  while (window.is_active()) {
    glad_glDrawArrays(GL_TRIANGLES, 0, 6);
    window.update();
    window.poll_events();
  }

  return 0;
}
