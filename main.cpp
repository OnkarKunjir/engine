#define GLFW_INCLUDE_NONE
#define __FILENAME__ "main.cpp"

#include "engine2d.hpp"
#include "render/render.hpp"
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

int main() {
  Engine2d engine("engine", 800, 800);
  Rect r(0, 0, 100, 100);
  while (engine.is_active()) {

    engine.draw(r);

    engine.poll_events();
    engine.update();
  }
  return 0;
}
