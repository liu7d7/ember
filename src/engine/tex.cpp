//
// Created by richard may clarkson on 11/12/2022.
//
#include "engine/tex.h"

#define STB_IMAGE_IMPLEMENTATION

#include "stb_image.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION

#include "stb_image_write.h"

void Ember::Texture::defaults(uint& handle, uint filter, bool multisample) {
  glGenTextures(1, &handle);
  glBindTexture(multisample ? GL_TEXTURE_2D_MULTISAMPLE : GL_TEXTURE_2D, handle);
  if (multisample) return;
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filter);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filter);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
  die_if_gl("TextureHelper::defaults");
}

Ember::Texture::Texture(ubyte* src, int width, int height, int cap) : width(width), height(height) {
  Texture::defaults(handle, GL_NEAREST);
  this->cap = cap;
  if (src) {
    glTexImage2D(GL_TEXTURE_2D, 0, cap, width, height, 0, cap, GL_UNSIGNED_BYTE, src);
  } else {
    die("failed to load texture from " + std::to_string(((ulong) src)));
  }
}

Ember::Texture::Texture(const std::string& src) {
  Texture::defaults(handle, GL_LINEAR);
  int channels;
  ubyte* data = stbi_load(src.c_str(), &width, &height, &channels, 0);
  cap = channels == 3 ? GL_RGB : GL_RGBA;
  if (data) {
    glTexImage2D(GL_TEXTURE_2D, 0, cap, width, height, 0, cap, GL_UNSIGNED_BYTE, data);
  } else {
    die("failed to load texture from " + src);
  }
}

Ember::Texture::Texture() : handle(0) {

}
