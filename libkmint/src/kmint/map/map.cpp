// HERE BE DRAGONS //
#include "kmint/map/map.hpp"
#include "kmint/math/size.hpp"
#include <iostream>
#include <limits>
#include <map>
#include <sstream>
#include <stdexcept>
#include <utility>
#include <vector>

namespace kmint::map {

map::map(map_graph &&g, math::isize sz, std::string bg_image)
    : graph_{std::move(g)}, size_{sz}, background_image_{std::move(bg_image)} {}

struct map_header {
  math::isize size{};
  int tile_dim{};
  std::string background_image{};
  int number_of_tiles() const noexcept { return size.width() * size.height(); }
};

std::istream &operator>>(std::istream &is, map_header &mh) {
  math::isize s{};
  int dim{};
  std::string bg;
  if (is >> s >> dim >> bg) {
    mh.size = s;
    mh.tile_dim = dim;
    mh.background_image = std::move(bg);
  }
  return is;
}

struct tile_info {
  char tile_type;
  bool accessible;
  float weight;
};

std::istream &operator>>(std::istream &is, tile_info &ti) {
  char t{};
  bool a{};
  float w{};
  if (is >> t >> a >> w) {
    ti.tile_type = t;
    ti.accessible = a;
    ti.weight = w;
  }
  return is;
}

class map_info {
public:
  map_info(map_header mh) noexcept : header_{mh} {};
  void add_tile_info(tile_info ti) { infos_.emplace(ti.tile_type, ti); }
  tile_info &at(char tile_type) { return infos_.at(tile_type); }
  tile_info const &at(char tile_type) const { return infos_.at(tile_type); }
  float weight_for(char tile_type) const { return infos_.at(tile_type).weight; }
  bool accessible(char tile_type) const {
    return infos_.at(tile_type).accessible;
  }
  map_header const &header() const noexcept { return header_; }

private:
  map_header header_;
  std::map<char, tile_info> infos_{};
};

class internal_map {
public:
  internal_map(map_info mi, std::vector<char> const &tiles)
      : info_{mi}, tiles_{tiles}, indices_(tiles_.size(), -1) {
    build_graph();
  }
  internal_map(map_info mi, std::vector<char> &&tiles)
      : info_{mi}, tiles_{std::move(tiles)}, indices_(tiles_.size()) {
    build_graph();
  }
  map_graph &graph() noexcept { return graph_; }
  map_info &info() noexcept { return info_; }
  int to_tile_index(int x, int y) const noexcept {
    return y * info_.header().size.width() + x;
  }
  int width() const noexcept { return info_.header().size.width(); }
  int height() const noexcept { return info_.header().size.height(); }

private:
  void build_nodes();
  void build_edges();
  void build_graph();
  map_info info_;
  std::vector<char> tiles_;
  std::vector<int> indices_;
  map_graph graph_{};
};

map_header read_map_header(std::istream &is) {
  map_header mh;
  is >> mh;
  if (!is) {
    throw std::runtime_error{"Could not read map header"};
  }
  return mh;
}

tile_info read_tile_info(std::istream &is) {
  if (tile_info ti{}; is >> ti) {
    return ti;
  }
  throw std::runtime_error{"Could not read tile info"};
}

map read_map(std::istream &is) {

  map_info mi{read_map_header(is)};
  is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  for (std::string s; std::getline(is, s) && !s.empty();) {
    std::istringstream iss{s};
    mi.add_tile_info(read_tile_info(iss));
  }

  std::vector<char> tiles{};
  tiles.reserve(mi.header().number_of_tiles());
  std::copy(std::istream_iterator<char>{is}, std::istream_iterator<char>{},
            std::back_inserter(tiles));
  internal_map m{mi, tiles};
  return {std::move(m.graph()),
          m.info().header().size * m.info().header().tile_dim,
          m.info().header().background_image};
}
map read_map(const char *description) {
  std::istringstream is{description};
  return read_map(is);
}
map read_map(std::string const &description) {
  return read_map(description.c_str());
}

void internal_map::build_nodes() {
  int w = width();
  int h = height();
  int next_index = 0;
  int dim = info_.header().tile_dim;
  int hdim = info_.header().tile_dim / 2;
  for (int y = 0; y < h; ++y) {
    for (int x = 0; x < w; ++x) {
      int tile_index = to_tile_index(x, y);
      char tt = tiles_[tile_index];
      auto ti{info_.at(tt)};
      if (ti.accessible) {
        indices_[tile_index] = next_index++;
        graph_.add_node(math::vector2d(hdim + x * dim, hdim + y * dim), {tt});
      }
    }
  }
}

void internal_map::build_edges() {
  int w = width();
  int h = height();
  for (int x = 0; x < w; ++x) {
    for (int y = 0; y < h; ++y) {

      int tile_index = to_tile_index(x, y);
      char tt = tiles_[tile_index];
      auto ti{info_.at(tt)};
      float weight{ti.weight};

      if (auto this_index = indices_[tile_index]; this_index >= 0) {
        for (int dx = -1; dx <= 1; dx += 2) {
          if (x + dx < 0 || x + dx >= w) {
            continue;
          }
          if (auto other_index = indices_[to_tile_index(x + dx, y)];
              other_index >= 0) {
            graph_[this_index].add_edge(graph_[other_index], weight);
          }
        }
        for (int dy = -1; dy <= 1; dy += 2) {
          if (y + dy < 0 || y + dy >= h) {
            continue;
          }
          if (auto other_index = indices_[to_tile_index(x, y + dy)];
              other_index >= 0) {
            graph_[this_index].add_edge(graph_[other_index], weight);
          }
        }
      }
    }
  }
}

void internal_map::build_graph() {
  build_nodes();
  build_edges();
}

} // namespace kmint::map
