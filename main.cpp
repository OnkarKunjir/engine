#include "render/buffer.hpp"
#include "render/bufferlayout.hpp"
#include "render/shader.hpp"
#include "render/texture.hpp"
#include "render/vertexarray.hpp"
#include "render/window.hpp"
#include <glad/gl.h>

int main() {
  Window window("title", 1000, 1000);

  float vertices[] = {
      // x, y, r, g, b, tex_x, tex_y
      -0.5f, 0.5f,  1.0f, 0.0f, 0.0f, 0.0f, 0.0f, // Top-left
      0.5f,  0.5f,  0.0f, 1.0f, 0.0f, 1.0f, 0.0f, // Top-right
      0.5f,  -0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, // Bottom-right
      -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f, // Bottom-left
  };

  unsigned int elements[] = {0, 1, 2, 2, 3, 0};

  Buffer buffer(GL_ARRAY_BUFFER, GL_STATIC_DRAW, sizeof(vertices), vertices);
  BufferLayout layout;
  layout.push_float(2);
  layout.push_float(3);
  layout.push_float(2);
  VertexArray square(buffer, layout);

  Buffer element_buffer(GL_ELEMENT_ARRAY_BUFFER, GL_STATIC_DRAW,
                        sizeof(elements), elements);

  Shader s("assets/shader/vertex.glsl", "assets/shader/fragment.glsl",
           "out_color");

  Texture cat("assets/textures/fat_cat.jpg", GL_TEXTURE0, GL_RGB);

  while (window.is_active()) {
    glad_glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
    window.update();
    window.poll_events();
  }

  return 0;
}
