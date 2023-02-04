//
// Created by richard may clarkson on 13/12/2022.
//

#ifndef GLENGINE_VAO_H
#define GLENGINE_VAO_H

#include "global.h"

namespace Ember {
  enum Attribute {
    FLOAT1 = 1, FLOAT2 = 2, FLOAT3 = 3, FLOAT4 = 4
  };

  struct VertexArray {
    uint handle;
    int stride;

    VertexArray();

    void init(const std::vector<Attribute>&);

    inline void use() const {
      glBindVertexArray(handle);
    }
  };

}

#endif //GLENGINE_VAO_H
