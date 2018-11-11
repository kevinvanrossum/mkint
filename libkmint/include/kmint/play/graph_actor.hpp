#ifndef KMINT_PLAY_GRAPH_ACTOR_H
#define KMINT_PLAY_GRAPH_ACTOR_H

#include "kmint/map/map.hpp"
#include "kmint/math/vector2d.hpp"
#include "kmint/play/free_roaming_actor.hpp"
#include "kmint/play/graph_drawable.hpp"

namespace kmint::play {
template <typename Graph> class graph_actor : public free_roaming_actor {
public:
  graph_actor(math::vector2d location, Graph const &g)
      : free_roaming_actor{location}, drawable_{g} {};
  bool perceivable() const override { return false; }
  ui::drawable const &drawable() const override { return drawable_; }

private:
  graph_drawable<Graph> drawable_;
};

using map_actor = graph_actor<map::map_graph>;
} // namespace kmint::play

#endif
