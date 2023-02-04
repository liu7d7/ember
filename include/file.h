//
// Created by richard may clarkson on 02/01/2023.
//

#ifndef GLENGINE_FILE_H
#define GLENGINE_FILE_H

#include "global.h"

namespace Ember::Files {
  inline Array<ubyte> read_bytes(const std::string& src) {
    FILE* file = fopen(src.c_str(), "rb");
    fseek(file, 0, SEEK_END);
    llong size = ftell(file);
    if (size == -1) {
      fclose(file);
      die("Failed to read file");
    }
    fseek(file, 0, SEEK_SET);

    auto* buf = new ubyte[size];
    fread(buf, 1, size, file);
    fclose(file);

    return Array<ubyte>{buf, size};
  }
}

#endif //GLENGINE_FILE_H
