//
// Created by richard may clarkson on 10/12/2022.
//

#ifndef GLENGINE_FBO_H
#define GLENGINE_FBO_H

#include "global.h"

namespace Ember {
  struct Framebuffer {
    uint handle;
    uint color{};
    uint depth{};
    int width{};
    int height{};
    bool multisample{};

    Framebuffer() : handle(0) { };

    Framebuffer(int, int, bool color = true, bool depth = false, bool multisample = false);

    void resize(int, int);

    inline void use() const {
      glBindFramebuffer(GL_FRAMEBUFFER, handle);
      die_if_gl("Framebuffer::use>glBindFramebuffer");
    }

    inline void clear() const {
      use();
      if (depth != UINT32_MAX) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        die_if_gl("Framebuffer::clear>glClearD");
      } else {
        glClear(GL_COLOR_BUFFER_BIT);
        die_if_gl("Framebuffer::clear>glClear");
      }
    }

    static inline void unuse() {
      glBindFramebuffer(GL_FRAMEBUFFER, 0);
      die_if_gl("Framebuffer::unuse>glBindFramebuffer");
    }

    inline void blit(Framebuffer* in) const {
      glBindFramebuffer(GL_READ_FRAMEBUFFER, handle);
      glBindFramebuffer(GL_DRAW_FRAMEBUFFER, in->handle);
      glBlitFramebuffer(0, 0, width, height, 0, 0, in->width, in->height, GL_COLOR_BUFFER_BIT, GL_NEAREST);
      die_if_gl("Framebuffer::blit>glBlitFramebuffer1");
    }

    inline void blit_by_handle(uint in, int dstWidth, int dstHeight) const {
      glBindFramebuffer(GL_READ_FRAMEBUFFER, handle);
      glBindFramebuffer(GL_DRAW_FRAMEBUFFER, in);
      glBlitFramebuffer(0, 0, width, height, 0, 0, dstWidth, dstHeight, GL_COLOR_BUFFER_BIT, GL_NEAREST);
      die_if_gl("Framebuffer::blit>glBlitFramebuffer " + std::to_string(in) + " " + std::to_string(dstWidth) + " " + std::to_string(dstHeight));
    }
  };
}

#endif //GLENGINE_FBO_H
