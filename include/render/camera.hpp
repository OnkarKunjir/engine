#pragma once

#define CAMERA_MOVE_FORWARD 0x1
#define CAMERA_MOVE_BACKWARD 0x2
#define CAMERA_MOVE_LEFT 0x4
#define CAMERA_MOVE_RIGHT 0x8

#include "render/shader.hpp"

#include <glm/glm.hpp>
#include <string>

class Camera {
private:
  float _sensitivity;

  glm::vec3 _position;
  glm::vec3 _orientation;
  glm::vec3 _up;   // up direction.
  glm::mat4 _proj; // projection matrix.

public:
  /**
   *  Creates perspective projection camera.
   *  @param positon Initial position of camera.
   *  @param orientation Direction to look at from positon.
   *  @param aspect_ratio Specify aspect ratio of screen.
   *  @param sensitivity Specify sensitivity of camera.
   *  @param fov Specify feild of view.
   *  @param near Specify near clip distace.
   *  @param far Specify far clip distace.
   */
  Camera(const glm::vec3 &position, const glm::vec3 &orientation,
         float aspect_ratio = 1.0f, float sensitivity = 100.0f,
         float fov = 45.0f, float near = 0.1f, float far = 100.0f);

  ~Camera();

  /**
   *  Function applies the view and perspective projection.
   *  @param shader Shader to witch uniforms of view and projection matrix to be
   *  sent.
   *  @param view_uniform Name of uniform for view matrix.
   *  @param proj_uniform Name of uniform for projection matrix.
   */
  void apply(const Shader &shader, const std::string &view_uniform,
             const std::string &proj_uniform) const;

  /**
   *  Move the camera in specified direction.
   *  @pram direction Specify the directions to move camera in.
   *  (CAMERA_MOVE_FORWARD, CAMERA_MOVE_BACKWARD, CAMERA_MOVE_LEFT,
   *  CAMERA_MOVE_RIGHT)
   *  @pram delta Specify time required to render last frame.
   */
  void move(int direction, float delta = 1.0f);

  /**
   *  Rotates the camera to given x and y cooridinates.
   */
  void rotate(float x, float y);

  const float *position() const;
};
