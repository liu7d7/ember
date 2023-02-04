//wwww
// Created by richard may clarkson on 29/01/2023.
//

#ifndef EMBER_IML_CHUNK_H
#define EMBER_IML_CHUNK_H

#include "global.h"
#include "engine/mesh.h"

namespace Ember {
  struct World;
  struct Chunk {
    struct ChunkVertex {
      glm::vec3 pos;
      glm::vec3 norm;
    };

    static const int SIZE = 24;
    static constexpr float MAXY = 32.f;
    Vec2i chunkPos;
    Mesh<ChunkVertex>* mesh;

    static Shader get_shader() {
      static Shader sh;
      if (!sh.handle) {
        sh = Shader("res/shader/chunk.vert", "res/shader/chunk.frag");
      }
      return sh;
    }

    Chunk();
    Chunk(World& world, Vec2i chunkPos);
  };
}

#endif //EMBER_IML_CHUNK_H
