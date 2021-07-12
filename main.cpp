#define __FILENAME__ "main.cpp"

#include "render/render.hpp"

#include <glad/gl.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

int main() {
  Window window("Test", 800, 800, 0, true);

  float rect_vertex[] = {
      -0.5f, 0.5f,  0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, // 0
      0.5f,  0.5f,  0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, // 1
      0.5f,  -0.5f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, // 2
      -0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f, // 3
  };

  Buffer buffer(GL_ARRAY_BUFFER, GL_STATIC_DRAW, sizeof(rect_vertex),
                rect_vertex);

  BufferLayout layout;
  layout.push_float(3);
  layout.push_float(3);
  layout.push_float(2);

  unsigned int index_data[] = {0, 1, 2, 2, 3, 0};
  Buffer index(GL_ELEMENT_ARRAY_BUFFER, GL_STATIC_DRAW, sizeof(index_data),
               index_data);

  VertexArray rect(buffer, index, layout);
  rect.bind();

  Shader color("assets/shader/texture/vertex.glsl",
               "assets/shader/texture/fragment.glsl", "out_color");
  glm::mat4 identity = glm::mat4(1.0f);

  color.set_uniform_matrix4fv("model", glm::value_ptr(identity));
  color.set_uniform_matrix4fv("view", glm::value_ptr(identity));
  color.set_uniform_matrix4fv("proj", glm::value_ptr(identity));

  color.bind();

  Texture tex("assets/textures/fat_cat.jpg", GL_TEXTURE0, GL_RGB);
  tex.bind();

  while (window.is_active()) {
    glad_glDrawElements(GL_TRIANGLES, sizeof(index_data) / sizeof(int),
                        GL_UNSIGNED_INT, nullptr);
    window.update();
    window.poll_events();
  }
  return 0;
}
