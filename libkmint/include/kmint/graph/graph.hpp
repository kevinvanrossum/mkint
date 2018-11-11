#ifndef KMINT_GRAPH_GRAPH_HPP
#define KMINT_GRAPH_GRAPH_HPP

#include "kmint/graph/basic_edge.hpp"
#include "kmint/graph/basic_graph.hpp"
#include "kmint/graph/basic_node.hpp"
#include <iosfwd>

namespace kmint::graph {

//! An empty struct for nodes that carry no additional information
struct no_node_info {};
std::ostream &operator<<(std::ostream &os, no_node_info /*unused*/);
std::istream &operator>>(std::istream &is, no_node_info & /*unused*/);

//! An alias for basic_graph in which nodes don't carry additonal information
using graph = basic_graph<no_node_info>;
//! An alias for a basic_node that carries no additional information
using node = basic_node<no_node_info>;
//! An alias for a basic_edge that joins two nodes that carry no additional
//! information
using edge = basic_edge<no_node_info>;

/*!
  \brief Read a graph from an input stream
 */
graph read_graph(std::istream &is);

} // namespace kmint::graph

#endif /* KMINT_GRAPH_GRAPH_HPP */
