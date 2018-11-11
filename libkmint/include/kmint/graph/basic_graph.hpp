#ifndef KMINT_GRAPH_BASIC_GRAPH_HPP
#define KMINT_GRAPH_BASIC_GRAPH_HPP

#include "kmint/graph/basic_node.hpp"
#include "kmint/math/vector2d.hpp"
#include "kmint/util/deref_unique_ptr.hpp"
#include "kmint/util/wrapped_iterator.hpp"
#include <algorithm>
#include <iosfwd>
#include <istream>
#include <iterator>
#include <memory>
#include <sstream>
#include <utility>
#include <vector>

namespace kmint {
namespace graph {

/*! \brief A template class for graphs.

   This template allows the definition of several types of graphs parameterized
   by a NodeInfo type. The NodeInfo type may be used to attach arbitrary
   information to a node.

   A basic_graph is a collection of \ref basic_node "basic_nodes". These nodes
   are parameterized by the same type.

   The nodes in the graph can be iterated over. Iterators to the beginning and
   one past the end can be obtained by calling \ref basic_graph::begin
   "begin()", \ref basic_graph::end "end()", \ref basic_graph::cbegin "cbegin()"
   or \ref basic_graph::cend, "cend()". Alternatively, nodes can be accessed by
   their index using the \ref basic_graph::operator[] "indexing operator". The
   number of nodes in the graph can be obtained by calling \ref
   basic_graph::num_nodes "num_nodes()".

   Nodes can be
*/
template <typename NodeInfo> class basic_graph {
public:
  //! The associated node type for this graph
  using node_type = basic_node<NodeInfo>;

private:
  using container = std::vector<std::unique_ptr<node_type>>;

public:
  //! This type is used for indexing
  using size_type = typename container::size_type;
  //! The indexing operator returns a reference to a value of this type.
  using value_type = node_type;
  //! The type of the iterators returned by \ref basic_graph::begin and \ref
  //! basic_graph::end
  using node_iterator =
      kmint::util::wrapped_iterator<node_type, typename container::iterator>;
  //! The type of the iterators returned by \ref basic_graph::cbegin and \ref
  //! basic_graph::cend.
  using const_node_iterator =
      kmint::util::wrapped_iterator<const node_type,
                                    typename container::const_iterator>;

  basic_graph() = default;
  ~basic_graph() = default;
  //! basic_graph maintains unique ownership semantics and cannot be copied.
  basic_graph(basic_graph const & /*other*/) = delete;
  //! basic_graph maintains unique ownership semantics and cannot be copied.
  basic_graph &operator=(basic_graph const & /*other*/) = delete;
  basic_graph(basic_graph && /*other*/) noexcept = default;
  basic_graph &operator=(basic_graph && /*other*/) noexcept = default;

  //! \returns a constant iterator at the first node in the graph
  const_node_iterator begin() const {
    return {nodes_.begin(), util::deref_unique_ptr_const<node_type>};
  }
  //! \returns a constant iterator at the first node in the graph
  const_node_iterator cbegin() const { return begin(); }

  //! \returns a constant iterator at one past the end
  const_node_iterator end() const {
    return {nodes_.end(), util::deref_unique_ptr_const<node_type>};
  }
  //! \returns a constant iterator at one past the end
  const_node_iterator cend() const { return end(); }

  //! \returns an iterator at the first node in the graph
  node_iterator begin() {
    return {nodes_.begin(), util::deref_unique_ptr<node_type>};
  }

  //! \returns an iterator at the one past the end of the nodes
  node_iterator end() {
    return {nodes_.end(), util::deref_unique_ptr<node_type>};
  }
  //! \returns a reference to the node at \a index
  node_type &operator[](size_type index) { return *nodes_[index]; }
  //! \returns a const reference to the node at \a index
  node_type const &operator[](size_type index) const { return *nodes_[index]; }

  /// \returns The number of nodes in the graph
  size_type num_nodes() const noexcept { return nodes_.size(); }

  /*!
    \brief Constructs a node in the graph
    \param loc the location of the node.
    \param ni a copy of this object will be used as the info for the newly
    constructed node \return a reference to the newly constructed node.
  */
  node_type &add_node(math::vector2d loc, NodeInfo const &ni) {
    nodes_.emplace_back(new node_type{num_nodes(), loc, ni});
    return *nodes_.back();
  }
  /*!
    \brief Constructs a node in the graph
    \param loc the location of the node.
    \param ni this object will be moved into the newly constructed node
    \return a reference to the newly constructed node
  */
  node_type &add_node(math::vector2d loc, NodeInfo &&ni) {
    nodes_.emplace_back(new node_type{num_nodes(), loc, std::move(ni)});
    return *nodes_.back();
  }

  /*!
    \brief Constructs a node in the graph. The information for the node will be
    default constructed. \param loc the location of the node. \return a
    reference to the newly constructed node
  */
  node_type &add_node(math::vector2d loc) {
    nodes_.emplace_back(new node_type{num_nodes(), loc});
    return *nodes_.back();
  }

  void untag_all() {
    std::for_each(begin(), end(), [](auto &n) { n.tagged(false); });
  }

  void tag(node_iterator beginTagged, node_iterator endTagged) {
    untag_all();
    std::for_each(beginTagged, endTagged, [](auto &n) { n.tagged(true); });
  }

private:
  container nodes_{};
};

//! Reads a graph from an input stream.
//!
//! \throws [std::runtime_error]() when encountering an error in the stream.
template <typename NodeInfo>
basic_graph<NodeInfo> read_basic_graph(std::istream &is) {
  basic_graph<NodeInfo> result{};
  bool reading_nodes = true;
  for (std::string s; std::getline(is, s);) {
    if (s.empty()) {
      reading_nodes = false;
      continue;
    }

    std::istringstream iss{s};
    if (reading_nodes) {
      math::vector2d p;
      NodeInfo ni{};
      if (iss >> p && iss >> ni) {
        result.add_node(p, ni);
      } else {
        throw std::runtime_error{"Error while reading node: " + s};
      }
    } else {
      int from;
      int to;
      float weight;
      if (iss >> from && iss >> to && iss >> weight) {
        auto &from_node = result[from];
        from_node.add_edge(result[to], weight);
      } else {
        throw std::runtime_error{"Error while reading edge: " + s};
      }
    }
  }

  return result;
}

} // namespace graph
} // namespace kmint

#endif
