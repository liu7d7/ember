//
// Created by richard may clarkson on 10/12/2022.
//

#ifndef GLENGINE_TEX_H
#define GLENGINE_TEX_H

#include "global.h"

namespace Ember {
  struct Texture {
    uint handle;
    int cap;
    int width;
    int height;

    Texture();

    explicit Texture(const std::string& src);

    explicit Texture(ubyte* src, int width, int height, int cap);

    inline void use(uint idx = 0) const {
      glActiveTexture(GL_TEXTURE0 + idx);
      glBindTexture(GL_TEXTURE_2D, handle);
    }

    static void defaults(uint& handle, uint filter, bool multisample = false);
  };
}

#endif //GLENGINE_TEX_H
