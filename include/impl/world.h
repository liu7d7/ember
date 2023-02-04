//
// Created by richard may clarkson on 29/01/2023.
//

#ifndef EMBER_IML_WORLD_H
#define EMBER_IML_WORLD_H

#include "global.h"
#include "chunk.h"
#include "gtc/noise.hpp"
#include "entity.h"

namespace Ember {
  struct World {
    static const int RENDER_DISTANCE = 10;
    std::unordered_map<Vec2i, Chunk, HashVec2> chunks;
    std::vector<Entity*> entities;

    World();
    void update(glm::vec3 camPos);
    void render(glm::vec3 camPos);

    static float height_at(glm::vec2 worldPos) {
      auto v = glm::simplex(worldPos / 100.f) * 0.5f + 0.5f;
      return v * Chunk::MAXY;
    }
  };
}

#endif //EMBER_IML_WORLD_H
