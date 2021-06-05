#include "render/window.hpp"
#include "utils/log.hpp"

int main() {
  Window window("title", 300, 300);
  while (window.is_active()) {
    window.update();
    window.poll_events();
  }
  return 0;
}
