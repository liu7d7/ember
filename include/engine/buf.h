//
// Created by richard may clarkson on 11/12/2022.
//

#ifndef GLENGINE_BUF_H
#define GLENGINE_BUF_H

#include "global.h"

namespace Ember {
  template<typename T>
  struct Buffer {
    uint cap{};
    uint head{};
    uint size{};
    uint handle;
    T* ptr;

    Buffer() : handle(0) { }

    Buffer(uint cap, uint size) : cap(cap), head(0), ptr(new T[size]), size(size) {
      glGenBuffers(1, &handle);
    }

    void reserve(uint newSize) {
      bool resized = false;
      while (newSize > size) {
        size *= 2;
        resized = true;
      }
      if (resized) {
        T* newItems = new T[size];
        std::copy(ptr, ptr + head, newItems);
        delete[] ptr;
        ptr = newItems;
      }
    }

    void put(const T& item) {
      reserve(head + 1);
      ptr[head++] = item;
    }

    void put(T* items, uint amt) {
      reserve(head + amt);
      copy(items, items + amt, ptr + head);
      head += amt;
    }

    void put(const T* items, uint amt) {
      reserve(head + amt);
      copy(items, items + amt, ptr + head);
      head += amt;
    }

    void data(T* items, uint amt, uint offset = 0) {
      use();
      glBufferSubData(cap, 0ull, amt * sizeof(T), items + offset);
    }

    inline void upload() {
      use();
      glBufferData(cap, sizeof(T) * head, ptr, GL_DYNAMIC_DRAW);
    }

    inline void clear() {
      head = 0;
    }

    inline void use() const {
      glBindBuffer(cap, handle);
    }
  };
}

#endif //GLENGINE_BUF_H
