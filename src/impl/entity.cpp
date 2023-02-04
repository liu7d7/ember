//
// Created by richard may clarkson on 05/01/2023.
//
#include "impl/entity.h"
#include "impl/comp.h"
#include "rand.h"

namespace Ember {
  void Entity::render(float dt) {
    for (auto& [_, value] : components) {
      value->render(*this, dt);
    }
  }

  void Entity::update() {
    for (auto& [_, value] : components) {
      value->update(*this);
    }
  }

  Entity::Entity() : id(Random::next_int()) {}
}