//
// Created by richard may clarkson on 05/01/2023.
//

#ifndef LILY_ENTITY_H
#define LILY_ENTITY_H

#include "global.h"
#include "comp.h"

namespace Ember {
  struct Entity {
    uint id;
    std::unordered_map<ulong, Component*> components;

    Entity();

    void render(float dt);

    void update();

    inline void add(Component* c) {
      components[typeid(*c).hash_code()] = c;
    }

    template<typename T>
    inline void rem() {
      components.erase(typeid(T).hash_code());
    }

    template<typename T>
    nodiscard inline bool has() const {
      return components.find(typeid(T).hash_code()) != components.end();
    }

    template<typename T>
    nodiscard inline T* get() {
      return (T*) components[typeid(T).hash_code()];
    }
  };
}

#endif //LILY_ENTITY_H
