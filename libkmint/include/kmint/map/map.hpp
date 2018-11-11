#ifndef KMINT_MAP_MAP_HPP
#define KMINT_MAP_MAP_HPP

#include "kmint/graph/basic_edge.hpp"
#include "kmint/graph/basic_graph.hpp"
#include "kmint/graph/basic_node.hpp"
#include "kmint/math/size.hpp"
#include <iosfwd>
#include <string>

namespace kmint::map {

/*! \brief a structure containing information about a tile of a graph

This struct contains two members: \a kind and \a reward. The latter is used for
Q-learning algorithms.
*/
struct map_node_info {
  /*! \brief The kind of tile.

    This could for instance convey information about the type of area:
    grassland, or desert or water.
  */
  char kind;
};

using map_graph = kmint::graph::basic_graph<map_node_info>;
using map_node = kmint::graph::basic_node<map_node_info>;
using map_edge = kmint::graph::basic_edge<map_node_info>;

/*! \brief An orthogonal grid of nodes spanning a screen area
 */
class map {
public:
  /*! \brief Constructs a map by obtaining ownership of a graph.


    Because map obtains the ownership of a \ref map_graph, the caller
    must pass in an rvalue reference. For example:
    \code{.cpp}
    #include <utility> // includes std::move

    kmint::map::map_graph g {};
    // ...
    map m { std::move(g), kmint::math::isize{1280,720} };
    \endcode


    \param g an rvalue reference to a \ref map_graph. \a g will be moved from
    \param sz the size of the map in pixels
   */
  map(map_graph &&g, math::isize sz, std::string bg_image);
  map(map const &) = delete;
  map(map &&) = default;
  map &operator=(map const &) = delete;
  map &operator=(map &&) = default;
  /*! \return A reference to the graph corresponding to this map */
  map_graph &graph() noexcept { return graph_; }
  /*! \return A constant reference to the graph corresponding to this map */
  map_graph const &graph() const noexcept { return graph_; }
  /*! \return the dimensions of the map in pixels */
  math::isize size() const noexcept { return size_; }
  /*! \return the path to the background image of this map */
  std::string const &background_image() const noexcept {
    return background_image_;
  }

private:
  map_graph graph_;
  math::isize size_;
  std::string background_image_;
};

map read_map(std::istream &is);
map read_map(const char *description);
map read_map(std::string const &description);

} // namespace kmint::map

#endif /* KMINT_MAP_MAP_HPP */
