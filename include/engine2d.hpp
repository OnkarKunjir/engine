#pragma once

#include "render/render.hpp"
#include "shapes/rect.hpp"

#include <glm/glm.hpp>
#include <string>
#include <vector>

class Engine2d {
protected:
  Window _window;

  // member required to draw.
  Buffer _vertex;       // vertex buffer.
  Buffer _index;        // index buffer.
  BufferLayout _layout; // vertex buffer layout.
  VertexArray _vao;     // engine 2d vertex array buffer.
  Shader _shader;       // default solid shader.

  glm::mat4 _proj; // projection matrix.

  mutable int _index_count = 0;

public:
  /**
   *  @brief Constructor to initalize 2d render engine.
   *  @param title Specify title of screen.
   *  @param widht Specify width of screen.
   *  @param height Specify height of screen.
   */
  Engine2d(const std::string &title, int width, int height);

  /**
   *  @brief Function to check if window is active.
   *  @return true if window is active else false.
   */
  bool is_active() const;
  /**
   *  @brief Function to poll events from IO device.
   */
  void poll_events() const;
  /**
   *  @brief Function to update display.
   */
  void update();

  /**
   *  @brief Function to draw rectangle on screen.
   *  @param rect Rect to be drawn.
   *  @param r Red
   *  @param g Green
   *  @param b Blue
   */
  void draw(const Rect &rect, float r = 1.0f, float g = 1.0f,
            float b = 1.0f) const;

  /**
   *  @brief Function to draw multiple rect on screen.
   *  @pram rect_arr vector containing rect to draw.
   */
  void draw(const std::vector<Rect> &rect_arr) const;

  void draw() const;
};
