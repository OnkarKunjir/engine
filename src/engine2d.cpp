#define __FILENAME__ "Engine2d"

#include "engine2d.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "utils/log.hpp"

#include <glad/gl.h>
#include <vector>

Engine2d::Engine2d(const std::string &title, int width, int height)
    : _window(Window(title, width, height, 0, false)),
      _vertex(GL_ARRAY_BUFFER, GL_DYNAMIC_DRAW),
      _index(GL_ELEMENT_ARRAY_BUFFER, GL_DYNAMIC_DRAW),
      _vao(_vertex, _index, _layout),
      _shader("assets/shader/engine2d/vertex.glsl",
              "assets/shader/engine2d/fragment.glsl", "out_color"),
      _proj(glm::ortho(0.0f, (float)width, (float)height, 0.0f)) {

  // create layout for vertex buffer.
  _vao.bind();
  _layout.push_float(2);
  _layout.push_float(3);
  _layout.bind();
  _vao.unbind();

  _window.fill(); // make backgroud of window balck.
  _window.key_callback_warn(
      false); // turn off warning for key callback not set.
  _shader.set_uniform_matrix4fv("proj", glm::value_ptr(_proj));
}

bool Engine2d::is_active() const { return _window.is_active(); }

void Engine2d::poll_events() const { _window.poll_events(); }

void Engine2d::update() { _window.update(); }

void Engine2d::draw(const Rect &rect, float r, float g, float b) const {
  float x = rect[0];
  float y = rect[1];
  float width = rect[2];
  float height = rect[3];

  float vertex[] = {
      x,         y,          r, g, b, // 0
      x + width, y,          r, g, b, // 1
      x + width, y + height, r, g, b, // 2
      x,         y + height, r, g, b, // 3
  };

  unsigned char index[] = {0, 1, 2, 2, 3, 0};
  _vertex.data(sizeof(vertex), vertex);
  _index.data(sizeof(index), index);

  _vao.bind();
  _shader.bind();
  glad_glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, nullptr);
  _vao.unbind();
}

void Engine2d::draw(const std::vector<Rect> &rect_arr) const {
  std::vector<float> vertex;
  std::vector<unsigned int> index;

  unsigned int i = 0;
  float x, y, width, height;

  for (auto &rect : rect_arr) {
    x = rect[0];
    y = rect[1];
    width = rect[2];
    height = rect[3];

    index.insert(index.end(), {i, i + 1, i + 2, i + 2, i + 3, i});
    i += 4;

    vertex.insert(vertex.end(),
                  {
                      x,         y,          1.0f, 1.0f, 1.0f, // 0
                      x + width, y,          1.0f, 1.0f, 1.0f, // 1
                      x + width, y + height, 1.0f, 1.0f, 1.0f, // 2
                      x,         y + height, 1.0f, 1.0f, 1.0f, // 3
                  });
  }

  _vertex.data(vertex.size() * sizeof(float), &vertex[0]);
  _index.data(vertex.size() * sizeof(int), &index[0]);

  _index_count = index.size();

  _vao.bind();
  _shader.bind();
  glad_glDrawElements(GL_TRIANGLES, index.size(), GL_UNSIGNED_INT, nullptr);
  _vao.unbind();
}

void Engine2d::draw() const {
  _vao.bind();
  _shader.bind();
  glad_glDrawElements(GL_TRIANGLES, _index_count, GL_UNSIGNED_INT, nullptr);
  _vao.unbind();
}
