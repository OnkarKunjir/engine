#define GLFW_INCLUDE_NONE
#define __FILENAME__ "main.cpp"

#include "render/render.hpp"
#include "utils/log.hpp"

#include <GLFW/glfw3.h>
#include <glad/gl.h>
#include <string>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>

/**
 *function to return camera move direction based on the key press.
 */
int get_camear_move(const Window &window) {
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

  // creating window.
  Window window("Engine", 800, 800);
  window.fill(0.07f, 0.13f, 0.17f);
  window.key_callback_warn(false);

  float pyramid_vertices[] = {
      // CORD / COLOR / TEXTURE/
      -0.5f, 0.0f, 0.5f,  0.83f, 0.70f, 0.44f, 0.0f, 0.0f, // 0
      -0.5f, 0.0f, -0.5f, 0.83f, 0.70f, 0.44f, 5.0f, 0.0f, // 1
      0.5f,  0.0f, -0.5f, 0.83f, 0.70f, 0.44f, 0.0f, 0.0f, // 2
      0.5f,  0.0f, 0.5f,  0.83f, 0.70f, 0.44f, 5.0f, 0.0f, // 3
      0.0f,  0.8f, 0.0f,  0.92f, 0.86f, 0.76f, 2.5f, 5.0f, // 4
  };

  unsigned int pyramid_index[] = {0, 1, 2, 0, 2, 3, 0, 1, 4,
                                  1, 2, 4, 2, 3, 4, 3, 0, 4};

  Buffer pyramid_buffer(GL_ARRAY_BUFFER, GL_STATIC_DRAW,
                        sizeof(pyramid_vertices), pyramid_vertices);
  BufferLayout pyramid_layout;
  pyramid_layout.push_float(3);
  pyramid_layout.push_float(3);
  pyramid_layout.push_float(2);
  Buffer pyramid_index_buffer(GL_ELEMENT_ARRAY_BUFFER, GL_STATIC_DRAW,
                              sizeof(pyramid_index), pyramid_index);
  VertexArray pyramid(pyramid_buffer, pyramid_index_buffer, pyramid_layout);
  pyramid.unbind();

  Shader shader("assets/shader/vertex.glsl", "assets/shader/fragment.glsl",
                "out_color");

  Texture brick("assets/textures/brick.png", GL_TEXTURE0, GL_RGBA);
  brick.parameter(GL_TEXTURE_WRAP_S, GL_REPEAT);
  brick.parameter(GL_TEXTURE_WRAP_T, GL_REPEAT);

  Camera camera(glm::vec3(0, 0, -2.0f), glm::vec3(0, 0, 1));
  glm::mat4 model = glm::mat4(1.0f);

  window.set_cursor((float)window.width() / 2, (float)window.height() / 2);
  while (window.is_active()) {

    double xpos, ypos;
    window.get_cursor(xpos, ypos);
    window.set_cursor((float)window.width() / 2, (float)window.height() / 2);

    // update the camera.
    camera.move(get_camear_move(window), window.delta());
    camera.rotate(xpos, ypos);

    shader.set_uniform_matrix4fv("model", glm::value_ptr(model));
    camera.apply(shader, "view", "proj");

    pyramid.bind();
    glad_glDrawElements(GL_TRIANGLES, sizeof(pyramid_index) / sizeof(int),
                        GL_UNSIGNED_INT, nullptr);

    window.update();
    window.poll_events();
  }

  return 0;
}
