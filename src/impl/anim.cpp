//
// Created by richard may clarkson on 06/01/2023.
//
#include <utility>

#include "impl/anim.h"

namespace Ember {
  // CONSTRUCTORS

  Animation::Animation(Easing ease, float start, float duration, bool repeating) : ease(std::move(ease)), start(start), duration(duration), repeating(repeating) {}
  Animation::Animation(Easing ease, float start, float duration) : Animation(std::move(ease), start, duration, false) {}
  Animation::Animation(Easing ease, float duration, bool repeating) : Animation(std::move(ease), now, duration, repeating) {}
  Animation::Animation(Easing ease, float duration) : Animation(std::move(ease), now, duration) {}
  Animation::Animation() : ease(linear) {}
  FromToAnimation::FromToAnimation(float from, float to, Easing ease, float duration) : Animation(std::move(ease), duration), from(from), to(to) {}
  ListOfAnimations::ListOfAnimations(const std::vector<Animation*>& anims) : Animation(linear, now, 0.f), anims(anims) {
    float tot = 0.f;
    for (var* anim : anims) {
      anim->start = start + tot;
      tot += anim->duration;
      duration += anim->duration;
    }
  }

  // IMPLEMENTATIONS

  float Animation::get(float time) {
    if (repeating) {
      time = fmod(time - start, duration) + start;
    }
    if (time < start) return 0;
    if (time > start + duration) return 1;
    return ease(time - start, duration);
  }

  float FromToAnimation::get(float time) {
    return lerp(from, to, Animation::get(time));
  }

  float ListOfAnimations::get(float time) {
    time -= start;
    float tot = 0.f;
    for (int i = 0; i < anims.size(); i++) {
      if (tot < time && (tot + anims[i]->duration > time || anims[i]->repeating)) {
        index = i;
        return anims[i]->get(start + time);
      }
      tot += anims[i]->duration;
    }
    return anims.back()->get(time + start);
  }

  ListOfAnimations::~ListOfAnimations() {
    for (var* anim : anims) {
      delete anim;
    }
  }

  ListOfAnimations::ListOfAnimations(const ListOfAnimations& other) : ListOfAnimations(other.anims) {}

  ListOfAnimations& ListOfAnimations::operator=(const ListOfAnimations& other) {
    if (this == &other) return *this;

    std::vector<Animation*> newAnims;
    for (var* anim : anims) {
      delete anim;
    }
    for (var* anim : other.anims) {
      newAnims.push_back(anim);
    }

    anims = newAnims;
    return *this;
  }

  float Animation::linear(float t, float d) {
    return t / d;
  }

  float Animation::ease_in_out(float t, float d) {
    t /= d / 2;
    if (t < 1) return 0.5f * t * t;
    t -= 1.f;
    return -0.5f * (t * (t - 2) - 1);
  }

  float Animation::ease_in_out_quart(float t, float d) {
    t /= d / 2;
    if (t < 1) return 0.5f * t * t * t * t;
    t -= 2;
    return -0.5f * (t * t * t * t - 2);
  }

  float Animation::ease_in_out_cubic(float t, float d) {
    t /= d / 2;
    if (t < 1) return 0.5f * t * t * t;
    t -= 2;
    return 0.5f * (t * t * t + 2);
  }

  Easing Animation::back_and_forth(const Easing& in) {
    return [in](float t, float d) -> float {
      if (t > d / 2.f) {
        d /= 2.f;
        t -= d;
        return 1 - in(t, d);
      } else {
        d /= 2.f;
        return in(t, d);
      }
    };
  }

  Easing Animation::constant(float val) {
    return [val](float t, float d) -> float {
      return val;
    };
  }
}