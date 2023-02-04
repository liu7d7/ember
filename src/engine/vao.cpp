//
// Created by richard may clarkson on 18/12/2022.
//

#include "engine/vao.h"

namespace Ember {
  VertexArray::VertexArray() {
    glGenVertexArrays(1, &handle);
  }

  void VertexArray::init(const std::vector<Attribute>& attribs) {
    use();
    const int fSize = sizeof(float);
    ulong offset{0};
    stride = 0;
    for (Attribute i : attribs) stride += i;
    for (uint i = 0; i < attribs.size(); i++) {
      glEnableVertexAttribArray(i);
      glVertexAttribPointer(i, attribs[i], GL_FLOAT, false, stride * fSize, (void*) offset);
      offset += attribs[i] * fSize;
    }
  }
}