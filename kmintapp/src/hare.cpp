#include "hare.hpp"
#include "cow.hpp"
#include "kmint/random.hpp"

using namespace kmint;

static const char *hare_image = "resources/rabbit.png";

map::map_node const &random_hare_node(map::map_graph const &graph) {
  int r = kmint::random_int(0, 3);
  for (std::size_t i = 0; i < graph.num_nodes(); ++i) {
    if (graph[i].node_info().kind == 'H') {
      if (r == 0)
        return graph[i];
      else
        --r;
    }
  }
  throw "could not find node for hare";
}

hare::hare(map::map_graph const &g)
    : play::map_bound_actor{g, random_hare_node(g)},
      drawable_{*this, kmint::graphics::image{hare_image, 1}} {}

void hare::act(kmint::delta_time dt) {
  for (std::size_t i = 0; i < num_colliding_actors(); ++i) {
    auto &a = colliding_actor(i);
    if (&a == cow_) {
      node(random_hare_node(graph()));
    }
  }
}