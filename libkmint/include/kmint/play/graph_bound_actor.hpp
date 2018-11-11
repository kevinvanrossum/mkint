#ifndef KMINT_PLAY_GRAPH_BOUND_ACTOR_HPP
#define KMINT_PLAY_GRAPH_BOUND_ACTOR_HPP

#include "kmint/map/map.hpp"
#include "kmint/math/vector2d.hpp"
#include "kmint/play/actor.hpp"

namespace kmint::play {

template <typename Graph> class graph_bound_actor : public actor {
public:
  using node_type = typename Graph::node_type;
  using edge_type = typename node_type::edge_type;
  graph_bound_actor(Graph const &graph, node_type const &initial_node)
      : graph_{&graph}, node_{&initial_node} {};
  math::vector2d location() const override { return node_->location(); }

  node_type const &node() const noexcept { return *node_; }
  void node(node_type const &n) noexcept { node_ = &n; }
  Graph const &graph() const noexcept { return *graph_; }

private:
  Graph const *graph_;
  node_type const *node_;
};

using map_bound_actor = graph_bound_actor<map::map_graph>;

} // namespace kmint::play

#endif
