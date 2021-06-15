#include "glm/fwd.hpp"
#define GLFW_INCLUDE_NONE
#define __FILENAME__ "main.cpp"
#define GLM_ENABLE_EXPERIMENTAL

#include "render/buffer.hpp"
#include "render/bufferlayout.hpp"
#include "render/camera.hpp"
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
  window.fill(0.07f, 0.13f, 0.17f);

  float vertices[] = {-0.5f, 0.0f, 0.5f,  0.83f, 0.70f, 0.44f, 0.0f, 0.0f,
                      -0.5f, 0.0f, -0.5f, 0.83f, 0.70f, 0.44f, 5.0f, 0.0f,
                      0.5f,  0.0f, -0.5f, 0.83f, 0.70f, 0.44f, 0.0f, 0.0f,
                      0.5f,  0.0f, 0.5f,  0.83f, 0.70f, 0.44f, 5.0f, 0.0f,
                      0.0f,  0.8f, 0.0f,  0.92f, 0.86f, 0.76f, 2.5f, 5.0f};

  unsigned int elements[] = {0, 1, 2, 0, 2, 3, 0, 1, 4,
                             1, 2, 4, 2, 3, 4, 3, 0, 4};

  Buffer buffer(GL_ARRAY_BUFFER, GL_STATIC_DRAW, sizeof(vertices), vertices);
  BufferLayout layout;
  layout.push_float(3);
  layout.push_float(3);
  layout.push_float(2);
  VertexArray square(buffer, layout);

  Buffer element_buffer(GL_ELEMENT_ARRAY_BUFFER, GL_STATIC_DRAW,
                        sizeof(elements), elements);

  Shader shader("assets/shader/vertex.glsl", "assets/shader/fragment.glsl",
                "out_color");

  Texture cat("assets/textures/brick.png", GL_TEXTURE0, GL_RGBA);
  cat.parameter(GL_TEXTURE_WRAP_S, GL_REPEAT);
  cat.parameter(GL_TEXTURE_WRAP_T, GL_REPEAT);

  float rotation = 0.0f;

  Camera camera(glm::vec3(0, 0, -2.0f), glm::vec3(0, 0, 1));

  window.set_key_callback(
      [&camera, &window](int key, int scancode, int action, int mods) {
        int direction = 0;
        switch (key) {
        case GLFW_KEY_W:
          direction |= CAMERA_MOVE_FORWARD;
          break;
        case GLFW_KEY_S:
          direction |= CAMERA_MOVE_BACKWARD;
          break;

        case GLFW_KEY_A:
          direction |= CAMERA_MOVE_LEFT;
          break;
        case GLFW_KEY_D:
          direction |= CAMERA_MOVE_RIGHT;
          break;
        }
        camera.move(direction, window.delta());
      });

  window.set_cursor((float)window.width() / 2, (float)window.height() / 2);
  while (window.is_active()) {

    glm::mat4 model = glm::mat4(1.0f);
    rotation += 2.0f;

    double xpos, ypos;
    window.get_cursor(xpos, ypos);
    window.set_cursor((float)window.width() / 2, (float)window.height() / 2);

    camera.rotate(xpos, ypos);

    model =
        glm::rotate(model, glm::radians(rotation), glm::vec3(0.0f, 1.0f, 0.0f));
    shader.set_uniform_matrix4fv("model", glm::value_ptr(model));
    camera.apply(shader, "view", "proj");

    glad_glDrawElements(GL_TRIANGLES, sizeof(elements) / sizeof(int),
                        GL_UNSIGNED_INT, nullptr);

    window.update();
    window.poll_events();
  }

  return 0;
}
