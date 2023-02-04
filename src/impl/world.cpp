//
// Created by richard may clarkson on 29/01/2023.
//
#include "impl/world.h"
#include "ember.h"

namespace Ember {
  World::World() {
    update(glm::vec3(0, 0, 0));
  }

  void World::update(glm::vec3 camPos) {
    int cx = int(camPos.x / Chunk::SIZE);
    int cy = int(camPos.z / Chunk::SIZE);
    if (camPos.x < 0) cx--;
    if (camPos.z < 0) cy--;
    for (int i = -RENDER_DISTANCE; i <= RENDER_DISTANCE; i++) {
      for (int j = -RENDER_DISTANCE; j <= RENDER_DISTANCE; j++) {
        Vec2i v(cx + i, cy + j);
        Chunk& c = chunks[v];
        if (c.mesh) continue;
        c = Chunk(*this, v);
      }
    }
    constexpr float TICKDIST_SQUARED = RENDER_DISTANCE * RENDER_DISTANCE * Chunk::SIZE * Chunk::SIZE * 4;
    for (auto e : entities) {
      if (distance2dSquared(e->get<Position>()->pos, camPos) > TICKDIST_SQUARED) continue;
      e->update();
    }
  }

  void World::render(glm::vec3 camPos) {
    int cx = int(camPos.x / Chunk::SIZE);
    int cy = int(camPos.z / Chunk::SIZE);
    if (camPos.x < 0) cx--;
    if (camPos.z < 0) cy--;
    GL::shader = Chunk::get_shader();
    for (int i = -RENDER_DISTANCE; i <= RENDER_DISTANCE; i++) {
      for (int j = -RENDER_DISTANCE; j <= RENDER_DISTANCE; j++) {
        Vec2i v(cx + i, cy + j);
        auto m = chunks[v].mesh;
        if (m) {
          m->draw();
        }
      }
    }

    constexpr float VIEWDIST_SQUARED = RENDER_DISTANCE * RENDER_DISTANCE * Chunk::SIZE * Chunk::SIZE;
    for (auto e : entities) {
      if (distance2dSquared(e->get<Position>()->pos, camPos) > VIEWDIST_SQUARED) continue;
      e->render(Ember::tickDelta);
    }
  }
}