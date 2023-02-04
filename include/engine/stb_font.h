//
// Created by richard may clarkson on 01/01/2023.
//

#ifndef GLENGINE_STB_FONT_H
#define GLENGINE_STB_FONT_H

#include "global.h"
#include "tex.h"
#include "file.h"
#include "mesh.h"

namespace Ember {
  struct Font {
    struct FontVertex {
      glm::vec3 pos;
      glm::vec2 uv;
      glm::vec4 col;
    };

    struct Char { // format MUST BE *exactly* like stbtt_packedchar
      ushort x0, y0, x1, y1;
      float xoff, yoff, xadvance;
      float xoff2, yoff2;
    };

    Char* chars{};
    Mesh<FontVertex>* mesh{};
    Texture image;
    int numChars{};
    float height{};
    float ascent{};

    const ushort FORMAT = L'\u00a7';

    static Shader get_shader() {
      static Shader sh;
      if (!sh.handle) sh = Shader("res/shader/font.vert", "res/shader/font.frag");
      return sh;
    }

    Font(const Array<ubyte>& bytes, int numChars, float height);

    void add(const std::wstring& text, float x, float y, uint color, bool shadow, float scale = 1.f) const;

    void draw() const;
  };
}

#endif //GLENGINE_STB_FONT_H
