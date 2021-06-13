#define GLFW_INCLUDE_NONE
#define __FILENAME__ "window.cpp"

#include "render/window.hpp"
#include "utils/log.hpp"

#include <cstdlib>
#include <functional>
#include <glad/gl.h>
#include <string>

// TODO: add support to change window hints.
// TODO: make depth test optional.

// static functions
void Window::glfw_error_callback(int error, const char *description) {
  Log::error(__FILENAME__ ":GLFW", description);
}

void Window::glfw_key_callback(GLFWwindow *window, int key, int scancode,
                               int action, int mods) {
  Window *ctx = (Window *)glfwGetWindowUserPointer(window);
  try {
    // if callback function is set call the callback function.
    ctx->_key_callback(key, scancode, action, mods);
  } catch (std::bad_function_call) {
    // warn about callback function not provided only once.
    if (!ctx->_key_callback_warn) {
      Log::warn(__FILENAME__, "Key callback function not provided.");
      ctx->_key_callback_warn = true;
    }
  }
}

// constructors and destructors
Window::Window(const std::string &title, int width, int height)
    : _key_callback_warn(false), _width(width), _height(height) {

  // initalizes glfw and creates window.
  glfwSetErrorCallback(glfw_error_callback);

  // initalizing glfw.
  if (!glfwInit()) {
    Log::error(__FILENAME__, "Failed to initalize glfw");
    exit(EXIT_FAILURE);
  }

  // creating window according to parameters provided.
  glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
  _window = glfwCreateWindow(_width, _height, title.c_str(), nullptr, nullptr);
  if (_window == nullptr) {
    Log::error(__FILENAME__, "Failed to create window");
    glfwTerminate();
    exit(EXIT_FAILURE);
  }

  // make current window context for opengl.
  glfwMakeContextCurrent(_window);

  // load opengl functions.
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

  // adding key callback function.
  glfwSetWindowUserPointer(_window, this);
  glfwSetKeyCallback(_window, glfw_key_callback);

  glfwSwapInterval(1);
  // FIXME: for testing purpose only.
  glfwSetInputMode(_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

  // opengl buffer options.
  glad_glEnable(GL_DEPTH_TEST); // enabeling depth test by default.
  glad_glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

Window::~Window() {
  glfwDestroyWindow(_window);
  glfwTerminate();
}

// public functions
bool Window::is_active() const { return !glfwWindowShouldClose(_window); }
void Window::poll_events() const { glfwPollEvents(); }

void Window::set_key_callback(
    std::function<void(int, int, int, int)> callback) {
  _key_callback = callback;
}

void Window::update() const {
  glfwSwapBuffers(_window);
  glad_glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Window::get_cursor(double &xpos, double &ypos, bool clamp) const {
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
}

int Window::width() const { return _width; }
int Window::height() const { return _height; }

// private and protected functions
