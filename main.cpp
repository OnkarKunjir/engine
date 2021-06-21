#define GLFW_INCLUDE_NONE
#define __FILENAME__ "main.cpp"

#include "render/render.hpp"
#include "shapes/cuboid.hpp"
#include "shapes/rect.hpp"
#include "utils/log.hpp"

#include <GLFW/glfw3.h>
#include <glad/gl.h>
#include <string>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>

int main() {
  Window window("Engine", 400, 400, true);

  Cuboid cube(-0.5, 0.5, -0.5, 1, 1, 1);

  Camera camera(glm::vec3(0, 0, 3), glm::vec3(0, 0, -1));
  Shader color_shader("assets/shader/color/vertex.glsl",
                      "assets/shader/color/fragment.glsl", "out_color");
  color_shader.bind();
  glm::mat4 model = glm::mat4(1);

  float rot = 0.5;
  while (window.is_active()) {
    model = glm::rotate(model, glm::radians(rot), glm::vec3(0, 1, 0));
    color_shader.set_uniform_matrix4fv("model", glm::value_ptr(model));
    camera.apply(color_shader, "view", "proj");
    cube.draw();

    window.update();
    window.poll_events();
  }

  return 0;
}
