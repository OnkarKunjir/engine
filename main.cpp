#define __FILENAME__ "main.cpp"

#include "render/render.hpp"

#include <glad/gl.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

int move(const Window &window) {
  int direction = 0;
  if (window.press(GLFW_KEY_W))
    direction |= CAMERA_MOVE_FORWARD;

  if (window.press(GLFW_KEY_S))
    direction |= CAMERA_MOVE_BACKWARD;

  if (window.press(GLFW_KEY_A))
    direction |= CAMERA_MOVE_LEFT;

  if (window.press(GLFW_KEY_D))
    direction |= CAMERA_MOVE_RIGHT;

  return direction;
}

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

  color.bind();

  Camera camera(glm::vec3(0, 0, -2), glm::vec3(0, 0, 1));
  Texture tex("assets/textures/fat_cat.jpg", GL_TEXTURE0, GL_RGB);
  tex.bind();

  window.set_cursor(window.width() / 2, window.height() / 2);
  while (window.is_active()) {
    auto [x, y] = window.get_cursor();
    camera.rotate(x, y);
    camera.move(move(window), 2 * window.delta());
    window.set_cursor(window.width() / 2, window.height() / 2);
    camera.apply(color, "view", "proj");
    glad_glDrawElements(GL_TRIANGLES, sizeof(index_data) / sizeof(int),
                        GL_UNSIGNED_INT, nullptr);
    window.update();
    window.poll_events();
  }
  return 0;
}
