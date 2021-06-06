/** wrapper around glfw. handles all the functions related to window creation
 *and input.
 */

#pragma once
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <string>

class Window {
  /**
   *Class to handle gui and input output
   */
private:
  GLFWwindow *_window;

public:
  /**Constructor
   *creates new window and loads initalizes glad
   *@param title title of the window
   *@param width widht of the window
   *@param height height of the window
   */
  Window(std::string title, int width, int height);
  ~Window();

  /**Callback function for glfw
   *@param error error id
   *@param description brif description of the erro
   */
  static void glfw_error_callback(int error, const char *description);

  /**Check if window should close
   *@return true if window was requested to close else false
   */
  bool is_active() const;
  /**Polls input event for current window*/
  void poll_events() const;
  /**Swaps buffer for current window*/
  void update() const;
};
