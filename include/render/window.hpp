/*
** wrapper around glfw. handles all the functions related to window creation and
*input.
*/

#pragma once
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <string>

class Window {
private:
  GLFWwindow *_window;

public:
  Window(std::string title, int width, int height);
  ~Window();

  static void glfw_error_callback(int error, const char *description);

  bool is_active();
  void poll_events();
  void update();
};
