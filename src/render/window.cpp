#define GLFW_INCLUDE_NONE
#define __FILENAME__ "window.cpp"

#include "render/window.hpp"
#include "utils/log.hpp"

#include <GLFW/glfw3.h>
#include <functional>
#include <glad/gl.h>
#include <string>
#include <utility>

// TODO: add support to change window hints.
// TODO: make depth test optional.

// static functions
void Window::glfw_error_callback(int error, const char *description) {
  Log::error(__FILENAME__ ":GLFW", description);
}

void Window::opengl_debug_callback(unsigned int source, unsigned int type,
                                   unsigned int id, unsigned int severity,
                                   int length, const char *message,
                                   const void *userParam) {
  Log::error("OpenGL", message);
}

// constructors and destructors
Window::Window(const std::string &title, int width, int height,
               int swap_interval, bool debug)
    : _width(width), _height(height), _lastframe_time(0), _delta_time(0) {

  // initalizes glfw and creates window.
  glfwSetErrorCallback(glfw_error_callback);

  // initalizing glfw.
  if (!glfwInit()) {
    Log::error(__FILENAME__, "Failed to initalize glfw");
  }

  // creating window according to parameters provided.
  glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
  _window = glfwCreateWindow(_width, _height, title.c_str(), nullptr, nullptr);
  if (_window == nullptr) {
    glfwTerminate();
    Log::error(__FILENAME__, "Failed to create window");
  }

  // make current window context for opengl.
  glfwMakeContextCurrent(_window);

  // load opengl functions.
  int version = gladLoadGL(glfwGetProcAddress);
  if (version == 0) {
    glfwDestroyWindow(_window);
    glfwTerminate();
    Log::error(__FILENAME__, "Failed to load glad");
  } else {
    Log::message(__FILENAME__, "OpenGL Version - " +
                                   std::to_string(GLAD_VERSION_MAJOR(version)) +
                                   "." +
                                   std::to_string(GLAD_VERSION_MINOR(version)));
  }

  // adding key callback function.
  glfwSetWindowUserPointer(_window, this);

  glfwSwapInterval(swap_interval);

  // opengl buffer options.
  glad_glEnable(GL_DEPTH_TEST); // enabeling depth test by default.
  glad_glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // opengl error callback.
  if (debug) {
    glad_glEnable(GL_DEBUG_OUTPUT);
    glad_glDebugMessageCallback(opengl_debug_callback, nullptr);
  }
}

Window::~Window() {
  glfwDestroyWindow(_window);
  glfwTerminate();
}

// public functions
bool Window::is_active() const { return !glfwWindowShouldClose(_window); }
void Window::poll_events() const { glfwPollEvents(); }

void Window::update() {
  glfwSwapBuffers(_window);
  glad_glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  float current_time = glfwGetTime();
  _delta_time = current_time - _lastframe_time;
  _lastframe_time = current_time;
}

std::pair<double, double> Window::get_cursor(bool norm, bool clamp) const {
  double xpos, ypos;
  glfwGetCursorPos(_window, &xpos, &ypos);

  if (clamp) {
    // clamp the values of cursor
    if (xpos < 0)
      xpos = 0;
    else if (xpos > _width)
      xpos = _width;

    if (ypos < 0)
      ypos = 0;
    else if (ypos > _height)
      ypos = _height;
  }

  if (norm) {
    xpos = (xpos - ((float)_width / 2)) / _width;
    ypos = (ypos - ((float)_height / 2)) / _height;
  }
  return std::make_pair(xpos, ypos);
}

void Window::set_cursor(double xpos, double ypos) const {
  glfwSetCursorPos(_window, xpos, ypos);
}

int Window::width() const { return _width; }
int Window::height() const { return _height; }
float Window::delta() const { return _delta_time; }

void Window::fill(float r, float g, float b, float a) const {
  glad_glClearColor(r, g, b, a);
}

int Window::get_key(int key) const { return glfwGetKey(_window, key); }

bool Window::press(int key) const { return get_key(key) == GLFW_PRESS; }
bool Window::release(int key) const { return get_key(key) == GLFW_RELEASE; }

// private and protected functions
