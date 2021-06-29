#define GLFW_INCLUDE_NONE
#define __FILENAME__ "main.cpp"

#include "engine2d.hpp"
#include "utils/log.hpp"

int main() {
  Engine2d engine("engine", 800, 800);
  while (engine.is_active()) {

    engine.draw({
        {100, 100, 20, 30},
        {200, 300, 40, 30},
    });

    engine.poll_events();
    engine.update();
  }
  return 0;
}
