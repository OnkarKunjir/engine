#define GLFW_INCLUDE_NONE
#define __FILENAME__ "main.cpp"

#include "render/render.hpp"
#include "shapes/cuboid.hpp"
#include "shapes/rect.hpp"
#include "utils/log.hpp"

#include <GLFW/glfw3.h>
#include <glad/gl.h>
#include <string>
#include <utility>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>

int walk(const Window &window) {
  int direction = 0;
  if (window.get_key(GLFW_KEY_W))
    direction |= CAMERA_MOVE_FORWARD;
  if (window.get_key(GLFW_KEY_S))
    direction |= CAMERA_MOVE_BACKWARD;
  if (window.get_key(GLFW_KEY_A))
    direction |= CAMERA_MOVE_LEFT;
  if (window.get_key(GLFW_KEY_D))
    direction |= CAMERA_MOVE_RIGHT;
  return direction;
}

int main() {
  Window window("Engine", 800, 800, false);
  window.set_cursor(window.width() / 2, window.height() / 2);
  window.key_callback_warn(false);
  window.fill(0.1f, 0.1f, 0.1f, 1.0f);

  float vertices[] = {
      //    COORDINATE   /      COLOR      /  TEXTURE /       Normal          /
      -0.5f, 0.5f,  0.0f,  1.0f,  1.0f,  1.0f,
      0.0f,  0.0f,  0.0f,  0.0f,  1.0f, // 0
      0.5f,  0.5f,  0.0f,  1.0f,  1.0f,  1.0f,
      1.0f,  0.0f,  0.0f,  0.0f,  1.0f, // 1
      0.5f,  -0.5f, 0.0f,  1.0f,  1.0f,  1.0f,
      1.0f,  1.0f,  0.0f,  0.0f,  1.0f, // 2
      -0.5f, -0.5f, 0.0f,  1.0f,  1.0f,  1.0f,
      0.0f,  1.0f,  0.0f,  0.0f,  1.0f, // 3

      -0.5f, 0.5f,  -1.0f, 1.0f,  1.0f,  1.0f,
      0.0f,  0.0f,  0.0f,  0.0f,  -1.0f, // 4
      0.5f,  0.5f,  -1.0f, 1.0f,  1.0f,  1.0f,
      1.0f,  0.0f,  0.0f,  0.0f,  -1.0f, // 5
      0.5f,  -0.5f, -1.0f, 1.0f,  1.0f,  1.0f,
      1.0f,  1.0f,  0.0f,  0.0f,  -1.0f, // 6
      -0.5f, -0.5f, -1.0f, 1.0f,  1.0f,  1.0f,
      0.0f,  1.0f,  0.0f,  0.0f,  -1.0f, // 7

      -0.5f, 0.5f,  0.0f,  1.0f,  1.0f,  1.0f,
      0.0f,  0.0f,  -1.0f, 0.0f,  0.0f, // 8
      -0.5f, 0.5f,  -1.0f, 1.0f,  1.0f,  1.0f,
      1.0f,  0.0f,  -1.0f, 0.0f,  0.0f, // 9
      -0.5f, -0.5f, -1.0f, 1.0f,  1.0f,  1.0f,
      1.0f,  1.0f,  -1.0f, 0.0f,  0.0f, // 10
      -0.5f, -0.5f, 0.0f,  1.0f,  1.0f,  1.0f,
      0.0f,  1.0f,  -1.0f, 0.0f,  0.0f, // 11

      0.5f,  0.5f,  0.0f,  1.0f,  1.0f,  1.0f,
      0.0f,  0.0f,  1.0f,  0.0f,  0.0f, // 12
      0.5f,  0.5f,  -1.0f, 1.0f,  1.0f,  1.0f,
      1.0f,  0.0f,  1.0f,  0.0f,  0.0f, // 13
      0.5f,  -0.5f, -1.0f, 1.0f,  1.0f,  1.0f,
      1.0f,  1.0f,  1.0f,  0.0f,  0.0f, // 14
      0.5f,  -0.5f, 0.0f,  1.0f,  1.0f,  1.0f,
      0.0f,  1.0f,  1.0f,  0.0f,  0.0f, // 15

      -0.5f, 0.5f,  -1.0f, 1.0f,  1.0f,  1.0f,
      0.0f,  0.0f,  0.0f,  1.0f,  0.0f, // 16
      0.5f,  0.5f,  -1.0f, 1.0f,  1.0f,  1.0f,
      1.0f,  0.0f,  0.0f,  1.0f,  0.0f, // 17
      0.5f,  0.5f,  0.0f,  1.0f,  1.0f,  1.0f,
      1.0f,  1.0f,  0.0f,  1.0f,  0.0f, // 18
      -0.5f, 0.5f,  0.0f,  1.0f,  1.0f,  1.0f,
      0.0f,  1.0f,  0.0f,  1.0f,  0.0f, // 19

      -0.5f, -0.5f, -1.0f, 1.0f,  1.0f,  1.0f,
      0.0f,  0.0f,  0.0f,  -1.0f, 0.0f, // 20
      0.5f,  -0.5f, -1.0f, 1.0f,  1.0f,  1.0f,
      1.0f,  0.0f,  0.0f,  -1.0f, 0.0f, // 21
      0.5f,  -0.5f, 0.0f,  1.0f,  1.0f,  1.0f,
      1.0f,  1.0f,  0.0f,  -1.0f, 0.0f, // 22
      -0.5f, -0.5f, 0.0f,  1.0f,  1.0f,  1.0f,
      0.0f,  1.0f,  0.0f,  -1.0f, 0.0f, // 23
  };

  unsigned int index[] = {
      0,  1,  2,  2,  3,  0,  // front
      4,  5,  6,  6,  7,  4,  // back
      8,  9,  10, 10, 11, 8,  // left
      12, 13, 14, 14, 15, 12, // right
      16, 17, 18, 18, 19, 16, // top
      20, 21, 22, 22, 23, 20, // bottom
  };
  Buffer vertex_buffer(GL_ARRAY_BUFFER, GL_STATIC_DRAW, sizeof(vertices),
                       vertices);
  Buffer index_buffer(GL_ELEMENT_ARRAY_BUFFER, GL_STATIC_DRAW, sizeof(index),
                      index);
  BufferLayout layout;
  layout.push_float(3);
  layout.push_float(3);
  layout.push_float(2);
  layout.push_float(3);
  VertexArray cube(vertex_buffer, index_buffer, layout);

  Cuboid light(0, 0, 0, 1, 1, 1);

  Camera camera(glm::vec3(0, 0, 3), glm::vec3(0, 0, -1));
  camera.speed(2);

  Shader texture_shader("assets/shader/texture/vertex.glsl",
                        "assets/shader/texture/fragment.glsl", "out_color");

  Shader color_shader("assets/shader/color/vertex.glsl",
                      "assets/shader/color/fragment.glsl", "out_color");

  texture_shader.bind();
  glm::mat4 model = glm::mat4(1);
  model = glm::scale(model, glm::vec3(2, 2, 2));

  glm::vec3 light_color = glm::vec3(1.0f, 1.0f, 1.0f);
  glm::vec3 light_pos = glm::vec3(0.0f, 4.0f, 3.0f);
  glm::mat4 light_model = glm::translate(glm::mat4(1), light_pos);
  texture_shader.set_uniform_float3fv("light_color",
                                      glm::value_ptr(light_color));

  Texture brick("assets/textures/brick.png", GL_TEXTURE0, GL_RGBA);
  brick.bind();

  while (window.is_active()) {

    auto [x, y] = window.get_cursor();
    window.set_cursor(window.width() / 2, window.height() / 2);

    camera.rotate(x, y);
    camera.move(walk(window), window.delta());

    texture_shader.bind();
    camera.apply(texture_shader, "view", "proj");
    texture_shader.set_uniform_matrix4fv("model", glm::value_ptr(model));
    texture_shader.set_uniform_float3fv("camera_position", camera.position());
    texture_shader.set_uniform_float3fv("light_position",
                                        glm::value_ptr(light_pos));

    cube.bind();
    glad_glDrawElements(GL_TRIANGLES, sizeof(index) / sizeof(int),
                        GL_UNSIGNED_INT, nullptr);

    color_shader.bind();
    camera.apply(color_shader, "view", "proj");
    texture_shader.set_uniform_matrix4fv("model", glm::value_ptr(light_model));
    light.draw();
    window.update();
    window.poll_events();
  }

  return 0;
}
