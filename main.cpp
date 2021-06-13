#include "glm/ext/matrix_transform.hpp"
#include "glm/ext/vector_float3.hpp"
#define GLFW_INCLUDE_NONE
#define __FILENAME__ "main.cpp"
#define GLM_ENABLE_EXPERIMENTAL

#include "render/buffer.hpp"
#include "render/bufferlayout.hpp"
#include "render/shader.hpp"
#include "render/texture.hpp"
#include "render/vertexarray.hpp"
#include "render/window.hpp"
#include "utils/log.hpp"

#include <GLFW/glfw3.h>
#include <glad/gl.h>
#include <string>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>

int main() {

  Window window("title", 800, 800);

  float vertices[] = {
      //   COORDINATES   /      COLORS       /   TexCoord
      -0.5f, 0.5f,  0.5f,  1.0f, 0.0f, 0.0f, 0.0f, 0.0f, // 0 Top-left
      0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 0.0f, 1.0f, 0.0f, // 1 Top-right
      0.5f,  -0.5f, 0.5f,  0.0f, 0.0f, 1.0f, 1.0f, 1.0f, // 2 Bottom-right
      -0.5f, -0.5f, 0.5f,  1.0f, 1.0f, 1.0f, 0.0f, 1.0f, // 3 Bottom-left

      -0.5f, 0.5f,  -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, // 4 Top-left
      0.5f,  0.5f,  -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, // 5 Top-right
      0.5f,  -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, // 6 Bottom-right
      -0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f, // 7 Bottom-left

      -0.5f, 0.5f,  0.5f,  1.0f, 0.0f, 0.0f, 1.0f, 0.0f, // 8 Top-left
      -0.5f, -0.5f, 0.5f,  1.0f, 1.0f, 1.0f, 1.0f, 1.0f, // 9 Bottom-left
      -0.5f, 0.5f,  -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, // 10 Top-left

      0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 0.0f, 0.0f, 0.0f, // 11 Top-right
      0.5f,  -0.5f, 0.5f,  0.0f, 0.0f, 1.0f, 0.0f, 1.0f, // 12 Bottom-right

  };

  unsigned int elements[] = {
      0,  1, 2, 2, 3, 0,  4,  5, 6, 6,  7,  4,
      10, 7, 9, 9, 8, 10, 11, 5, 6, 11, 12, 6,
  };

  Buffer buffer(GL_ARRAY_BUFFER, GL_STATIC_DRAW, sizeof(vertices), vertices);
  BufferLayout layout;
  layout.push_float(3);
  layout.push_float(3);
  layout.push_float(2);
  VertexArray square(buffer, layout);

  Buffer element_buffer(GL_ELEMENT_ARRAY_BUFFER, GL_STATIC_DRAW,
                        sizeof(elements), elements);

  Shader s("assets/shader/vertex.glsl", "assets/shader/fragment.glsl",
           "out_color");

  Texture cat("assets/textures/brick.png", GL_TEXTURE0, GL_RGBA);
  cat.parameter(GL_TEXTURE_WRAP_S, GL_REPEAT);
  cat.parameter(GL_TEXTURE_WRAP_T, GL_REPEAT);

  unsigned int model_loc = s.get_uniform("model");
  unsigned int view_loc = s.get_uniform("view");
  unsigned int proj_loc = s.get_uniform("proj");

  float rotation = 0.0f;
  glad_glEnable(GL_DEPTH_TEST);

  float x = 0;
  float z = -2.0f;

  window.set_key_callback(
      [&x, &z](int key, int scancode, int action, int mods) {
        switch (key) {
        case GLFW_KEY_A:
          x += 0.1f;
          break;
        case GLFW_KEY_D:
          x -= 0.1f;
          break;
        case GLFW_KEY_W:
          z += 0.1f;
          break;
        case GLFW_KEY_S:
          z -= 0.1f;
          break;
        }
      });
  while (window.is_active()) {
    glad_glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 view = glm::mat4(1.0f);
    glm::mat4 proj = glm::mat4(1.0f);

    rotation += 0.5f;

    double xpos, ypos;
    window.get_cursor(xpos, ypos);
    xpos /= window.width();
    ypos /= window.height();

    model =
        glm::rotate(model, glm::radians(rotation), glm::vec3(0.0f, 1.0f, 0.0f));

    view = glm::lookAt(glm::vec3(x, 0, z), glm::vec3(xpos, ypos, 0),
                       glm::vec3(0, 1, 0));

    proj = glm::perspective(glm::radians(45.0f), 1.0f, 0.1f, 100.0f);

    glad_glUniformMatrix4fv(model_loc, 1, false, glm::value_ptr(model));
    glad_glUniformMatrix4fv(view_loc, 1, false, glm::value_ptr(view));
    glad_glUniformMatrix4fv(proj_loc, 1, false, glm::value_ptr(proj));

    glad_glDrawElements(GL_TRIANGLES, sizeof(elements) / sizeof(int),
                        GL_UNSIGNED_INT, nullptr);

    window.update();
    window.poll_events();
  }

  return 0;
}
