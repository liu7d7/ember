//
// Created by richard may clarkson on 05/01/2023.
//
#include "engine/stb_font.h"

#define STB_TRUETYPE_IMPLEMENTATION

#include "stb_truetype.h"

namespace Ember {
  Font::Font(const Array<ubyte>& bytes, int numChars, float height) {
    this->mesh = new Mesh<FontVertex>(DrawModes::triangle, {Attribute::FLOAT3, Attribute::FLOAT2, Attribute::FLOAT4});
    this->numChars = numChars;
    this->height = height;
    this->chars = new Char[numChars];
    stbtt_fontinfo fontInfo;
    if (!stbtt_InitFont(&fontInfo, bytes.ptr, 0)) {
      die("Failed to load font");
    }

    stbtt_pack_context packContext;
    ubyte* bitmap = new ubyte[2048 * 2048];
    stbtt_PackBegin(&packContext, bitmap, 2048, 2048, 0, 1, nullptr);
    stbtt_PackSetOversampling(&packContext, 8, 8);
    stbtt_PackFontRange(&packContext, bytes.ptr, 0, height, 32, numChars, (stbtt_packedchar*) chars);
    stbtt_PackEnd(&packContext);

    int asc;
    stbtt_GetFontVMetrics(&fontInfo, &asc, nullptr, nullptr);
    ascent = (float) asc * stbtt_ScaleForMappingEmToPixels(&fontInfo, height);

    image = Texture(bitmap, 2048, 2048, GL_RED);

    delete[] bitmap;
  }

  void Font::add(const std::wstring& text, float x, float y, uint color, bool shadow, float scale) const {
    if (!mesh->building) mesh->begin();
    int len = (int) text.length();
    float dx = x;
    float dy = y + ascent * scale;
    float r = (float) ((color >> 16) & 0xFF) / 255.0f;
    float g = (float) ((color >> 8) & 0xFF) / 255.0f;
    float b = (float) (color & 0xFF) / 255.0f;
    float a = (float) ((color >> 24) & 0xFF) / 255.0f;
    for (int i = 0; i < len; i++) {
      ushort cur = text[i];
      ushort prev = i > 0 ? text[i - 1] : ' ';
      if (prev == FORMAT) continue;

      if (cur == FORMAT && i < len - 1) {
        ushort next = text[i - 1];
        if (isalpha(next)) next = tolower(next);

        // handle formatting
        continue;
      }

      if (cur < 32 || cur > 32 + numChars) cur = ' ';

      var c = chars[cur - 32];
      float dxs = dx + c.xoff * scale;
      float dys = dy + c.yoff * scale;
      float dx1s = dx + c.xoff2 * scale;
      float dy1s = dy + c.yoff2 * scale;

      glm::vec4 col;
      if (shadow) {
        col = glm::vec4(glm::vec3(r, g, b) * 0.25f, a);
        mesh->quad(
          mesh->put({glm::vec3(dxs + 1, dys + 1, 1), glm::vec2((float) c.x0 / 2048.f, (float) c.y0 / 2048.f), col}),
          mesh->put({glm::vec3(dx1s + 1, dys + 1, 1), glm::vec2((float) c.x1 / 2048.f, (float) c.y0 / 2048.f), col}),
          mesh->put({glm::vec3(dx1s + 1, dy1s + 1, 1), glm::vec2((float) c.x1 / 2048.f, (float) c.y1 / 2048.f), col}),
          mesh->put({glm::vec3(dxs + 1, dy1s + 1, 1), glm::vec2((float) c.x0 / 2048.f, (float) c.y1 / 2048.f), col})
        );
      }

      col = glm::vec4(r, g, b, a);
      mesh->quad(
        mesh->put({glm::vec3(dxs, dys, 1), glm::vec2((float) c.x0 / 2048.f, (float) c.y0 / 2048.f), col}),
        mesh->put({glm::vec3(dx1s, dys, 1), glm::vec2((float) c.x1 / 2048.f, (float) c.y0 / 2048.f), col}),
        mesh->put({glm::vec3(dx1s, dy1s, 1), glm::vec2((float) c.x1 / 2048.f, (float) c.y1 / 2048.f), col}),
        mesh->put({glm::vec3(dxs, dy1s, 1), glm::vec2((float) c.x0 / 2048.f, (float) c.y1 / 2048.f), col})
      );

      dx += c.xadvance * scale * 0.96f;
    }
  }

  void Font::draw() const {
    image.use();
    mesh->draw();
  }

}