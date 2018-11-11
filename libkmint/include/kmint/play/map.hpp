#ifndef KMINT_PLAY_MAP_HPP
#define KMINT_PLAY_MAP_HPP

#include "kmint/graph/graph.hpp"
#include <iosfwd>
#include <string>

namespace kmint::play {

class map {
public:
  map(std::string const &json);
  map(std::istream &json_is);

private:
  ui::tile_layer foreground_layer_;
  ui::tile_layer main_layer_;
  ui::tile_layer background_layer_;
  graph::graph graph_{};
};

} // namespace kmint::play

#endif /* KMINT_PLAY_MAP_HPP */
