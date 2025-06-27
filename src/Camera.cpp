#include "Camera.h"
#include <GL/gl.h>
#include <GL/glu.h>

Camera::Camera() {
  Position = glm::vec3(0, 0, 0);
  WorldUp = glm::vec3(0, 1, 0);
  Yaw = -128.0f;
  Pitch = -42.0f;
  MovementSpeed = 500;
  MouseSensitivity = 1;
  Zoom = 1;
  updateCameraVectors();
}

void Camera::move(Camera_Movement direction, float deltaTime) {

  float velocity = MovementSpeed * deltaTime;
  if (direction == FORWARD)
    Position += Front * velocity;
  if (direction == BACKWARD)
    Position -= Front * velocity;
  if (direction == LEFT)
    Position -= Right * velocity;
  if (direction == RIGHT)
    Position += Right * velocity;
  if (direction == UP)
    Position += Up * velocity;
  if (direction == DOWN)
    Position -= Up * velocity;
}

void Camera::moveMouse(float xoffset, float yoffset, bool constrainPitch) {
  xoffset *= MouseSensitivity;
  yoffset *= MouseSensitivity;

  Yaw += xoffset;
  Pitch += yoffset;

  // make sure that when pitch is out of bounds, screen doesn't get flipped
  if (constrainPitch) {
    if (Pitch > 89.0f)
      Pitch = 89.0f;
    if (Pitch < -89.0f)
      Pitch = -89.0f;
  }

  // update Front, Right and Up Vectors using the updated Euler angles
  updateCameraVectors();
}

void Camera::update(float delta) {
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glm::vec3 CenterPoint = Position + Front;
  gluLookAt(Position.x, Position.y, Position.z,          // eye
            CenterPoint.x, CenterPoint.y, CenterPoint.z, // center
            Up.x, Up.y, Up.z);                           // up
}

glm::mat4 Camera::GetViewMatrix() {
  return glm::lookAt(Position, Position + Front, Up);
}

glm::mat4 Camera::getPerspective() {
  return glm::perspective(-fovy, aspect, zNear, zFar);
}