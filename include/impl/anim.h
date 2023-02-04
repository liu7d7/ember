//
// Created by richard may clarkson on 06/01/2023.
//

#ifndef LILY_IML_ANIM_H
#define LILY_IML_ANIM_H

#include "global.h"
#include "functional"

namespace Ember {
  typedef std::function<float(float, float)> Easing;

  struct Animation {
    Easing ease;
    float start{};
    float duration{};
    bool repeating = false;

    Animation();

    Animation(Easing ease, float duration);
    Animation(Easing ease, float duration, bool repeating);
    Animation(Easing ease, float start, float duration);
    Animation(Easing ease, float start, float duration, bool repeating);

    nodiscard virtual inline bool done() {
      return start + duration < now;
    }

    nodiscard virtual float get(float time);

    static float linear(float t, float d);
    static float ease_in_out(float t, float d);
    static float ease_in_out_quart(float t, float d);
    static float ease_in_out_cubic(float t, float d);

    static Easing back_and_forth(const Easing& in);
    static Easing constant(float value);
  };

  struct FromToAnimation : public Animation {
    float from;
    float to;

    FromToAnimation(float from, float to, Easing ease, float duration);

    nodiscard float get(float time) override;
  };

  struct ListOfAnimations : public Animation {
    std::vector<Animation*> anims;
    int index = 0;

    explicit ListOfAnimations(const std::vector<Animation*>& anims);
    // rule of three
    ~ListOfAnimations();
    ListOfAnimations(const ListOfAnimations& other);
    ListOfAnimations& operator=(const ListOfAnimations& other);

    nodiscard float get(float time) override;
  };
}

#endif //LILY_IML_ANIM_H
