#ifndef KMINT_GRAPH_BASIC_EDGE_HPP
#define KMINT_GRAPH_BASIC_EDGE_HPP

#include "kmint/math/vector2d.hpp"

namespace kmint {
namespace graph {
template <typename NodeInfo> class basic_node;

template <typename NodeInfo> class basic_edge {
public:
  using node_type = basic_node<NodeInfo>;
  basic_edge(node_type const &from, node_type const &to, float weight = 1.0f)
      : from_{&from}, to_{&to}, weight_{weight} {}
  node_type const &to() const noexcept { return *to_; }
  node_type const &from() const noexcept { return *from_; }
  float weight() const noexcept { return weight_; }

private:
  node_type const *from_;
  node_type const *to_;
  float weight_;
};

} // namespace graph
} // namespace kmint

#endif
