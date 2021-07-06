#define __FILENAME__ "main.cpp"

#include "engine2d.hpp"
#include "utils/log.hpp"
#include "utils/profile.hpp"

int main() {
  Engine2d engine("engine", 800, 800);

  std::vector<Rect> rect;

  for (int i = 0; i < 800; i += 10) {
    for (int j = 0; j < 800; j += 10) {
      rect.push_back({(float)i, (float)j, 10.0f, 10.0f});
    }
  }

  engine.draw(rect);

  {
    Profile::Timer t(__PRETTY_FUNCTION__);
    for (int i = 0; i < 1000 && engine.is_active(); i++) {
      engine.draw();
      engine.poll_events();
      engine.update();
    }
  }

  return 0;
}
