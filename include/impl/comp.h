//
// Created by richard may clarkson on 05/01/2023.
//

#ifndef LILY_COMP_H
#define LILY_COMP_H

#include "global.h"
#include "engine/imodel.h"
#include "anim.h"

namespace Ember {
  struct Entity;

  struct Component {
    virtual void render(Entity& entity, float dt) { };

    virtual void update(Entity& entity) { };

    Component() = default;
  };

  struct Position : public Component {
    glm::vec3 pos;
    glm::vec3 prevPos;
    float yaw;
    float prevYaw;
    float pitch;
    float prevPitch;

    Position();
    explicit Position(const glm::vec3& vec);

    void update(Entity& entity) override;

    inline void set_prev() {
      prevPos = pos;
      prevYaw = yaw;
      prevPitch = pitch;
    }

    nodiscard glm::vec3 to_lerped(float dt) const;
  };

  struct Velocity : public Component {
    glm::vec3 vel;
    float yawVel;
    float pitchVel;

    Velocity();
    explicit Velocity(const glm::vec3& in);

    void update(Entity& entity) override;
  };

  struct InstancedBody : public Component {
    InstancedModel* mod;

    explicit InstancedBody(InstancedModel* mod);

    void render(Entity& entity, float dt) override;
  };

  struct Body : public Component {
    Model mod;

    explicit Body(Model mod);
    explicit Body(Model* mod);

    void render(Entity& entity, float dt) override;
  };

  static std::vector<InstancedModel*> __plant_cache;
  struct Plant : public Component {
    InstancedModel* mod;
    float rot;

    Plant();

    void render(Entity& entity, float dt) override;
  };

  struct Player : public Component {
    enum ParticleType {
      BODY, SMOKE
    };

    struct Particle {
      ParticleType type;
      glm::vec3 startPos;
      // random float between -PI and PI
      float seed;
      float start;
      bool markedForDeath = false;
    };

    const Easing movingArms = Animation::back_and_forth(Animation::ease_in_out);
    Position* pos{};
    Velocity* vel{};
    InstancedModel* gray;
    Model yellow;
    Model balloon;
    Animation yaw;
    glm::vec2 prevMovement{};
    std::vector<Particle> particles;
    float prevYaw{};
    float targetYaw{};

    Player();

    void render_particles();
    void render(Entity& entity, float dt) override;

    void update(Entity& entity) override;
  };

  struct Transform : public Component {
    glm::mat4 matrix;

    Transform();
    explicit Transform(const glm::mat4& matrix);
  };
}

#endif //LILY_COMP_H
