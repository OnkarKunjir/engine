/** wrapper around glfw. handles all the functions related to window creation
 *and input.
 */

#pragma once

#define GLFW_INCLUDE_NONE

#include <GLFW/glfw3.h>
#include <functional>
#include <string>
#include <utility>

class Window {

private:
  GLFWwindow *_window;
  int _width, _height;

  float _lastframe_time;
  float _delta_time;

public:
  /**
   *  Creates and initialize new window and opengl context.
   *  @param title title of the window
   *  @param width widht of the window
   *  @param height height of the window
   *  @param swap_interval Specify time to wait before swapping buffers.
   *  @param debug if true logs opengl debug messages.
   */
  Window(const std::string &title, int width, int height, int swap_interval = 1,
         bool debug = false);
  ~Window();

  /**
   *  Callback function for glfw
   *  @param error error id
   *  @param description brif description of the erro
   */
  static void glfw_error_callback(int error, const char *description);

  /**
   *  OpenGL debug callback.
   */
  static void opengl_debug_callback(unsigned int source, unsigned int type,
                                    unsigned int id, unsigned int severity,
                                    int length, const char *message,
                                    const void *userParam);
  /**
   *  Check if window should close
   *  @return true if window was requested to close else false
   */
  bool is_active() const;

  /**
   *  Polls input event for current window
   */
  void poll_events() const;

  /**
   * Updates content of the screen.
   */
  void update();

  /**
   *  Function to get cursor positon on current window.
   *  @param xpos x co-ordinate.
   *  @param ypos y co-orinate.
   *  @param norm Normalize coordinates ie. make origin at the center or screen.
   *  @param clamp clamp if true, values of xpos and ypos between [0, width] and
   *  [0, height] respectivly.
   */
  std::pair<double, double> get_cursor(bool norm = true,
                                       bool clamp = false) const;

  /**
   *  Function to set cursor positon on current window.
   *  @param xpos x co-ordinate.
   *  @param ypos y co-ordinate.
   */
  void set_cursor(double xpos, double ypos) const;

  /**
   *  Getter function for _width.
   *  @return the width of current window.
   */
  int width() const;

  /**
   *  Getter function for _height.
   *  @return height of current window.
   */
  int height() const;

  /**
   *  Getter function for _delta_time.
   *  @return time requred to render last frame.
   */
  float delta() const;

  /**
   *  Default backgroud color for window.
   *  @param r Red.
   *  @param g Green.
   *  @param b Blue.
   *  @param a Alpha.
   */
  void fill(float r = 0.0f, float g = 0.0f, float b = 0.0f,
            float a = 1.0f) const;

  /**
   *  Function to get key state.
   *  @param key key to check. eg. GLFW_KEY_A
   *  @return GLFW_PRESS or GLFW_RELEASE.
   */
  int get_key(int key) const;

  /**
   *  @return true if key is pressed.
   */
  bool press(int key) const;

  /**
   *  @return true if key is released.
   */
  bool release(int key) const;
};
