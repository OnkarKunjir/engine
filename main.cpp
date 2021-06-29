#define GLFW_INCLUDE_NONE
#define __FILENAME__ "main.cpp"

#include "engine2d.hpp"
#include "utils/log.hpp"

#include <chrono>
#include <string>

int main() {
  Engine2d engine("engine", 800, 800);

  engine.draw({
      {100, 100, 20, 30},
      {200, 300, 40, 30},
  });

  while (engine.is_active()) {

    auto start = std::chrono::high_resolution_clock::now();
    engine.draw();
    engine.poll_events();
    engine.update();
    auto end = std::chrono::high_resolution_clock::now();

    auto diff = end - start;
    Log::warn("Time", std::to_string(diff.count() * 1e-9));
  }
  return 0;
}
