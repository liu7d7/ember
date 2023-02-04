//
// Created by richard may clarkson on 21/12/2022.
//

#ifndef GLENGINE_CAMERA_H
#define GLENGINE_CAMERA_H

#include "global.h"
#include <vector>

namespace Ember {
  enum CameraMove {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT,
    UP,
    DOWN
  };

  const float YAW = -90.0f;
  const float PITCH = 0.0f;
  const float SPEED = 5.25f;
  const float SENSITIVITY = 0.1f;
  const float ZOOM = 45.0f;

  struct Camera {
    glm::vec3 pos;
    glm::vec3 velo{};
    glm::vec3 front;
    glm::vec3 motion;
    glm::vec3 up;
    glm::vec3 right;
    glm::vec3 worldUp;
    float yaw;
    float pitch;
    float speed;
    float sensitivity;
    float zoom;

    // constructor with vectors
    explicit Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = YAW,
                    float pitch = PITCH);

    // constructor with scalar values
    Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch);

    nodiscard inline glm::vec3 view_pos() const {
      return pos - front * 100.f;
    }

    // returns the view matrix calculated using Euler Angles and the LookAt Matrix
    nodiscard inline glm::mat4 get_look() const {
      glm::mat4 m = glm::lookAt(view_pos(), pos, up);
      m = glm::scale(glm::mat4(1.f), glm::vec3(0.4f)) * m;
      m = glm::translate(glm::mat4(1.f), glm::vec3(0.f, -4.5f, 0.f)) * m;
      return m;
    }

    // processes input received from any keyboard-like input system. Accepts input parameter in the form of camera defined ENUM (to abstract it from windowing systems)
    void key(CameraMove direction, float deltaTime);

    // processes input received from a mouse input system. Expects the offset value in both the x and y direction.
    void move(float xoffset, float yoffset, bool constrainPitch = true);

    // processes input received from a mouse scroll-wheel event. Only requires input on the vertical wheel-axis
    void scroll(float yoffset);

    // calculates the front vector from the Camera's (updated) Euler Angles
    void update();
  };
}
#endif //GLENGINE_CAMERA_H
