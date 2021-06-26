#pragma once

#include <glm/glm.hpp>
#include <string>

#include "render/render.hpp"
#include "shapes/rect.hpp"

class Engine2d {
private:
  Window _window;

  // member required to draw.
  Buffer _vertex;
  Buffer _index;
  BufferLayout _layout;
  VertexArray _vao;
  Shader _shader;

  glm::mat4 _proj; // projection matrix.

public:
  /**
   *  @brief Constructor to initalize 2d render engine.
   *  @param title Specify title of screen.
   *  @param widht Specify width of screen.
   *  @param height Specify height of screen.
   */
  Engine2d(const std::string &title, int width, int height);

  // function to access window properties
  bool is_active() const;
  void poll_events() const;
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
};
