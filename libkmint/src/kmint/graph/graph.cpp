#include "kmint/graph/graph.hpp"
#include <istream>
#include <ostream>

namespace kmint {
namespace graph {

std::ostream &operator<<(std::ostream &os, no_node_info /*unused*/) {
  return os;
}
std::istream &operator>>(std::istream &is, no_node_info & /*unused*/) {
  return is;
}

graph read_graph(std::istream &is) {
  return read_basic_graph<no_node_info>(is);
}

} // namespace graph
} // namespace kmint
