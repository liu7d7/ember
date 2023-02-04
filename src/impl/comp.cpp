//
// Created by richard may clarkson on 05/01/2023.
//
#include <utility>

#include "impl/comp.h"
#include "impl/entity.h"
#include "ember.h"
#include "engine/lines.h"
#include "impl/world.h"
#include "rand.h"

namespace Ember {
  // CONSTRUCTORS

  Position::Position() : pos(0.f), yaw(0.f), pitch(0.f), prevPos(0.f), prevYaw(0.f), prevPitch(0.f) { }

  Position::Position(const glm::vec3& vec) : pos(vec), prevPos(vec), yaw(0.f), prevYaw(0.f), pitch(0.f), prevPitch(0.f) { }

  Velocity::Velocity() : vel(0.f), yawVel(0.f), pitchVel(0.f) { }

  Transform::Transform() : matrix(glm::mat4(1.f)) { }

  Transform::Transform(const glm::mat4& matrix) : matrix(matrix) { }

  InstancedBody::InstancedBody(InstancedModel* mod) : mod(mod) { }

  Body::Body(Model* mod) : mod(*mod) { }

  Body::Body(Model mod) : mod(std::move(mod)) { }

  Player::Player() : yaw(Animation(Animation::ease_in_out_quart, 600.f)),
    gray(InstancedModel::get("res/model/icosphere3.obj", {{Model::SHADING_MODEL, {{"Icosphere", glm::vec4(0.5, 1., 0., 0.)}}}, {Model::COLOR, {{"Icosphere", 0xff6e51c8_vec4}}}})),
    yellow("res/model/icosphere3.obj", {{Model::SHADING_MODEL, {{"Icosphere", glm::vec4(0.5, 1., 0., 0.)}}}, {Model::COLOR, {{"Icosphere", 0xffeac4ae_vec4}}}}),
    balloon("res/model/balloon-3.obj", {{Model::SHADING_MODEL, {{"Balloon", glm::vec4(0.5, 0.35, 0.6, 0.)}, {"Carriage", glm::vec4(0.5, 1., 0., 0.)}}}, {Model::COLOR, {{"Balloon", 0xffeac4ae_vec4}, {"Carriage", 0xffd68fb8_vec4}}}})
  {
    gray->mod->scale(0.66f);
    yellow.scale(0.1f);
    balloon.scale(0.8f);
  }

  Velocity::Velocity(const glm::vec3& in) : vel(in), pitchVel(0.f), yawVel(0.f) {}

  Plant::Plant() : rot(Random::next_float(-180.f, 180.f)), mod(__plant_cache.empty() ? nullptr : __plant_cache[Random::next_int() % __plant_cache.size()]) {
    if (!mod) {
      __plant_cache.push_back(InstancedModel::get("res/model/bush2.obj",
                                                  {{Model::SHADING_MODEL, {{"Base", glm::vec4(0.5, 0.7, 0., 0.)}, {"Balls1", glm::vec4(0.5, 0.7, 0.3, 0.)}, {"Balls2", glm::vec4(0.5, 0.6, 0.4, 0.)}}},
                                            {Model::COLOR, {{"Base", 0xffeac4ae_vec4}, {"Balls1", 0xffce79d2_vec4}, {"Balls2", 0xffdda2a3_vec4}, {"Bush", 0xffeac4ae_vec4}}}}));
      __plant_cache.push_back(InstancedModel::get("res/model/bush3.obj",
                                                  {{Model::SHADING_MODEL, {{"Base", glm::vec4(0.5, 0.7, 0., 0.)}, {"Balls1", glm::vec4(0.5, 0.7, 0.3, 0.)}, {"Balls2", glm::vec4(0.5, 0.6, 0.4, 0.)}}},
                                            {Model::COLOR, {{"Base", 0xffeac4ae_vec4}, {"Balls1", 0xffce79d2_vec4}, {"Balls2", 0xffdda2a3_vec4}, {"Bush", 0xffeac4ae_vec4}}}}));
      __plant_cache.push_back(InstancedModel::get("res/model/tree1.obj",
                                                  {{Model::SHADING_MODEL, {{"Trunk", glm::vec4(0.5, .7, 0., 0.)}, {"Leaves1", glm::vec4(0.5, 0.7, 0.3, 0.)}, {"Leaves2", glm::vec4(0.5, 0.6, 0.4, 0.)}, {"Leaves3", glm::vec4(0.5, 0.8, 0.4, 0.)}}},
                                            {Model::COLOR, {{"Trunk", 0xff6e51c8_vec4}, {"Leaves1", 0xffce79d2_vec4}, {"Leaves2", 0xffdda2a3_vec4}, {"Leaves3", 0xffd68fb8_vec4}}}}));
      __plant_cache.push_back(InstancedModel::get("res/model/tree2.obj",
                                                  {{Model::SHADING_MODEL, {{"Trunk", glm::vec4(0.5, .7, 0., 0.)}, {"Leaves1", glm::vec4(0.5, 0.7, 0.3, 0.)}, {"Leaves2", glm::vec4(0.5, 0.6, 0.4, 0.)}}},
                                            {Model::COLOR, {{"Trunk", 0xff6e51c8_vec4}, {"Leaves1", 0xffce79d2_vec4}, {"Leaves2", 0xffdda2a3_vec4}}}}));
      __plant_cache.push_back(InstancedModel::get("res/model/tree3.obj",
                                                  {{Model::SHADING_MODEL, {{"Trunk", glm::vec4(0.5, .7, 0., 0.)}, {"Leaves1", glm::vec4(0.5, 0.7, 0.3, 0.)}, {"Leaves2", glm::vec4(0.5, 0.6, 0.4, 0.)}}},
                                            {Model::COLOR, {{"Trunk", 0xff6e51c8_vec4}, {"Leaves1", 0xffce79d2_vec4}, {"Leaves2", 0xffdda2a3_vec4}}}}));
      __plant_cache.push_back(InstancedModel::get("res/model/tree4.obj",
                                                  {{Model::SHADING_MODEL, {{"Trunk", glm::vec4(0.5, .7, 0., 0.)}, {"Leaves1", glm::vec4(0.5, 0.7, 0.3, 0.)}, {"Leaves2", glm::vec4(0.5, 0.6, 0.4, 0.)}}},
                                            {Model::COLOR, {{"Trunk", 0xff6e51c8_vec4}, {"Leaves1", 0xffce79d2_vec4}, {"Leaves2", 0xffdda2a3_vec4}}}}));
      for (auto it : __plant_cache) {
        it->mod->scale(7.5f);
      }
      mod = __plant_cache[Random::next_int() % __plant_cache.size()];
    }
  }

  // IMPLEMENTATIONS

  void Position::update(Entity& entity) {
    if (entity.has<Velocity>()) {
      var* vel = entity.get<Velocity>();
      prevPos = pos;
      prevYaw = yaw;
      prevPitch = pitch;
      pos += vel->vel;
      yaw += vel->yawVel;
      pitch += vel->pitchVel;
    }
    pos.y = World::height_at(glm::vec2(pos.x, pos.z));
  }

  glm::vec3 Position::to_lerped(float dt) const {
    return lerp(prevPos, pos, dt);
  }

  void Velocity::update(Entity& entity) {
    vel *= 0.75f;
    yawVel *= 0.75f;
    pitchVel *= 0.75f;
  }

  void InstancedBody::render(Entity& entity, float dt) {
    glm::vec3 pos(0.f);
    if (entity.has<Position>()) {
      var* comp = entity.get<Position>();
      pos = lerp(comp->prevPos, comp->pos, dt);
    }
    glm::mat4 transform = entity.has<Transform>() ? entity.get<Transform>()->matrix : glm::mat4(1.f);
    mod->add(pos);
  }

  void Body::render(Entity& entity, float dt) {
    glm::vec3 pos(0.f);
    if (entity.has<Position>()) {
      var* comp = entity.get<Position>();
      pos = comp->to_lerped(dt);
    }
    mod.draw(pos);
  }

  void Player::render_particles() {
    GL::shader = InstancedModel::get_shader();
    for (auto& it : particles) {
      if (it.markedForDeath) continue;
      glm::vec3 posi = it.startPos;
      glm::vec3 dir = {cos(glm::radians(it.seed)), 0.f, sin(glm::radians(it.seed))};
      if (now - it.start > 1000) {
        it.markedForDeath = true;
        continue;
      }
      posi += dir * ((now - it.start) * 0.005f);
      float size = 1 - (now - it.start) * 0.001f + 0.1f;
      GL::push();
      GL::translate(posi);
      GL::scale(glm::vec3(size));
      GL::translate(-posi);
      gray->add(posi);
      GL::pop();
    }

    gray->draw(true);
    // remove parts marked for death
    particles.erase(std::remove_if(particles.begin(), particles.end(), [](const Particle& p) { return p.markedForDeath; }), particles.end());
  }

  constexpr float BODY_OFFSET = 16.f;

  void Player::render(Entity& entity, float dt) {
    if (!this->pos) {
      this->pos = entity.get<Position>();
      this->vel = entity.get<Velocity>();
    }

    glm::vec3 bodyPos = pos->to_lerped(dt) + glm::vec3(0.f, (cos(glm::radians(now * 0.25f)) + 1.f) * 0.75f + BODY_OFFSET, 0.f);

    GL::shader = Model::get_shader();
    GL::push();
    GL::translate(bodyPos);
    GL::rotate(lerp(prevYaw, targetYaw, yaw.get(now)), glm::vec3(0.f, 1.f, 0.f));
    GL::translate(-bodyPos);
    balloon.draw(bodyPos);
    GL::pop();

    render_particles();
  }

  void Player::update(Ember::Entity& entity) {
    if (!this->pos) {
      this->pos = entity.get<Position>();
      this->vel = entity.get<Velocity>();
    }

    glm::vec2 movement(0.f);
    movement.x += (float) (glfwGetKey(Ember::window, GLFW_KEY_D) == GLFW_PRESS);
    movement.x -= (float) (glfwGetKey(Ember::window, GLFW_KEY_A) == GLFW_PRESS);
    movement.y += (float) (glfwGetKey(Ember::window, GLFW_KEY_W) == GLFW_PRESS);
    movement.y -= (float) (glfwGetKey(Ember::window, GLFW_KEY_S) == GLFW_PRESS);

    glm::vec3 bodyPos = pos->pos + glm::vec3(0.f, (cos(glm::radians(now * 0.25f)) + 1.f) * 0.75f + BODY_OFFSET, 0.f);

    if (Ember::age % 12 == 0)
      for (int i = 0; i < 5; i++)
        particles.push_back({Player::SMOKE, bodyPos + glm::vec3(0., 3.75, 0.), Random::next_float(-180.f, 180.f), now});

    if (prevMovement != movement) {
      if (!approx_eq(movement.x, movement.y) || !approx_eq(movement.x, 0.f)) {
        prevYaw = yaw.done() ? targetYaw : lerp(prevYaw, targetYaw, yaw.get(now));
        targetYaw = (float) glm::degrees(atan2(-movement.x, movement.y));
        yaw.start = now;
      }
    }

    prevMovement = movement;

    if (!approx_eq(movement.x, 0.f) || !approx_eq(movement.y, 0.f)) {
      movement = normalize(movement);
    }

    vel->vel.x = -movement.x;
    vel->vel.z = movement.y;

    if (glfwGetKey(Ember::window, GLFW_KEY_SPACE) == GLFW_PRESS && approx_eq(vel->vel.y, 0.f)) {
      vel->vel.y = 3.f;
    }
  }

  void Plant::render(Entity& entity, float dt) {
    mod->add(entity.get<Position>()->to_lerped(dt), glm::rotate(glm::mat4(1.f), glm::radians(rot), glm::vec3(0.f, 1.f, 0.f)));
  }
}