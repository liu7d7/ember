//
// Created by richard may clarkson on 05/01/2023.
//

#ifndef LILY_RAND_H
#define LILY_RAND_H

#include "global.h"
#include "random"

namespace Ember::Random {
  static std::random_device rd;
  static std::mt19937 gen(rd());
  static std::uniform_real_distribution<> dis(0., 1.);

  static int next_int() {
    return (int) (dis(gen) * INT32_MAX);
  }

  static int next_int(int min, int max) {
    return min + (int) (dis(gen) * (max - min));
  }

  static float next_float() {
    return (float) dis(gen);
  }

  static float next_float(float min, float max) {
    return min + (max - min) * (float) dis(gen);
  }

  static glm::vec3 next_vec3() {
    return glm::vec3(next_float(), next_float(), next_float());
  }

  static glm::vec3 next_vec3(float min, float max) {
    return glm::vec3(next_float(min, max), next_float(min, max), next_float(min, max));
  }

  static bool next_bool() {
    return dis(gen) > 0.5f;
  }
}

#endif //LILY_RAND_H
