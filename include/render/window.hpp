/** wrapper around glfw. handles all the functions related to window creation
 *and input.
 */

#pragma once

#define GLFW_INCLUDE_NONE

#include <GLFW/glfw3.h>
#include <functional>
#include <string>

class Window {
  /**
   *Class to handle gui and input output
   */
private:
  GLFWwindow *_window;
  int _width, _height;
  bool _key_callback_warn;
  std::function<void(int, int, int, int)> _key_callback;

public:
  /**
   *Constructor
   *creates new window and loads initalizes glad
   *@param title title of the window
   *@param width widht of the window
   *@param height height of the window
   */
  Window(const std::string &title, int width, int height);
  ~Window();

  /**
   *Callback function for glfw
   *@param error error id
   *@param description brif description of the erro
   */
  static void glfw_error_callback(int error, const char *description);

  /**
   *glfw callback for key press
   */
  static void glfw_key_callback(GLFWwindow *window, int key, int scancode,
                                int action, int mods);

  /**
   *Check if window should close
   *@return true if window was requested to close else false
   */
  bool is_active() const;

  /**
   *Polls input event for current window
   */
  void poll_events() const;

  /**
   *Sets keycallback.
   *@param callback(int key, int scancode, int action, int mods) function is
   *called everytime new key event is detected.
   */
  void set_key_callback(std::function<void(int, int, int, int)> callback);

  /**
   *Swaps buffer for current window and clears color buffer and depth buffer
   *bit.
   */
  void update() const;

  /**
   *Function to get cursor positon on current window.
   *@param xpos x co-ordinate.
   *@param ypos y co-orinate.
   *@param clamp clamp if true, values of xpos and ypos between [0, width] and
   *[0, height] respectivly.
   */
  void get_cursor(double &xpos, double &ypos, bool clamp = false) const;

  /**
   *Getter function for _width.
   *@return the width of current window.
   */
  int width() const;

  /**
   *Getter function for _height.
   *@return height of current window.
   */
  int height() const;
};
