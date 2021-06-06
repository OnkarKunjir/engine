#include "render/window.hpp"
#include "GLFW/glfw3.h"
#include "utils/log.hpp"
#include <cstdlib>
#include <glad/gl.h>
#include <iostream>
#include <string>

// TODO: add support to change window hints.

#define __FILENAME__ "window.cpp"

// static functions
void Window::glfw_error_callback(int error, const char *description) {
  Log::error(__FILENAME__ ":GLFW", description);
}

// constructors and destructors
Window::Window(std::string title, int width, int height) {
  // initalizes glfw and creates window
  glfwSetErrorCallback(glfw_error_callback);
  if (!glfwInit()) {
    Log::error(__FILENAME__, "Failed to initalize glfw");
    exit(EXIT_FAILURE);
  }

  // creating window according to parameters provided
  glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
  _window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
  if (_window == nullptr) {
    Log::error(__FILENAME__, "Failed to create window");
    glfwTerminate();
    exit(EXIT_FAILURE);
  }
  glfwMakeContextCurrent(_window);

  int version = gladLoadGL(glfwGetProcAddress);
  if (version == 0) {
    Log::error(__FILENAME__, "Failed to load glad");
    glfwDestroyWindow(_window);
    glfwTerminate();
    exit(EXIT_FAILURE);
  } else {
    Log::message(__FILENAME__, "OpenGL Version - " +
                                   std::to_string(GLAD_VERSION_MAJOR(version)) +
                                   "." +
                                   std::to_string(GLAD_VERSION_MINOR(version)));
  }

  glfwSwapInterval(1);
}

Window::~Window() {
  glfwDestroyWindow(_window);
  glfwTerminate();
}

// public functions
bool Window::is_active() const { return !glfwWindowShouldClose(_window); }
void Window::poll_events() const { glfwPollEvents(); }
void Window::update() const { glfwSwapBuffers(_window); }

// private and protected functions
