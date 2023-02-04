//
// Created by richard may clarkson on 10/12/2022.
//
#include "engine/fbo.h"
#include "engine/tex.h"

using namespace Ember;

namespace Ember {
  void init(Framebuffer& in, bool color, bool depth, bool multisample) {
    if (color) {
      Texture::defaults(in.color, GL_NEAREST, multisample);
      if (multisample)
        glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, 4, GL_RGBA8, in.width, in.height, false);
      else
        glTexStorage2D(GL_TEXTURE_2D, 1, GL_RGBA8, in.width, in.height);
      die_if_gl("Framebuffer::init>colorAndShadingModel>glTexStorage2D");
      glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0,
                             multisample ? GL_TEXTURE_2D_MULTISAMPLE : GL_TEXTURE_2D, in.color, 0);
      die_if_gl("Framebuffer::init>colorAndShadingModel>glFramebufferTexture2D");
    } else {
      in.color = UINT32_MAX;
    }

    if (depth) {
      if (multisample) {
        Texture::defaults(in.depth, GL_NEAREST, multisample);
        glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, 4, GL_DEPTH_COMPONENT24, in.width, in.height, false);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D_MULTISAMPLE, in.depth, 0);
        die_if_gl("Framebuffer::init>depth>glTexImage2DMultisample");
      } else {
        Texture::defaults(in.depth, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, GL_NONE);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, in.width, in.height, 0,
                     GL_DEPTH_COMPONENT, GL_UNSIGNED_INT, nullptr);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D,
                               in.depth, 0);
        die_if_gl("Framebuffer::init>depth>!multisample>glFramebufferTexture2D");
      }
    } else {
      in.depth = UINT32_MAX;
    }

    uint code = glCheckFramebufferStatus(GL_FRAMEBUFFER);
    if (code != GL_FRAMEBUFFER_COMPLETE) {
      die("Framebuffer::init>glCheckFramebufferStatus(" + gl_to_string(code) + ")");
    }
  }

  Framebuffer::Framebuffer(int width, int height, bool color, bool depth, bool multisample) : multisample(multisample),
                                                                                                                width(width),
                                                                                                                height(height) {
    glGenFramebuffers(1, &handle);
    use();

    init(*this, color, depth, multisample);
  }

  void Framebuffer::resize(int newWidth, int newHeight) {
    width = newWidth;
    height = newHeight;
    bool hasColor = color != UINT32_MAX;
    bool hasDepth = depth != UINT32_MAX;
    if (hasColor) {
      glDeleteTextures(1, &color);
    }
    if (hasDepth) {
      glDeleteTextures(1, &depth);
    }
    use();
    init(*this, hasColor, hasDepth, multisample);
  }
}