//
// Created by richard may clarkson on 29/01/2023.
//
#include "impl/chunk.h"
#include "impl/palette.h"
#include "impl/world.h"
#include "rand.h"

namespace Ember {
  glm::vec3 calc_pos(int i, int j, Vec2i chunkPos) {
    glm::vec2 p = {(float) i + (float) chunkPos.x * Chunk::SIZE, (float) j + (float) chunkPos.y * Chunk::SIZE};
    return {p.x, World::height_at(p), p.y};
  }

  Chunk::Chunk(World& world, Vec2i chunkPos) : chunkPos(chunkPos), mesh(new Mesh<ChunkVertex>(DrawModes::triangle, {Attribute::FLOAT3, Attribute::FLOAT3})) {
    mesh->begin();
    int dp[SIZE + 1][SIZE + 1] { -1 };
    for (int i = 0; i <= SIZE; i++) {
      for (int j = 0; j <= SIZE; j++) {
        int offx = i == SIZE ? -1 : 1;
        int offy = j == SIZE ? -1 : 1;
        glm::vec3 a = calc_pos(i, j, chunkPos);
        glm::vec3 b = calc_pos(i + offx, j, chunkPos);
        glm::vec3 c = calc_pos(i, j + offy, chunkPos);
        auto dir = glm::cross(b - a, c - a);
        auto norm = glm::normalize(dir);
        if (offx != -1 && offy != -1 || offx == -1 && offy == -1) {
          norm = -norm;
        }
        dp[i][j] = mesh->put({a, norm});
      }
    }
    for (int i = 0; i < SIZE; i++) {
      for (int j = 0; j < SIZE; j++) {
        mesh->quad(dp[i][j], dp[i][j + 1], dp[i + 1][j + 1], dp[i + 1][j]);
      }
    }
    mesh->end();

    for (int i = 0; i < 3; i++) {
      glm::vec3 pos = Random::next_vec3(0, SIZE);
      pos.x += chunkPos.x * SIZE;
      pos.z += chunkPos.y * SIZE;
      pos.y = World::height_at({pos.x, pos.z});
      auto e = new Entity;
      e->add(new Position(pos));
      e->add(new Plant);
      world.entities.push_back(e);
    }
  }

  Chunk::Chunk() : mesh(nullptr), chunkPos(Vec2i(INT32_MAX, INT32_MAX)) {

  }
}