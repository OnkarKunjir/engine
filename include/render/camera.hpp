#pragma once

#define CAMERA_MOVE_FORWARD 0x1
#define CAMERA_MOVE_BACKWARD 0x2
#define CAMERA_MOVE_LEFT 0x4
#define CAMERA_MOVE_RIGHT 0x8

#include "glm/fwd.hpp"
#include <glm/glm.hpp>
#include <string>

#include "render/shader.hpp"

class Camera {
private:
  float _speed;
  float _sensitivity;

  glm::vec3 _position;
  glm::vec3 _orientation;
  glm::vec3 _up;   // up direction.
  glm::mat4 _proj; // projection matrix.

public:
  /**
   *Constructor
   *@param positon Initial position of camera.
   *@param orientation Direction to look at form positon.
   *@param speed Speed with camera should move.
   */
  Camera(const glm::vec3 &position, const glm::vec3 &orientation,
         float fov = 45.0f, float aspect_ratio = 1.0f, float near = 0.1f,
         float far = 100.0f, float speed = 3.0f);

  ~Camera();
  /**
   *Function applies the view and perspective projection.
   *@param shader Shader to witch uniforms of view and projection matrix to be
   *sent.
   *@param view_uniform Name of uniform for view matrix.
   *@param proj_uniform Name of uniform for projection matrix.
   */
  void apply(const Shader &shader, const std::string &view_uniform,
             const std::string &proj_uniform) const;

  /**
   *Move the camera in specified direction.
   */
  void move(int direction, float delta = 1.0f);

  /**
   *Rotates the camera to given x and y cooridinates.
   */
  void rotate(float x, float y);
};
