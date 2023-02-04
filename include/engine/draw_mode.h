//
// Created by richard may clarkson on 19/12/2022.
//

#ifndef GLENGINE_DRAW_MODE_H
#define GLENGINE_DRAW_MODE_H

#include "global.h"

namespace Ember {
  struct DrawMode {
    int size;
    uint cap;
  };

  namespace DrawModes {
    static const DrawMode line{2, GL_LINES};
    static const DrawMode triangle{3, GL_TRIANGLES};
    static const DrawMode triangle_strip{2, GL_TRIANGLE_STRIP};
  }
}
#endif //GLENGINE_DRAW_MODE_H
