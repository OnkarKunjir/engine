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
  bool _warn;
  std::function<void(int, int, int, int)> _key_callback;

  float _lastframe_time;
  float _delta_time;

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
   *Function to disable or enable warning for key callback not provided.
   *@param warn gives warning if true.
   */
  void key_callback_warn(bool warn = true);
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
  void update();

  /**
   *Function to get cursor positon on current window.
   *@param xpos x co-ordinate.
   *@param ypos y co-orinate.
   *@param norm Normalize coordinates ie. make origin at the center or screen.
   *@param clamp clamp if true, values of xpos and ypos between [0, width] and
   *[0, height] respectivly.
   */
  void get_cursor(double &xpos, double &ypos, bool norm = true,
                  bool clamp = false) const;

  /**
   *Function to set cursor positon on current window.
   *@param xpos x co-ordinate.
   *@param ypos y co-ordinate.
   */
  void set_cursor(double xpos, double ypos) const;

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

  /**
   *Getter function for _delta_time.
   *@return time requred to render last frame.*/
  float delta() const;

  /**
   *Default backgroud color for window.
   *@param r Red.
   *@param g Green.
   *@param b Blue.
   *@param a Alpha.
   */
  void fill(float r = 0.0f, float g = 0.0f, float b = 0.0f,
            float a = 1.0f) const;

  /**
   *Function to get key state.
   *@param key key to check. eg. GLFW_KEY_A
   *@return GLFW_PRESS or GLFW_RELEASE.
   */
  int get_key(int key) const;

  /**
   *@return true if key is pressed.
   */
  bool press(int key) const;
  /**
   *@return true if key is released.
   */
  bool release(int key) const;
};
