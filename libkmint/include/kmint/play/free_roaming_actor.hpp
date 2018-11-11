#ifndef KMINT_PLAY_FREE_ROAMING_ACTOR_H
#define KMINT_PLAY_FREE_ROAMING_ACTOR_H

#include "kmint/math/vector2d.hpp"
#include "kmint/play/actor.hpp"

namespace kmint::play {
class free_roaming_actor : public actor {
public:
  free_roaming_actor(math::vector2d location) : actor{}, location_{location} {}
  math::vector2d location() const override { return location_; }

protected:
  void location(math::vector2d loc) { location_ = loc; }

private:
  math::vector2d location_;
};
} // namespace kmint::play

#endif
