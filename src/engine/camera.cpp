//
// Created by richard may clarkson on 05/01/2023.
//
#include "engine/camera.h"

namespace Ember {
  void Camera::scroll(float yoffset) {
    zoom -= (float) yoffset;
    if (zoom < 1.0f)
      zoom = 1.0f;
    if (zoom > 45.0f)
      zoom = 45.0f;
  }

  void Camera::update() {
    // calculate the new newFront vector
    glm::vec3 newFront;
    newFront.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    newFront.y = sin(glm::radians(pitch));
    newFront.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    front = newFront;
    up = normalize(cross(right, newFront));
    right = normalize(cross(newFront,
                            worldUp));  // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
  }

  void Camera::move(float xoffset, float yoffset, bool constrainPitch) {
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    yaw += xoffset;
    pitch += yoffset;

    // make sure that when pitch is out of bounds, screen doesn't get flipped
    if (constrainPitch) {
      if (pitch > 89.0f)
        pitch = 89.0f;
      if (pitch < -89.0f)
        pitch = -89.0f;
    }

    // update front, right and up Vectors using the updated Euler angles
    update();
  }

  void Camera::key(CameraMove direction, float deltaTime) {
    float velocity = speed * deltaTime;
    if (direction == CameraMove::FORWARD)
      velo += normalize(front * glm::vec3(1, 0, 1)) * velocity;
    if (direction == CameraMove::BACKWARD)
      velo -= normalize(front * glm::vec3(1, 0, 1)) * velocity;
    if (direction == CameraMove::LEFT)
      velo -= right * velocity;
    if (direction == CameraMove::RIGHT)
      velo += right * velocity;
    if (direction == CameraMove::UP)
      velo += up * velocity;
    if (direction == CameraMove::DOWN)
      velo -= up * velocity;
    pos += velo;
  }

  Camera::Camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch) : front(glm::vec3(0.0f, 0.0f, -1.0f)), speed(SPEED),
                                                                             sensitivity(SENSITIVITY), zoom(ZOOM), pos(position),
                                                                             worldUp(up),
                                                                             yaw(yaw), pitch(pitch) {
    update();
  }

  Camera::Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch) : front(
    glm::vec3(0.0f, 0.0f, -1.0f)), speed(SPEED), sensitivity(SENSITIVITY), zoom(ZOOM), yaw(yaw), pitch(pitch) {
    pos = glm::vec3(posX, posY, posZ);
    worldUp = glm::vec3(upX, upY, upZ);
    update();
  }
}