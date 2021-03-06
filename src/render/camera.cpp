#define __FILENAME__ "Camera"

#include "render/camera.hpp"
#include "render/shader.hpp"
#include "utils/log.hpp"

#include <string>

#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>

Camera::Camera(const glm::vec3 &position, const glm::vec3 &orientation,
               float aspect_ratio, float sensitivity, float fov, float near,
               float far)
    : _position(position), _orientation(orientation),
      _up(glm::vec3(0.0f, 1.0f, 0.0f)), _sensitivity(sensitivity),
      _proj(glm::perspective(glm::radians(fov), aspect_ratio, near, far)) {}

Camera::~Camera() {}

// public function.
void Camera::apply(const Shader &shader, const std::string &view_uniform,
                   const std::string &proj_uniform) const {
  glm::mat4 view = glm::lookAt(_position, _position + _orientation, _up);

  shader.set_uniform_matrix4fv(view_uniform, glm::value_ptr(view));
  shader.set_uniform_matrix4fv(proj_uniform, glm::value_ptr(_proj));
}

void Camera::move(int direction, float speed) {
  if (direction & CAMERA_MOVE_FORWARD)
    _position += speed * _orientation;

  if (direction & CAMERA_MOVE_BACKWARD)
    _position -= speed * _orientation;

  if (direction & CAMERA_MOVE_LEFT)
    _position -= speed * glm::normalize(glm::cross(_orientation, _up));

  if (direction & CAMERA_MOVE_RIGHT)
    _position += speed * glm::normalize(glm::cross(_orientation, _up));
}

void Camera::rotate(float x, float y) {

  float rotx = _sensitivity * y; // roatation on x axis.
  float roty = _sensitivity * x; // rotation on y axis.

  // changing pitch. (roation along x axis)
  glm::vec3 neworientation =
      glm::rotate(_orientation, glm::radians(-rotx),
                  glm::normalize(glm::cross(_orientation, _up)));

  if (glm::abs(glm::angle(neworientation, _up) - glm::radians(90.0f)) <=
      glm::radians(85.0f)) {
    // limit camera from moving more than 90deg in vertical direction to
    // prevent flipping.
    _orientation = neworientation;
  }

  // chaning yaw. (roatation along y axis)
  _orientation = glm::rotate(_orientation, glm::radians(-roty), _up);
}

const float *Camera::position() const { return glm::value_ptr(_position); }
