#include "kmint/play/actor.hpp"

namespace kmint::play {

void actor::register_collision(actor &p) { collision_set_.emplace_back(&p); }

void actor::register_perceived(actor &p) { perceived_set_.emplace_back(&p); }

} // namespace kmint::play
